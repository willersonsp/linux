// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * HiSilicon Gigabit Ethernet MAC (HiGMAC) driver — minimal QEMU bring-up.
 *
 * Target: hisi3516av100 / hi3519v101 HiGMAC V200 IP block, as emulated by
 * QEMU hw/net/hisi-gmac.c.  This is the bare-bones path needed to bring
 * up an interface in QEMU SLIRP: ifup, DHCP, ping.  TSO, COE, EEE, RSS,
 * autoeee, multicast hash, ethtool, suspend/resume — all omitted.
 *
 * MDIO is implemented in-driver (registered as a child mii_bus) because
 * the QEMU model exposes the MDIO controller at offset 0x3C0 of the same
 * MMIO region as the MAC.
 *
 * Copyright (c) 2026 OpenIPC.
 */

#include <linux/clk.h>
#include <linux/etherdevice.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/iopoll.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/of.h>
#include <linux/of_mdio.h>
#include <linux/of_net.h>
#include <linux/phy.h>
#include <linux/platform_device.h>
#include <linux/reset.h>
#include <linux/skbuff.h>

/* ── MAC registers ──────────────────────────────────────────────────── */

#define STATION_ADDR_LOW	0x0000
#define STATION_ADDR_HIGH	0x0004
#define MAC_DUPLEX_HALF_CTRL	0x0008
#define PORT_MODE		0x0040
#define PORT_EN			0x0044
#define   BITS_RX_EN		BIT(1)
#define   BITS_TX_EN		BIT(2)
#define REC_FILT_CONTROL	0x0064
#define   BIT_CRC_ERR_PASS	BIT(5)
#define   BIT_PAUSE_FRM_PASS	BIT(4)
#define   BIT_VLAN_DROP_EN	BIT(3)
#define   BIT_BC_DROP_EN	BIT(2)
#define   BIT_MC_MATCH_EN	BIT(1)
#define   BIT_UC_MATCH_EN	BIT(0)
#define MODE_CHANGE_EN		0x01B4
#define   BIT_MODE_CHANGE_EN	BIT(0)
#define CRF_MIN_PACKET		0x0210
#define   BIT_OFFSET_TX_MIN_LEN	8
#define   BIT_MASK_TX_MIN_LEN	GENMASK(13, 8)
#define CONTROL_WORD		0x0214
#define   CONTROL_WORD_CONFIG	0x640

/* ── Descriptor ring registers ──────────────────────────────────────── */

#define RX_FQ_START_ADDR	0x0500
#define RX_FQ_DEPTH		0x0504
#define RX_FQ_WR_ADDR		0x0508
#define RX_FQ_RD_ADDR		0x050C
#define RX_FQ_REG_EN		0x0518

#define RX_BQ_START_ADDR	0x0520
#define RX_BQ_DEPTH		0x0524
#define RX_BQ_WR_ADDR		0x0528
#define RX_BQ_RD_ADDR		0x052C
#define RX_BQ_REG_EN		0x0538

#define TX_BQ_START_ADDR	0x0580
#define TX_BQ_DEPTH		0x0584
#define TX_BQ_WR_ADDR		0x0588
#define TX_BQ_RD_ADDR		0x058C
#define TX_BQ_REG_EN		0x0598

#define TX_RQ_START_ADDR	0x05A0
#define TX_RQ_DEPTH		0x05A4
#define TX_RQ_WR_ADDR		0x05A8
#define TX_RQ_RD_ADDR		0x05AC
#define TX_RQ_REG_EN		0x05B8

/* REG_EN latches the next write to the matching register.  Bit layout
 * matches the vendor header: bit2=START_ADDR_EN, bit1=DEPTH_EN, bit0=
 * read/write pointer enable (whichever is SW-controlled for that ring).
 */
#define   REG_EN_START_ADDR	BIT(2)
#define   REG_EN_DEPTH		BIT(1)
#define   REG_EN_PTR		BIT(0)

#define RAW_PMU_INT		0x05C0
#define ENA_PMU_INT		0x05C4
#define STATUS_PMU_INT		0x05C8
#define DESC_WR_RD_ENA		0x05CC
#define IN_QUEUE_TH		0x05D8
#define RX_BQ_IN_TIMEOUT_TH	0x05E0
#define TX_RQ_IN_TIMEOUT_TH	0x05E4
#define STOP_CMD		0x05E8
#define   BITS_RX_STOP_EN	BIT(0)
#define   BITS_TX_STOP_EN	BIT(1)

