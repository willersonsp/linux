// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Hi3516AV100 / Hi3516DV100 Clock and Reset Generator Driver
 *
 * Copyright (c) 2016 HiSilicon Technologies Co., Ltd.
 *
 * Ported from the 4.9 vendor BSP (clk-hi3516a.c) onto the modern crg-
 * platform_driver scaffold, mirroring crg-hi3516cv200.c. Keeps the
 * vendor compatible string ("hisilicon,hi3516a-clock") so the vendor
 * DT compiles unchanged against this driver. V2A generation —
 * Cortex-A7, ARMv7. Distinct from the V2 cv200/3518ev20x family which
 * uses ARM926EJ-S.
 *
 * SoC sibling list (all share this CRG layout): Hi3516AV100,
 * Hi3516DV100.
 *
 * The vendor BSP programs APLL at boot for the CPU mux. This mainline
 * port leaves the CPU at the U-Boot-configured rate (APLL exposed as
 * a stub fixed-rate so DT references resolve) — full PLL support is
 * a follow-up; the kernel boots fine without runtime CPU freq scaling.
 */

#include <dt-bindings/clock/hi3516av100-clock.h>
#include <linux/clk-provider.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/reset-controller.h>
#include "clk.h"
#include "crg.h"
#include "reset.h"

/* ---------------- CRG block (hisilicon,hi3516a-clock) ---------------- */

static const struct hisi_fixed_rate_clock hi3516av100_fixed_rate_clks[] = {
	{ HI3516AV100_FIXED_3M,      "3m",      NULL, 0, 3000000,        },
	{ HI3516AV100_FIXED_6M,      "6m",      NULL, 0, 6000000,        },
	{ HI3516AV100_FIXED_13P5M,   "13.5m",   NULL, 0, 13500000,       },
	{ HI3516AV100_FIXED_24M,     "24m",     NULL, 0, 24000000,       },
	{ HI3516AV100_FIXED_25M,     "25m",     NULL, 0, 25000000,       },
	{ HI3516AV100_FIXED_27M,     "27m",     NULL, 0, 27000000,       },
	{ HI3516AV100_FIXED_37P125M, "37.125m", NULL, 0, 37125000,       },
	{ HI3516AV100_FIXED_50M,     "50m",     NULL, 0, 50000000,       },
	{ HI3516AV100_FIXED_74P25M,  "74.25m",  NULL, 0, 74250000,       },
	{ HI3516AV100_FIXED_75M,     "75m",     NULL, 0, 75000000,       },
	{ HI3516AV100_FIXED_99M,     "99m",     NULL, 0, 99000000,       },
	{ HI3516AV100_FIXED_100M,    "100m",    NULL, 0, 100000000,      },
	{ HI3516AV100_FIXED_125M,    "125m",    NULL, 0, 125000000,      },
	{ HI3516AV100_FIXED_145M,    "145m",    NULL, 0, 145000000,      },
	{ HI3516AV100_FIXED_148P5M,  "148.5m",  NULL, 0, 148500000,      },
	{ HI3516AV100_FIXED_150M,    "150m",    NULL, 0, 150000000,      },
	{ HI3516AV100_FIXED_194M,    "194m",    NULL, 0, 194000000,      },
	{ HI3516AV100_FIXED_198M,    "198m",    NULL, 0, 198000000,      },
	{ HI3516AV100_FIXED_200M,    "200m",    NULL, 0, 200000000,      },
	{ HI3516AV100_FIXED_229M,    "229m",    NULL, 0, 229000000,      },
	{ HI3516AV100_FIXED_237M,    "237m",    NULL, 0, 237000000,      },
	{ HI3516AV100_FIXED_242M,    "242m",    NULL, 0, 242000000,      },
	{ HI3516AV100_FIXED_250M,    "250m",    NULL, 0, 250000000,      },
	{ HI3516AV100_FIXED_297M,    "297m",    NULL, 0, 297000000,      },
	{ HI3516AV100_FIXED_300M,    "300m",    NULL, 0, 300000000,      },
	{ HI3516AV100_FIXED_333M,    "333m",    NULL, 0, 333000000,      },
	{ HI3516AV100_FIXED_400M,    "400m",    NULL, 0, 400000000,      },
	{ HI3516AV100_FIXED_500M,    "500m",    NULL, 0, 500000000,      },
	{ HI3516AV100_FIXED_594M,    "594m",    NULL, 0, 594000000,      },
	{ HI3516AV100_FIXED_600M,    "600m",    NULL, 0, 600000000,      },
	{ HI3516AV100_FIXED_750M,    "750m",    NULL, 0, 750000000,      },
	{ HI3516AV100_FIXED_900M,    "900m",    NULL, 0, 900000000,      },
	{ HI3516AV100_FIXED_1000M,   "1000m",   NULL, 0, 1000000000UL,   },
	{ HI3516AV100_FIXED_1188M,   "1188m",   NULL, 0, 1188000000UL,   },
	/* APLL: stub fixed-rate at 850 MHz (mid of vendor OPP table). Full
	 * PLL programming is a follow-up — DT references resolve so the
	 * a7_mux entry doesn't fail clk_get during probe. */
	{ HI3516AV100_APLL_CLK,      "apll",    NULL, 0, 850000000,      },
};