#define RX_BQ_IN_INT		BIT(17)
#define TX_RQ_IN_INT		BIT(19)
#define RX_BQ_IN_TIMEOUT_INT	BIT(28)
#define TX_RQ_IN_TIMEOUT_INT	BIT(29)
#define DEF_INT_MASK		(RX_BQ_IN_INT | RX_BQ_IN_TIMEOUT_INT | \
				 TX_RQ_IN_INT | TX_RQ_IN_TIMEOUT_INT)

/* ── MDIO registers (at offset 0x3C0 from MAC base) ─────────────────── */

#define MDIO_BASE		0x03C0
#define MDIO_SINGLE_CMD		(MDIO_BASE + 0x00)
#define MDIO_SINGLE_DATA	(MDIO_BASE + 0x04)
#define MDIO_RDATA_STATUS	(MDIO_BASE + 0x10)
#define   MDIO_WRITE		BIT(16)
#define   MDIO_READ		BIT(17)
#define   MDIO_START		BIT(20)
#define   BIT_PHY_ADDR_OFFSET	8

/* ── Descriptor format ──────────────────────────────────────────────── */

/* 32-byte (8-word) descriptors are the default for HiGMAC V200.  The
 * QEMU model also hardcodes DESC_SIZE_BYTES = 32.  Only word0 and word1
 * are meaningful in this driver; the remaining 6 words are HW-private /
 * RX-hash / skb-id space we leave zero.
 */
struct higmac_desc {
	__le32 data_buff_addr;
	__le32 ctl;	/* see HIGMAC_CTL_* below */
	__le32 reserved[6];
};

#define DESC_SIZE	sizeof(struct higmac_desc)	/* 32 bytes */

/* word1 / ctl layout (matches vendor higmac.h bitfield definition):
 *  bits [10:0]  buffer_len   (programmed by SW = MAX - 1)
 *  bits [15:11] reserved
 *  bits [26:16] data_len     (HW writes RX len here, SW writes TX len)
 *  bits [28:27] reserved
 *  bits [30:29] fl           (FULL = 3 for single-packet)
 *  bit  [31]    descvid      (0 = FREE, 1 = BUSY)
 */
#define CTL_BUF_LEN(x)		((x) & 0x7FF)
#define CTL_DATA_LEN(x)		(((x) & 0x7FF) << 16)
#define CTL_DATA_LEN_GET(c)	(((c) >> 16) & 0x7FF)
#define CTL_FL(x)		(((x) & 0x3) << 29)
#define CTL_FL_FULL		3
#define CTL_DESCVID		BIT(31)

/* ── Driver tunables ────────────────────────────────────────────────── */

#define HIGMAC_RING_LEN		128	/* power of two; per ring */
#define HIGMAC_RX_BUF_SIZE	1600
#define HIGMAC_NAPI_WEIGHT	64

#define ring_next(i)		(((i) + 1) & (HIGMAC_RING_LEN - 1))

struct higmac_ring {
	struct higmac_desc *desc;
	dma_addr_t desc_dma;
	struct sk_buff **skb;	/* one per descriptor */
	dma_addr_t *dma;	/* mapped buffer dma addr per descriptor */
	unsigned int head;
	unsigned int tail;
};

struct higmac_priv {
	void __iomem *base;
	struct device *dev;
	struct net_device *ndev;
	struct napi_struct napi;
	struct mii_bus *mii_bus;
	struct clk *mac_clk;
	struct clk *macif_clk;
	struct reset_control *port_rst;
	struct reset_control *macif_rst;

	struct higmac_ring rx_fq;	/* free queue: SW → HW */
	struct higmac_ring rx_bq;	/* buffer queue: HW → SW */
	struct higmac_ring tx_bq;	/* send queue: SW → HW */
	struct higmac_ring tx_rq;	/* reclaim queue: HW → SW */

	int link_status;
};

/* ── Register helpers ───────────────────────────────────────────────── */

static inline u32 higmac_rd(struct higmac_priv *priv, u32 reg)
{
	return readl(priv->base + reg);
}

static inline void higmac_wr(struct higmac_priv *priv, u32 reg, u32 val)
{
	writel(val, priv->base + reg);
}

/* Convert between ring index and the byte-offset value the HW expects
 * in WR/RD pointer registers.  HW reports/consumes byte offsets relative
 * to ring start, advancing by DESC_SIZE per descriptor.
 */
static inline u32 byte_off(unsigned int idx)
{
	return idx * DESC_SIZE;
}