/* Vendor mux topology — bits per register from clk-hi3516a.c (v1.0.8.0
 * BSP). sysaxi_mux selects 198m vs 148.5m; CPU mux (a7_mux) picks
 * 400m/500m/apll for the Cortex-A7 cluster. */
static const char *const sysaxi_mux_p[]  = { "198m", "148.5m" };
static const char *const uart_mux_p[]    = { "clk_sysapb", "6m" };
static const char *const snor_mux_p[]    = { "24m", "75m", "125m" };
static const char *const snand_mux_p[]   = { "24m", "75m", "125m" };
static const char *const nand_mux_p[]    = { "24m", "198m" };
static const char *const eth_phy_mux_p[] = { "50m", "25m" };
static const char *const a7_mux_p[]      = { "400m", "500m", "apll" };
static const char *const mmc_mux_p[]     = { "50m", "100m", "25m", "75m" };

static u32 sysaxi_mux_table[]  = { 0, 1 };
static u32 uart_mux_table[]    = { 0, 1 };
static u32 snor_mux_table[]    = { 0, 1, 2 };
static u32 snand_mux_table[]   = { 0, 1, 2 };
static u32 nand_mux_table[]    = { 0, 1 };
static u32 eth_phy_mux_table[] = { 0, 1 };
static u32 a7_mux_table[]      = { 2, 1, 0 };
static u32 mmc_mux_table[]     = { 0, 1, 2, 3 };