static inline unsigned int idx_of(u32 byte_offset)
{
	return (byte_offset / DESC_SIZE) & (HIGMAC_RING_LEN - 1);
}

/* ── MDIO bus ───────────────────────────────────────────────────────── */

static int higmac_mdio_wait(struct higmac_priv *priv)
{
	u32 val;

	return readl_poll_timeout(priv->base + MDIO_SINGLE_CMD, val,
				  !(val & MDIO_START), 20, 10000);
}

static int higmac_mdio_read(struct mii_bus *bus, int phy_id, int reg)
{
	struct higmac_priv *priv = bus->priv;
	int ret;

	ret = higmac_mdio_wait(priv);
	if (ret)
		return ret;

	higmac_wr(priv, MDIO_SINGLE_CMD,
		  MDIO_START | MDIO_READ |
		  ((u32)phy_id << BIT_PHY_ADDR_OFFSET) | (reg & 0x1F));

	ret = higmac_mdio_wait(priv);
	if (ret)
		return ret;

	if (higmac_rd(priv, MDIO_RDATA_STATUS))
		return 0;

	return higmac_rd(priv, MDIO_SINGLE_DATA) >> 16;
}

static int higmac_mdio_write(struct mii_bus *bus, int phy_id, int reg,
			     u16 val)
{
	struct higmac_priv *priv = bus->priv;
	int ret;

	ret = higmac_mdio_wait(priv);
	if (ret)
		return ret;

	higmac_wr(priv, MDIO_SINGLE_DATA, val);
	higmac_wr(priv, MDIO_SINGLE_CMD,
		  MDIO_START | MDIO_WRITE |
		  ((u32)phy_id << BIT_PHY_ADDR_OFFSET) | (reg & 0x1F));

	return higmac_mdio_wait(priv);
}

static int higmac_mdio_register(struct higmac_priv *priv)
{
	struct device_node *mdio_np;
	struct mii_bus *bus;
	int ret;

	bus = devm_mdiobus_alloc(priv->dev);
	if (!bus)
		return -ENOMEM;

	bus->name = "higmac_mdio";
	bus->read = higmac_mdio_read;
	bus->write = higmac_mdio_write;
	bus->priv = priv;
	bus->parent = priv->dev;
	snprintf(bus->id, MII_BUS_ID_SIZE, "%s", dev_name(priv->dev));

	mdio_np = of_get_child_by_name(priv->dev->of_node, "mdio");
	ret = of_mdiobus_register(bus, mdio_np);
	of_node_put(mdio_np);
	if (ret) {
		dev_err(priv->dev, "of_mdiobus_register failed: %d\n", ret);
		return ret;
	}

	priv->mii_bus = bus;
	return 0;
}

/* ── Ring allocation / free ─────────────────────────────────────────── */

static int higmac_ring_alloc(struct higmac_priv *priv, struct higmac_ring *r)
{
	r->desc = dma_alloc_coherent(priv->dev,
				     HIGMAC_RING_LEN * DESC_SIZE,
				     &r->desc_dma, GFP_KERNEL);
	if (!r->desc)
		return -ENOMEM;

	r->skb = devm_kcalloc(priv->dev, HIGMAC_RING_LEN,
			      sizeof(*r->skb), GFP_KERNEL);
	if (!r->skb)
		return -ENOMEM;

	r->dma = devm_kcalloc(priv->dev, HIGMAC_RING_LEN,
			      sizeof(*r->dma), GFP_KERNEL);
	if (!r->dma)
		return -ENOMEM;

	r->head = 0;
	r->tail = 0;
	return 0;
}

static void higmac_ring_free(struct higmac_priv *priv, struct higmac_ring *r)
{
	if (r->desc) {
		dma_free_coherent(priv->dev,
				  HIGMAC_RING_LEN * DESC_SIZE,
				  r->desc, r->desc_dma);
		r->desc = NULL;
	}
}

static int higmac_rings_alloc(struct higmac_priv *priv)
{
	int ret;

	ret = higmac_ring_alloc(priv, &priv->rx_fq);
	if (ret)
		return ret;
	ret = higmac_ring_alloc(priv, &priv->rx_bq);
	if (ret)
		goto err_rx_fq;
	ret = higmac_ring_alloc(priv, &priv->tx_bq);
	if (ret)
		goto err_rx_bq;
	ret = higmac_ring_alloc(priv, &priv->tx_rq);
	if (ret)
		goto err_tx_bq;
	return 0;

err_tx_bq:
	higmac_ring_free(priv, &priv->tx_bq);
err_rx_bq:
	higmac_ring_free(priv, &priv->rx_bq);
err_rx_fq:
	higmac_ring_free(priv, &priv->rx_fq);
	return ret;
}