static const struct hisi_mux_clock hi3516av100_mux_clks[] = {
	{ HI3516AV100_SYSAXI_CLK,  "sysaxi_mux",  sysaxi_mux_p,
	  ARRAY_SIZE(sysaxi_mux_p),
	  CLK_SET_RATE_PARENT, 0x30, 3, 1, 0, sysaxi_mux_table, },
	{ HI3516AV100_SNOR_MUX,    "snor_mux",    snor_mux_p,
	  ARRAY_SIZE(snor_mux_p),
	  CLK_SET_RATE_PARENT, 0xc0, 2, 2, 0, snor_mux_table, },
	{ HI3516AV100_SNAND_MUX,   "snand_mux",   snand_mux_p,
	  ARRAY_SIZE(snand_mux_p),
	  CLK_SET_RATE_PARENT, 0xc0, 6, 2, 0, snand_mux_table, },
	{ HI3516AV100_NAND_MUX,    "nand_mux",    nand_mux_p,
	  ARRAY_SIZE(nand_mux_p),
	  CLK_SET_RATE_PARENT, 0xd0, 2, 1, 0, nand_mux_table, },
	{ HI3516AV100_MMC0_MUX,    "mmc0_mux",    mmc_mux_p,
	  ARRAY_SIZE(mmc_mux_p),
	  CLK_SET_RATE_PARENT, 0xc4, 2, 2, 0, mmc_mux_table, },
	{ HI3516AV100_MMC1_MUX,    "mmc1_mux",    mmc_mux_p,
	  ARRAY_SIZE(mmc_mux_p),
	  CLK_SET_RATE_PARENT, 0xc4, 10, 2, 0, mmc_mux_table, },
	{ HI3516AV100_UART_MUX,    "uart_mux",    uart_mux_p,
	  ARRAY_SIZE(uart_mux_p),
	  CLK_SET_RATE_PARENT, 0xe4, 19, 1, 0, uart_mux_table, },
	{ HI3516AV100_ETH_PHY_MUX, "eth_phy_mux", eth_phy_mux_p,
	  ARRAY_SIZE(eth_phy_mux_p),
	  CLK_SET_RATE_PARENT, 0xcc, 6, 1, 0, eth_phy_mux_table, },
	{ HI3516AV100_A7_MUX,      "a7_mux",      a7_mux_p,
	  ARRAY_SIZE(a7_mux_p),
	  CLK_SET_RATE_PARENT, 0x30, 8, 2, 0, a7_mux_table, },
};

/* sysaxi/4 → clk_sysapb (50 MHz) — vendor fixed-factor entry. */
static struct hisi_fixed_factor_clock hi3516av100_fixed_factor_clks[] = {
	{ HI3516AV100_SYSAXI_CLK, "clk_sysapb", "sysaxi_mux", 1, 4,
	  CLK_SET_RATE_PARENT, },
};

static const struct hisi_gate_clock hi3516av100_gate_clks[] = {
	/* spi nor / nand / parallel-nand */
	{ HI3516AV100_SNOR_CLK,     "clk_snor",     "snor_mux",
	  CLK_SET_RATE_PARENT, 0xc0, 1, 0, },
	{ HI3516AV100_SNAND_CLK,    "clk_snand",    "snand_mux",
	  CLK_SET_RATE_PARENT, 0xc0, 5, 0, },
	{ HI3516AV100_NAND_CLK,     "clk_nand",     "nand_mux",
	  CLK_SET_RATE_PARENT, 0xd8, 1, 0, },
	/* mmc / sd */
	{ HI3516AV100_MMC0_CLK,     "clk_mmc0",     "mmc0_mux",
	  CLK_SET_RATE_PARENT, 0xc4, 1, 0, },
	{ HI3516AV100_MMC1_CLK,     "clk_mmc1",     "mmc1_mux",
	  CLK_SET_RATE_PARENT, 0xc4, 9, 0, },
	/* usb */
	{ HI3516AV100_USB2_CTRL_UTMI0_REQ, "clk_usb2_utmi0_req", NULL,
	  CLK_SET_RATE_PARENT, 0xb4, 5, 1, },
	{ HI3516AV100_USB2_HRST_REQ,       "clk_usb2_hrst_req",  NULL,
	  CLK_SET_RATE_PARENT, 0xb4, 0, 1, },
	/* uart */
	{ HI3516AV100_UART0_CLK,    "clk_uart0",    "50m",
	  CLK_SET_RATE_PARENT, 0xe4, 15, 0, },
	{ HI3516AV100_UART1_CLK,    "clk_uart1",    "50m",
	  CLK_SET_RATE_PARENT, 0xe4, 16, 0, },
	{ HI3516AV100_UART2_CLK,    "clk_uart2",    "50m",
	  CLK_SET_RATE_PARENT, 0xe4, 17, 0, },
	{ HI3516AV100_UART3_CLK,    "clk_uart3",    "50m",
	  CLK_SET_RATE_PARENT, 0xe4, 18, 0, },
	/* ethernet — av100 has higmac (GMAC) not femac. Two gate bits:
	 * clk_eth (port) and clk_eth_macif (mac interface). */
	{ HI3516AV100_ETH_CLK,      "clk_eth",      NULL,
	  CLK_SET_RATE_PARENT, 0xcc, 1, 0, },
	{ HI3516AV100_ETH_MACIF_CLK, "clk_eth_macif", NULL,
	  CLK_SET_RATE_PARENT, 0xcc, 3, 0, },
	/* spi */
	{ HI3516AV100_SPI0_CLK,     "clk_spi0",     "clk_sysapb",
	  CLK_SET_RATE_PARENT, 0xe4, 13, 0, },
	{ HI3516AV100_SPI1_CLK,     "clk_spi1",     "clk_sysapb",
	  CLK_SET_RATE_PARENT, 0xe4, 14, 0, },
	/* dmac */
	{ HI3516AV100_DMAC_CLK,     "clk_dmac",     "50m",
	  CLK_SET_RATE_PARENT, 0xd8, 5, 0, },
};