static void higmac_rings_free(struct higmac_priv *priv)
{
	higmac_ring_free(priv, &priv->tx_rq);
	higmac_ring_free(priv, &priv->tx_bq);
	higmac_ring_free(priv, &priv->rx_bq);
	higmac_ring_free(priv, &priv->rx_fq);
}

/* ── RX path ────────────────────────────────────────────────────────── */

/* Refill RX_FQ with new skbs.  Called from open and from NAPI poll. */
static void higmac_rx_refill(struct higmac_priv *priv)
{
	struct higmac_ring *fq = &priv->rx_fq;
	unsigned int pos = fq->head;
	struct sk_buff *skb;
	dma_addr_t addr;
	struct higmac_desc *desc;
	bool advanced = false;

	while (1) {
		unsigned int next = ring_next(pos);

		/* leave one slot empty to distinguish full/empty */
		if (next == fq->tail)
			break;

		if (fq->skb[pos])
			break;

		skb = netdev_alloc_skb_ip_align(priv->ndev,
						HIGMAC_RX_BUF_SIZE);
		if (!skb)
			break;

		addr = dma_map_single(priv->dev, skb->data,
				      HIGMAC_RX_BUF_SIZE, DMA_FROM_DEVICE);
		if (dma_mapping_error(priv->dev, addr)) {
			dev_kfree_skb_any(skb);
			break;
		}

		fq->skb[pos] = skb;
		fq->dma[pos] = addr;

		desc = &fq->desc[pos];
		desc->data_buff_addr = cpu_to_le32(addr);
		desc->ctl = cpu_to_le32(CTL_BUF_LEN(HIGMAC_RX_BUF_SIZE - 1));
		memset(desc->reserved, 0, sizeof(desc->reserved));

		pos = next;
		advanced = true;
	}

	if (advanced) {
		/* publish descriptors before bumping the HW WR pointer */
		wmb();
		fq->head = pos;
		higmac_wr(priv, RX_FQ_WR_ADDR, byte_off(pos));
	}
}

/* Consume RX_BQ — packets the HW has filled.  Returns # packets handed
 * to the stack (used as NAPI work_done).
 */
static int higmac_rx_poll(struct higmac_priv *priv, int budget)
{
	struct net_device *ndev = priv->ndev;
	struct higmac_ring *bq = &priv->rx_bq;
	struct higmac_ring *fq = &priv->rx_fq;
	unsigned int pos = bq->tail;
	unsigned int hw_wr;
	int done = 0;

	hw_wr = idx_of(higmac_rd(priv, RX_BQ_WR_ADDR));

	while (pos != hw_wr && done < budget) {
		struct higmac_desc *desc = &bq->desc[pos];
		u32 ctl = le32_to_cpu(desc->ctl);
		dma_addr_t buf_dma = le32_to_cpu(desc->data_buff_addr);
		unsigned int len = CTL_DATA_LEN_GET(ctl);
		struct sk_buff *skb = NULL;
		unsigned int i;

		/* RX_BQ descriptors carry the dma address back to us; find
		 * the matching slot in rx_fq by dma address.
		 *
		 * For QEMU we typically consume in order, so the slot is
		 * fq->tail, but match on dma to be safe against any HW
		 * reordering (and to avoid relying on RX_FQ index that the
		 * QEMU model doesn't echo back in the descriptor).
		 */
		for (i = 0; i < HIGMAC_RING_LEN; i++) {
			unsigned int slot = (fq->tail + i) & (HIGMAC_RING_LEN - 1);

			if (fq->skb[slot] && fq->dma[slot] == buf_dma) {
				skb = fq->skb[slot];
				dma_unmap_single(priv->dev, fq->dma[slot],
						 HIGMAC_RX_BUF_SIZE,
						 DMA_FROM_DEVICE);
				fq->skb[slot] = NULL;
				fq->dma[slot] = 0;
				if (slot == fq->tail)
					fq->tail = ring_next(fq->tail);
				break;
			}
		}

		if (!skb || !len || len > HIGMAC_RX_BUF_SIZE) {
			if (skb)
				dev_kfree_skb_any(skb);
			ndev->stats.rx_errors++;
			goto next;
		}

		skb_put(skb, len);
		skb->protocol = eth_type_trans(skb, ndev);
		skb->ip_summed = CHECKSUM_NONE;

		napi_gro_receive(&priv->napi, skb);
		ndev->stats.rx_packets++;
		ndev->stats.rx_bytes += len;

next:
		pos = ring_next(pos);
		done++;
	}

	if (pos != bq->tail) {
		bq->tail = pos;
		higmac_wr(priv, RX_BQ_RD_ADDR, byte_off(pos));
	}

	/* Walk fq->tail forward past any holes (slots already consumed
	 * out-of-order above).  This keeps the "leave one slot empty"
	 * convention sane.
	 */
	while (fq->tail != fq->head && !fq->skb[fq->tail])
		fq->tail = ring_next(fq->tail);

	higmac_rx_refill(priv);
	return done;
}

/* ── TX path ────────────────────────────────────────────────────────── */

/* Reclaim completed TX descriptors.  Called from NAPI poll. */
static void higmac_tx_reclaim(struct higmac_priv *priv)
{
	struct net_device *ndev = priv->ndev;
	struct higmac_ring *rq = &priv->tx_rq;
	struct higmac_ring *bq = &priv->tx_bq;
	unsigned int pos = rq->tail;
	unsigned int hw_wr;
	unsigned int pkts = 0;
	unsigned int bytes = 0;

	netif_tx_lock(ndev);

	hw_wr = idx_of(higmac_rd(priv, TX_RQ_WR_ADDR));

	while (pos != hw_wr) {
		struct sk_buff *skb = bq->skb[pos];

		if (!skb)
			break;

		dma_unmap_single(priv->dev, bq->dma[pos], skb->len,
				 DMA_TO_DEVICE);

		pkts++;
		bytes += skb->len;

		dev_consume_skb_any(skb);
		bq->skb[pos] = NULL;
		bq->dma[pos] = 0;

		pos = ring_next(pos);
	}

	if (pos != rq->tail) {
		rq->tail = pos;
		bq->tail = pos;	/* tx_bq and tx_rq advance in lock-step */
		higmac_wr(priv, TX_RQ_RD_ADDR, byte_off(pos));
	}

	if (pkts) {
		netdev_completed_queue(ndev, pkts, bytes);
		if (netif_queue_stopped(ndev))
			netif_wake_queue(ndev);
	}

	netif_tx_unlock(ndev);
}

static netdev_tx_t higmac_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct higmac_priv *priv = netdev_priv(ndev);
	struct higmac_ring *bq = &priv->tx_bq;
	unsigned int pos = bq->head;
	struct higmac_desc *desc;
	dma_addr_t addr;

	if (skb->len < ETH_HLEN) {
		dev_kfree_skb_any(skb);
		ndev->stats.tx_errors++;
		return NETDEV_TX_OK;
	}

	/* Full-ring check; leave one slot empty. */
	if (ring_next(pos) == bq->tail) {
		netif_stop_queue(ndev);
		return NETDEV_TX_BUSY;
	}

	addr = dma_map_single(priv->dev, skb->data, skb->len, DMA_TO_DEVICE);
	if (dma_mapping_error(priv->dev, addr)) {
		dev_kfree_skb_any(skb);
		ndev->stats.tx_dropped++;
		return NETDEV_TX_OK;
	}

	bq->skb[pos] = skb;
	bq->dma[pos] = addr;

	desc = &bq->desc[pos];
	desc->data_buff_addr = cpu_to_le32(addr);
	desc->ctl = cpu_to_le32(CTL_BUF_LEN(HIGMAC_RX_BUF_SIZE - 1) |
				CTL_DATA_LEN(skb->len) |
				CTL_FL(CTL_FL_FULL) |
				CTL_DESCVID);
	memset(desc->reserved, 0, sizeof(desc->reserved));

	/* publish descriptor before bumping HW WR pointer */
	wmb();

	bq->head = ring_next(pos);
	higmac_wr(priv, TX_BQ_WR_ADDR, byte_off(bq->head));

	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += skb->len;
	netdev_sent_queue(ndev, skb->len);

	/* one slot before full → stop the queue */
	if (ring_next(bq->head) == bq->tail)
		netif_stop_queue(ndev);

	return NETDEV_TX_OK;
}

/* ── NAPI / IRQ ─────────────────────────────────────────────────────── */

static int higmac_poll(struct napi_struct *napi, int budget)
{
	struct higmac_priv *priv = container_of(napi, struct higmac_priv,
						napi);
	int work_done;

	higmac_tx_reclaim(priv);
	work_done = higmac_rx_poll(priv, budget);

	if (work_done < budget) {
		napi_complete_done(napi, work_done);
		/* re-enable interrupts */
		higmac_wr(priv, ENA_PMU_INT, DEF_INT_MASK);
	}

	return work_done;
}