static struct hisi_clock_data *hi3516av100_clk_register(struct platform_device *pdev)
{
	struct hisi_clock_data *clk_data;
	int ret;

	clk_data = hisi_clk_alloc(pdev, HI3516AV100_CRG_NR_CLKS);
	if (!clk_data)
		return ERR_PTR(-ENOMEM);

	ret = hisi_clk_register_fixed_rate(hi3516av100_fixed_rate_clks,
			ARRAY_SIZE(hi3516av100_fixed_rate_clks), clk_data);
	if (ret)
		return ERR_PTR(ret);

	ret = hisi_clk_register_mux(hi3516av100_mux_clks,
			ARRAY_SIZE(hi3516av100_mux_clks), clk_data);
	if (ret)
		goto unregister_fixed_rate;

	ret = hisi_clk_register_fixed_factor(hi3516av100_fixed_factor_clks,
			ARRAY_SIZE(hi3516av100_fixed_factor_clks), clk_data);
	if (ret)
		goto unregister_mux;

	ret = hisi_clk_register_gate(hi3516av100_gate_clks,
			ARRAY_SIZE(hi3516av100_gate_clks), clk_data);
	if (ret)
		goto unregister_fixed_factor;

	ret = of_clk_add_provider(pdev->dev.of_node,
			of_clk_src_onecell_get, &clk_data->clk_data);
	if (ret)
		goto unregister_gate;

	return clk_data;

unregister_gate:
	hisi_clk_unregister_gate(hi3516av100_gate_clks,
			ARRAY_SIZE(hi3516av100_gate_clks), clk_data);
unregister_fixed_factor:
	/* hisi_clk_unregister_fixed_factor() helper not exported; rely on probe cleanup. */
unregister_mux:
	hisi_clk_unregister_mux(hi3516av100_mux_clks,
			ARRAY_SIZE(hi3516av100_mux_clks), clk_data);
unregister_fixed_rate:
	hisi_clk_unregister_fixed_rate(hi3516av100_fixed_rate_clks,
			ARRAY_SIZE(hi3516av100_fixed_rate_clks), clk_data);
	return ERR_PTR(ret);
}

static void hi3516av100_clk_unregister(struct platform_device *pdev)
{
	struct hisi_crg_dev *crg = platform_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);

	hisi_clk_unregister_gate(hi3516av100_gate_clks,
			ARRAY_SIZE(hi3516av100_gate_clks), crg->clk_data);
	hisi_clk_unregister_mux(hi3516av100_mux_clks,
			ARRAY_SIZE(hi3516av100_mux_clks), crg->clk_data);
	hisi_clk_unregister_fixed_rate(hi3516av100_fixed_rate_clks,
			ARRAY_SIZE(hi3516av100_fixed_rate_clks), crg->clk_data);
}

static const struct hisi_crg_funcs hi3516av100_crg_funcs = {
	.register_clks = hi3516av100_clk_register,
	.unregister_clks = hi3516av100_clk_unregister,
};