static irqreturn_t higmac_irq(int irq, void *dev_id)
{
	struct net_device *ndev = dev_id;
	struct higmac_priv *priv = netdev_priv(ndev);
	u32 status;

	status = higmac_rd(priv, RAW_PMU_INT) & DEF_INT_MASK;
	if (!status)
		return IRQ_NONE;

	/* mask and ack */
	higmac_wr(priv, ENA_PMU_INT, 0);
	higmac_wr(priv, RAW_PMU_INT, status);

	napi_schedule(&priv->napi);
	return IRQ_HANDLED;
}

/* ── HW init ────────────────────────────────────────────────────────── */

static void higmac_set_mac_hw(struct higmac_priv *priv, const u8 *mac)
{
	u32 high = (mac[0] << 8) | mac[1];
	u32 low  = (mac[2] << 24) | (mac[3] << 16) | (mac[4] << 8) | mac[5];

	higmac_wr(priv, STATION_ADDR_HIGH, high);
	higmac_wr(priv, STATION_ADDR_LOW, low);
}

/* Program one ring's base addr + depth via the latched REG_EN dance. */
static void higmac_setup_ring(struct higmac_priv *priv,
			      u32 reg_en, u32 reg_start, u32 reg_depth,
			      dma_addr_t base)
{
	/* base */
	higmac_wr(priv, reg_en, REG_EN_START_ADDR);
	higmac_wr(priv, reg_start, lower_32_bits(base));
	higmac_wr(priv, reg_en, 0);

	/* depth (in 32-bit words: descriptors * DESC_SIZE / 4) */
	higmac_wr(priv, reg_en, REG_EN_DEPTH);
	higmac_wr(priv, reg_depth,
		  HIGMAC_RING_LEN * (DESC_SIZE / sizeof(u32)));
	higmac_wr(priv, reg_en, 0);
}

static void higmac_hw_init(struct higmac_priv *priv)
{
	u32 val;

	/* mask and clear all interrupts */
	higmac_wr(priv, ENA_PMU_INT, 0);
	higmac_wr(priv, RAW_PMU_INT, ~0u);

	/* permissive receive filter: accept broadcast + everything, but
	 * drop CRC errors (BIT_CRC_ERR_PASS=1 means "let CRC-bad pass" —
	 * here we set it because we don't want to drop in QEMU where
	 * there are no CRC errors anyway; vendor sets it too).
	 */
	val = BIT_CRC_ERR_PASS;
	higmac_wr(priv, REC_FILT_CONTROL, val);

	/* TX min packet length = ETH_HLEN */
	val = higmac_rd(priv, CRF_MIN_PACKET);
	val &= ~BIT_MASK_TX_MIN_LEN;
	val |= ETH_HLEN << BIT_OFFSET_TX_MIN_LEN;
	higmac_wr(priv, CRF_MIN_PACKET, val);

	higmac_wr(priv, CONTROL_WORD, CONTROL_WORD_CONFIG);

	/* default port mode: 100M full-duplex.  QEMU's PHY stub reports
	 * 100M FD permanently, so we don't bother with adjust_link.
	 */
	higmac_wr(priv, MODE_CHANGE_EN, BIT_MODE_CHANGE_EN);
	higmac_wr(priv, PORT_MODE, 0x01);	/* GMAC_SPEED_100 */
	higmac_wr(priv, MODE_CHANGE_EN, 0);
	higmac_wr(priv, MAC_DUPLEX_HALF_CTRL, 1);

	/* IRQ thresholds — fire immediately on first packet */
	higmac_wr(priv, IN_QUEUE_TH, (1 << 16) | 1);
	higmac_wr(priv, RX_BQ_IN_TIMEOUT_TH, 0x10000);
	higmac_wr(priv, TX_RQ_IN_TIMEOUT_TH, 0x18000);

	/* program ring descriptor bases + depths */
	higmac_setup_ring(priv, RX_FQ_REG_EN,
			  RX_FQ_START_ADDR, RX_FQ_DEPTH,
			  priv->rx_fq.desc_dma);
	higmac_setup_ring(priv, RX_BQ_REG_EN,
			  RX_BQ_START_ADDR, RX_BQ_DEPTH,
			  priv->rx_bq.desc_dma);
	higmac_setup_ring(priv, TX_BQ_REG_EN,
			  TX_BQ_START_ADDR, TX_BQ_DEPTH,
			  priv->tx_bq.desc_dma);
	higmac_setup_ring(priv, TX_RQ_REG_EN,
			  TX_RQ_START_ADDR, TX_RQ_DEPTH,
			  priv->tx_rq.desc_dma);
}

static void higmac_reset(struct higmac_priv *priv)
{
	if (priv->port_rst) {
		reset_control_assert(priv->port_rst);
		usleep_range(50, 100);
		reset_control_deassert(priv->port_rst);
	}
	if (priv->macif_rst) {
		reset_control_assert(priv->macif_rst);
		usleep_range(50, 100);
		reset_control_deassert(priv->macif_rst);
	}
}

/* ── netdev_ops ─────────────────────────────────────────────────────── */

static int higmac_open(struct net_device *ndev)
{
	struct higmac_priv *priv = netdev_priv(ndev);
	int ret;

	ret = higmac_rings_alloc(priv);
	if (ret)
		return ret;

	higmac_reset(priv);
	higmac_hw_init(priv);
	higmac_set_mac_hw(priv, ndev->dev_addr);

	/* prime RX_FQ before enabling RX */
	higmac_rx_refill(priv);

	napi_enable(&priv->napi);

	/* enable descriptor engines (bit pattern from vendor) */
	higmac_wr(priv, DESC_WR_RD_ENA, 0xF);

	/* enable TX + RX */
	higmac_wr(priv, PORT_EN, BITS_TX_EN | BITS_RX_EN);

	/* enable interrupts */
	higmac_wr(priv, RAW_PMU_INT, ~0u);
	higmac_wr(priv, ENA_PMU_INT, DEF_INT_MASK);

	if (ndev->phydev)
		phy_start(ndev->phydev);

	netif_start_queue(ndev);
	netif_carrier_on(ndev);
	return 0;
}

static int higmac_stop(struct net_device *ndev)
{
	struct higmac_priv *priv = netdev_priv(ndev);
	unsigned int i;

	netif_stop_queue(ndev);
	netif_carrier_off(ndev);

	if (ndev->phydev)
		phy_stop(ndev->phydev);

	/* mask interrupts and stop port */
	higmac_wr(priv, ENA_PMU_INT, 0);
	higmac_wr(priv, STOP_CMD, BITS_RX_STOP_EN | BITS_TX_STOP_EN);
	higmac_wr(priv, PORT_EN, 0);
	higmac_wr(priv, DESC_WR_RD_ENA, 0);

	napi_disable(&priv->napi);

	/* unmap any in-flight buffers */
	for (i = 0; i < HIGMAC_RING_LEN; i++) {
		if (priv->rx_fq.skb[i]) {
			dma_unmap_single(priv->dev, priv->rx_fq.dma[i],
					 HIGMAC_RX_BUF_SIZE,
					 DMA_FROM_DEVICE);
			dev_kfree_skb_any(priv->rx_fq.skb[i]);
			priv->rx_fq.skb[i] = NULL;
		}
		if (priv->tx_bq.skb[i]) {
			dma_unmap_single(priv->dev, priv->tx_bq.dma[i],
					 priv->tx_bq.skb[i]->len,
					 DMA_TO_DEVICE);
			dev_kfree_skb_any(priv->tx_bq.skb[i]);
			priv->tx_bq.skb[i] = NULL;
		}
	}

	higmac_rings_free(priv);
	netdev_reset_queue(ndev);
	return 0;
}

static int higmac_set_mac_address(struct net_device *ndev, void *p)
{
	struct higmac_priv *priv = netdev_priv(ndev);
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	eth_hw_addr_set(ndev, addr->sa_data);
	higmac_set_mac_hw(priv, ndev->dev_addr);
	return 0;
}

static const struct net_device_ops higmac_netdev_ops = {
	.ndo_open		= higmac_open,
	.ndo_stop		= higmac_stop,
	.ndo_start_xmit		= higmac_xmit,
	.ndo_set_mac_address	= higmac_set_mac_address,
	.ndo_validate_addr	= eth_validate_addr,
	.ndo_eth_ioctl		= phy_do_ioctl_running,
};

/* ── phy adjust_link (no-op for QEMU PHY stub, kept for real HW) ────── */