/* Early clocks for consumers wired up before platform_driver probing
 * (PL011 console, higmac ethernet on av100). The CPU/timer path on
 * av100 uses arch-timer (Cortex-A7), not SP804, so we don't need to
 * front-load the timer mux here. */
static const struct hisi_fixed_rate_clock hi3516av100_crg_early_fixed[] = {
	{ HI3516AV100_SYSAXI_CLK,    "sysapb_early",    NULL, 0, 50000000, },
	{ HI3516AV100_UART0_CLK,     "uart0_early",     NULL, 0, 24000000, },
	{ HI3516AV100_UART1_CLK,     "uart1_early",     NULL, 0, 24000000, },
	{ HI3516AV100_UART2_CLK,     "uart2_early",     NULL, 0, 24000000, },
	{ HI3516AV100_UART3_CLK,     "uart3_early",     NULL, 0, 24000000, },
	{ HI3516AV100_ETH_CLK,       "eth_early",       NULL, 0, 50000000, },
	{ HI3516AV100_ETH_MACIF_CLK, "eth_macif_early", NULL, 0, 50000000, },
};

/* Minimal no-op reset controller — femac and other drivers may request
 * reset_control on probe; without a registered provider, ethernet
 * defers forever. Mirror cv300 with explicit 2-cell xlate so
 * reset_controller_register doesn't force of_reset_n_cells = 1. */

static int hi3516av100_crg_reset_noop(struct reset_controller_dev *rcdev,
				      unsigned long id)
{
	return 0;
}

static const struct reset_control_ops hi3516av100_crg_reset_ops = {
	.reset    = hi3516av100_crg_reset_noop,
	.assert   = hi3516av100_crg_reset_noop,
	.deassert = hi3516av100_crg_reset_noop,
};

static int hi3516av100_crg_reset_xlate(struct reset_controller_dev *rcdev,
				       const struct of_phandle_args *spec)
{
	return (spec->args[0] << 8) | (spec->args[1] & 0xff);
}

static struct reset_controller_dev hi3516av100_crg_reset_rcdev = {
	.ops              = &hi3516av100_crg_reset_ops,
	.nr_resets        = 0x40000,
	.of_reset_n_cells = 2,
	.of_xlate         = hi3516av100_crg_reset_xlate,
};

static void __init hi3516av100_crg_early_init(struct device_node *np)
{
	struct hisi_clock_data *clk_data;

	pr_info("hi3516av100-clk: CLK_OF_DECLARE early init\n");
	clk_data = hisi_clk_init(np, HI3516AV100_CRG_NR_CLKS);
	if (!clk_data) {
		pr_err("hi3516av100-clk: hisi_clk_init FAILED\n");
		return;
	}
	hisi_clk_register_fixed_rate(hi3516av100_crg_early_fixed,
		ARRAY_SIZE(hi3516av100_crg_early_fixed), clk_data);

	hi3516av100_crg_reset_rcdev.of_node = np;
	hi3516av100_crg_reset_rcdev.owner = THIS_MODULE;
	if (reset_controller_register(&hi3516av100_crg_reset_rcdev) < 0)
		pr_err("hi3516av100-clk: reset controller register failed\n");
}
CLK_OF_DECLARE(hi3516av100_clk_early, "hisilicon,hi3516a-clock",
		hi3516av100_crg_early_init);

/* ---------------- sys controller block (sysctrl@20050000) ---------------- */

/* SP804 timer DT references sysctrl-exposed TIME0_0..TIME3_7 clocks
 * (8 timer slots on av100 vs 4 on cv200). Timer init runs at
 * start_kernel — well before platform_driver probing. Register the
 * timer clocks as fixed-rate 3 MHz (the value the vendor mux ultimately
 * selects via timer_mux_p={"3m", "apb"} entry 0). On av100 the arch
 * timer (Cortex-A7 generic) is preferred — these are stubs for the
 * vendor DT references. */
static const struct hisi_fixed_rate_clock hi3516av100_sysctrl_early_fixed[] = {
	{ HI3516AV100_TIME0_0_CLK, "timer0_0_early", NULL, 0, 3000000, },
	{ HI3516AV100_TIME0_1_CLK, "timer0_1_early", NULL, 0, 3000000, },
	{ HI3516AV100_TIME1_2_CLK, "timer1_2_early", NULL, 0, 3000000, },
	{ HI3516AV100_TIME1_3_CLK, "timer1_3_early", NULL, 0, 3000000, },
	{ HI3516AV100_TIME2_4_CLK, "timer2_4_early", NULL, 0, 3000000, },
	{ HI3516AV100_TIME2_5_CLK, "timer2_5_early", NULL, 0, 3000000, },
	{ HI3516AV100_TIME3_6_CLK, "timer3_6_early", NULL, 0, 3000000, },
	{ HI3516AV100_TIME3_7_CLK, "timer3_7_early", NULL, 0, 3000000, },
};

static void __init hi3516av100_sysctrl_early_init(struct device_node *np)
{
	struct hisi_clock_data *clk_data;

	pr_info("hi3516av100-sys: CLK_OF_DECLARE early init\n");
	clk_data = hisi_clk_init(np, HI3516AV100_SC_NR_CLKS);
	if (!clk_data) {
		pr_err("hi3516av100-sys: hisi_clk_init FAILED\n");
		return;
	}
	hisi_clk_register_fixed_rate(hi3516av100_sysctrl_early_fixed,
		ARRAY_SIZE(hi3516av100_sysctrl_early_fixed), clk_data);
}
CLK_OF_DECLARE(hi3516av100_sysctrl_early, "hisilicon,hi3516a-sysctrl",
		hi3516av100_sysctrl_early_init);

/* ---------------- platform driver (post-CLK_OF_DECLARE finalize) -------- */

static const struct of_device_id hi3516av100_crg_match_table[] = {
	{ .compatible = "hisilicon,hi3516a-clock", .data = &hi3516av100_crg_funcs },
	{ }
};
MODULE_DEVICE_TABLE(of, hi3516av100_crg_match_table);

static int hi3516av100_crg_probe(struct platform_device *pdev)
{
	struct hisi_crg_dev *crg;

	crg = devm_kmalloc(&pdev->dev, sizeof(*crg), GFP_KERNEL);
	if (!crg)
		return -ENOMEM;

	crg->funcs = of_device_get_match_data(&pdev->dev);
	if (!crg->funcs)
		return -ENOENT;

	crg->rstc = hisi_reset_init(pdev);
	if (!crg->rstc)
		return -ENOMEM;

	crg->clk_data = crg->funcs->register_clks(pdev);
	if (IS_ERR(crg->clk_data)) {
		hisi_reset_exit(crg->rstc);
		return PTR_ERR(crg->clk_data);
	}

	platform_set_drvdata(pdev, crg);
	return 0;
}

static void hi3516av100_crg_remove(struct platform_device *pdev)
{
	struct hisi_crg_dev *crg = platform_get_drvdata(pdev);

	hisi_reset_exit(crg->rstc);
	crg->funcs->unregister_clks(pdev);
}

static struct platform_driver hi3516av100_crg_driver = {
	.probe  = hi3516av100_crg_probe,
	.remove = hi3516av100_crg_remove,
	.driver = {
		.name = "hi3516av100-crg",
		.of_match_table = hi3516av100_crg_match_table,
	},
};

static int __init hi3516av100_crg_init(void)
{
	return platform_driver_register(&hi3516av100_crg_driver);
}
core_initcall(hi3516av100_crg_init);

static void __exit hi3516av100_crg_exit(void)
{
	platform_driver_unregister(&hi3516av100_crg_driver);
}
module_exit(hi3516av100_crg_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("HiSilicon Hi3516AV100 / Hi3516DV100 CRG Driver");