static void higmac_adjust_link(struct net_device *ndev)
{
	struct higmac_priv *priv = netdev_priv(ndev);
	struct phy_device *phy = ndev->phydev;
	int status = 0;

	if (!phy)
		return;
	if (phy->link)
		status |= BIT(0);

	if (status != priv->link_status) {
		priv->link_status = status;
		phy_print_status(phy);
	}
}

/* ── Probe / remove ─────────────────────────────────────────────────── */

static int higmac_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct net_device *ndev;
	struct higmac_priv *priv;
	struct phy_device *phy;
	int ret;

	ndev = devm_alloc_etherdev(dev, sizeof(*priv));
	if (!ndev)
		return -ENOMEM;

	SET_NETDEV_DEV(ndev, dev);
	platform_set_drvdata(pdev, ndev);

	priv = netdev_priv(ndev);
	priv->dev = dev;
	priv->ndev = ndev;

	priv->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	priv->mac_clk = devm_clk_get_optional_enabled(dev, "higmac_clk");
	if (IS_ERR(priv->mac_clk))
		return dev_err_probe(dev, PTR_ERR(priv->mac_clk),
				     "higmac_clk\n");

	priv->macif_clk = devm_clk_get_optional_enabled(dev, "macif_clk");
	if (IS_ERR(priv->macif_clk))
		return dev_err_probe(dev, PTR_ERR(priv->macif_clk),
				     "macif_clk\n");

	priv->port_rst = devm_reset_control_get_optional(dev, "port_reset");
	if (IS_ERR(priv->port_rst))
		return dev_err_probe(dev, PTR_ERR(priv->port_rst),
				     "port_reset\n");

	priv->macif_rst = devm_reset_control_get_optional(dev, "macif_reset");
	if (IS_ERR(priv->macif_rst))
		return dev_err_probe(dev, PTR_ERR(priv->macif_rst),
				     "macif_reset\n");

	ret = of_get_ethdev_address(np, ndev);
	if (ret) {
		eth_hw_addr_random(ndev);
		dev_info(dev, "no MAC in DT, using random %pM\n",
			 ndev->dev_addr);
	}

	ret = higmac_mdio_register(priv);
	if (ret)
		return ret;

	phy = of_phy_get_and_connect(ndev, np, higmac_adjust_link);
	if (!phy) {
		dev_err(dev, "failed to connect to PHY\n");
		ret = -ENODEV;
		goto err_mdio;
	}

	ndev->netdev_ops = &higmac_netdev_ops;
	ndev->watchdog_timeo = 5 * HZ;

	netif_napi_add_weight(ndev, &priv->napi, higmac_poll,
			      HIGMAC_NAPI_WEIGHT);

	ndev->irq = platform_get_irq(pdev, 0);
	if (ndev->irq < 0) {
		ret = ndev->irq;
		goto err_phy;
	}

	ret = devm_request_irq(dev, ndev->irq, higmac_irq, IRQF_SHARED,
			       dev_name(dev), ndev);
	if (ret) {
		dev_err(dev, "request_irq failed: %d\n", ret);
		goto err_phy;
	}

	ret = register_netdev(ndev);
	if (ret) {
		dev_err(dev, "register_netdev failed: %d\n", ret);
		goto err_phy;
	}

	dev_info(dev, "HiGMAC at %pa irq %d mac %pM\n",
		 &pdev->resource[0].start, ndev->irq, ndev->dev_addr);
	return 0;

err_phy:
	netif_napi_del(&priv->napi);
	phy_disconnect(phy);
err_mdio:
	mdiobus_unregister(priv->mii_bus);
	return ret;
}

static void higmac_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct higmac_priv *priv = netdev_priv(ndev);

	unregister_netdev(ndev);
	netif_napi_del(&priv->napi);
	if (ndev->phydev)
		phy_disconnect(ndev->phydev);
	mdiobus_unregister(priv->mii_bus);
}

static const struct of_device_id higmac_of_match[] = {
	{ .compatible = "hisilicon,higmac" },
	{ .compatible = "hisilicon,hi3516av100-gmac" },
	{ .compatible = "hisilicon,hi3519v101-gmac" },
	{},
};
MODULE_DEVICE_TABLE(of, higmac_of_match);

static struct platform_driver higmac_driver = {
	.driver = {
		.name = "hisi-higmac",
		.of_match_table = higmac_of_match,
	},
	.probe = higmac_probe,
	.remove = higmac_remove,
};

module_platform_driver(higmac_driver);

MODULE_DESCRIPTION("HiSilicon HiGMAC Gigabit Ethernet driver (minimal)");
MODULE_AUTHOR("OpenIPC");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:hisi-higmac");
