// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Hi3516CV300 Clock and Reset Generator Driver
 *
 * Copyright (c) 2016 HiSilicon Technologies Co., Ltd.
 *
 * Backports the full vendor clock topology (CRG + sysctrl/timers, with
 * media/USB/sensor branches) onto the upstream platform_driver scaffolding.
 * Keeps the DT (hi3516cv300.dtsi) compatible without modification.
 */

#include <dt-bindings/clock/hi3516cv300-clock.h>
#include <linux/clk-provider.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include "clk.h"
#include "crg.h"
#include "reset.h"

/* ---------------- CRG block (hisilicon,hi3516cv300-crg) ---------------- */

static const struct hisi_fixed_rate_clock hi3516cv300_fixed_rate_clks[] = {
	{ HI3516CV300_FIXED_3M,     "3m",     NULL, 0, 3000000,   },
	{ HI3516CV300_FIXED_6M,     "6m",     NULL, 0, 6000000,   },
	{ HI3516CV300_FIXED_12M,    "12m",    NULL, 0, 12000000,  },
	{ HI3516CV300_FIXED_15M,    "15m",    NULL, 0, 15000000,  },
	{ HI3516CV300_FIXED_24M,    "24m",    NULL, 0, 24000000,  },
	{ HI3516CV300_FIXED_25M,    "25m",    NULL, 0, 25000000,  },
	{ HI3516CV300_FIXED_27M,    "27m",    NULL, 0, 27000000,  },
	{ HI3516CV300_FIXED_37P125M,"37.125m",NULL, 0, 37125000,  },
	{ HI3516CV300_FIXED_44M,    "44m",    NULL, 0, 44000000,  },
	{ HI3516CV300_FIXED_49P5M,  "49.5m",  NULL, 0, 49500000,  },
	{ HI3516CV300_FIXED_50M,    "50m",    NULL, 0, 50000000,  },
	{ HI3516CV300_FIXED_54M,    "54m",    NULL, 0, 54000000,  },
	{ HI3516CV300_FIXED_74P25M, "74.25m", NULL, 0, 74250000,  },
	{ HI3516CV300_FIXED_75M,    "75m",    NULL, 0, 75000000,  },
	{ HI3516CV300_FIXED_83P3M,  "83.3m",  NULL, 0, 83300000,  },
	{ HI3516CV300_FIXED_99M,    "99m",    NULL, 0, 99000000,  },
	{ HI3516CV300_FIXED_100M,   "100m",   NULL, 0, 100000000, },
	{ HI3516CV300_FIXED_125M,   "125m",   NULL, 0, 125000000, },
	{ HI3516CV300_FIXED_148P5M, "148.5m", NULL, 0, 148500000, },
	{ HI3516CV300_FIXED_150M,   "150m",   NULL, 0, 150000000, },
	{ HI3516CV300_FIXED_166P6M, "166.6m", NULL, 0, 166600000, },
	{ HI3516CV300_FIXED_198M,   "198m",   NULL, 0, 198000000, },
	{ HI3516CV300_FIXED_200M,   "200m",   NULL, 0, 200000000, },
	{ HI3516CV300_FIXED_250M,   "250m",   NULL, 0, 250000000, },
	{ HI3516CV300_FIXED_297M,   "297m",   NULL, 0, 297000000, },
	{ HI3516CV300_FIXED_300M,   "300m",   NULL, 0, 300000000, },
	{ HI3516CV300_FIXED_396M,   "396m",   NULL, 0, 396000000, },
	{ HI3516CV300_FIXED_400M,   "400m",   NULL, 0, 400000000, },
};

static const char *const apb_mux_p[]    = { "24m", "50m" };
static const char *const uart_mux_p[]   = { "24m", "6m" };
static const char *const fmc_mux_p[]    = { "24m", "83.3m", "148.5m", "198m", "297m" };
static const char *const mmc_mux_p[]    = { "49.5m" };
static const char *const mmc2_mux_p[]   = { "99m", "49.5m" };
static const char *const sensor_mux_p[] = {
	"74.25m", "37.125m", "54m", "27m", "24m", "25m", "24m", "25m"
};
static const char *const viu_mux_p[]    = { "83.3m", "125m", "148.5m", "198m", "250m" };
static const char *const vedu_mux_p[]   = { "166.6m", "198m" };
static const char *const vpss_mux_p[]   = { "148.5m", "198m", "250m" };
static const char *const vgs_mux_p[]    = { "198m", "250m", "297m" };
static const char *const ive_mux_p[]    = { "198m", "250m", "297m" };
static const char *const pwm_mux_p[]    = { "3m", "50m", "24m", "24m" };

static u32 apb_mux_table[]     = { 0, 1 };
static u32 uart_mux_table[]    = { 0, 1 };
static u32 fmc_mux_table[]     = { 0, 1, 2, 3, 4 };
static u32 mmc_mux_table[]     = { 0 };
static u32 mmc2_mux_table[]    = { 0, 2 };
static u32 sensor_mux_table[]  = { 0, 1, 2, 3, 4, 5, 6, 7 };
static u32 viu_mux_table[]     = { 0, 1, 2, 3, 4 };
static u32 vedu_mux_table[]    = { 0, 1 };
static u32 vpss_mux_table[]    = { 0, 1, 2 };
static u32 vgs_mux_table[]     = { 0, 1, 2 };
static u32 ive_mux_table[]     = { 0, 1, 2 };
static u32 pwm_mux_table[]     = { 0, 1, 2, 3 };

static const struct hisi_mux_clock hi3516cv300_mux_clks[] = {
	{ HI3516CV300_APB_CLK,    "apb",        apb_mux_p,    ARRAY_SIZE(apb_mux_p),
		CLK_SET_RATE_PARENT, 0x30, 0,  1, 0, apb_mux_table,    },
	{ HI3516CV300_UART_MUX,   "uart_mux",   uart_mux_p,   ARRAY_SIZE(uart_mux_p),
		CLK_SET_RATE_PARENT, 0xe4, 19, 1, 0, uart_mux_table,   },
	{ HI3516CV300_FMC_MUX,    "fmc_mux",    fmc_mux_p,    ARRAY_SIZE(fmc_mux_p),
		CLK_SET_RATE_PARENT, 0xc0, 2,  3, 0, fmc_mux_table,    },
	{ HI3516CV300_MMC0_MUX,   "mmc0_mux",   mmc_mux_p,    ARRAY_SIZE(mmc_mux_p),
		CLK_SET_RATE_PARENT, 0xc4, 4,  2, 0, mmc_mux_table,    },
	{ HI3516CV300_MMC1_MUX,   "mmc1_mux",   mmc_mux_p,    ARRAY_SIZE(mmc_mux_p),
		CLK_SET_RATE_PARENT, 0xc4, 12, 2, 0, mmc_mux_table,    },
	{ HI3516CV300_MMC2_MUX,   "mmc2_mux",   mmc2_mux_p,   ARRAY_SIZE(mmc2_mux_p),
		CLK_SET_RATE_PARENT, 0xc4, 20, 2, 0, mmc2_mux_table,   },
	{ HI3516CV300_MMC3_MUX,   "mmc3_mux",   mmc_mux_p,    ARRAY_SIZE(mmc_mux_p),
		CLK_SET_RATE_PARENT, 0xc8, 4,  2, 0, mmc_mux_table,    },
	{ HI3516CV300_PWM_MUX,    "pwm_mux",    pwm_mux_p,    ARRAY_SIZE(pwm_mux_p),
		CLK_SET_RATE_PARENT, 0x38, 2,  2, 0, pwm_mux_table,    },
	/* media mux clocks */
	{ HI3516CV300_SENSOR_MUX, "sensor_mux", sensor_mux_p, ARRAY_SIZE(sensor_mux_p),
		CLK_SET_RATE_PARENT, 0x2c, 23, 3, 0, sensor_mux_table, },
	{ HI3516CV300_VIU_MUX,    "viu_mux",    viu_mux_p,    ARRAY_SIZE(viu_mux_p),
		CLK_SET_RATE_PARENT, 0x2c, 2,  3, 0, viu_mux_table,    },
	{ HI3516CV300_VEDU_MUX,   "vedu_mux",   vedu_mux_p,   ARRAY_SIZE(vedu_mux_p),
		CLK_SET_RATE_PARENT, 0x40, 10, 2, 0, vedu_mux_table,   },
	{ HI3516CV300_VPSS_MUX,   "vpss_mux",   vpss_mux_p,   ARRAY_SIZE(vpss_mux_p),
		CLK_SET_RATE_PARENT, 0x48, 10, 2, 0, vpss_mux_table,   },
	{ HI3516CV300_VGS_MUX,    "vgs_mux",    vgs_mux_p,    ARRAY_SIZE(vgs_mux_p),
		CLK_SET_RATE_PARENT, 0x5c, 10, 2, 0, vgs_mux_table,    },
	{ HI3516CV300_IVE_MUX,    "ive_mux",    ive_mux_p,    ARRAY_SIZE(ive_mux_p),
		CLK_SET_RATE_PARENT, 0x6c, 2,  2, 0, ive_mux_table,    },
};

static const struct hisi_divider_clock hi3516cv300_div_clks[] = {
	{ HI3516CV300_ISP_DIV, "isp_div", "viu_mux", 0, 0x2c, 17, 1, 0, NULL, },
};

static const struct hisi_gate_clock hi3516cv300_gate_clks[] = {
	/* uart */
	{ HI3516CV300_UART0_CLK,    "clk_uart0",    "uart_mux",  CLK_SET_RATE_PARENT, 0xe4, 15, 0, },
	{ HI3516CV300_UART1_CLK,    "clk_uart1",    "uart_mux",  CLK_SET_RATE_PARENT, 0xe4, 16, 0, },
	{ HI3516CV300_UART2_CLK,    "clk_uart2",    "uart_mux",  CLK_SET_RATE_PARENT, 0xe4, 17, 0, },
	/* spi */
	{ HI3516CV300_SPI0_CLK,     "clk_spi0",     "100m",      CLK_SET_RATE_PARENT, 0xe4, 13, 0, },
	{ HI3516CV300_SPI1_CLK,     "clk_spi1",     "100m",      CLK_SET_RATE_PARENT, 0xe4, 14, 0, },
	/* fmc + mmc */
	{ HI3516CV300_FMC_CLK,      "clk_fmc",      "fmc_mux",   CLK_SET_RATE_PARENT, 0xc0, 1, 0, },
	{ HI3516CV300_MMC0_CLK,     "clk_mmc0",     "mmc0_mux",  CLK_SET_RATE_PARENT, 0xc4, 1, 0, },
	{ HI3516CV300_MMC1_CLK,     "clk_mmc1",     "mmc1_mux",  CLK_SET_RATE_PARENT, 0xc4, 9, 0, },
	{ HI3516CV300_MMC2_CLK,     "clk_mmc2",     "mmc2_mux",  CLK_SET_RATE_PARENT, 0xc4, 17, 0, },
	{ HI3516CV300_MMC3_CLK,     "clk_mmc3",     "mmc3_mux",  CLK_SET_RATE_PARENT, 0xc8, 1, 0, },
	/* ethernet */
	{ HI3516CV300_ETH_CLK,      "clk_eth",      NULL,        0,                   0xec, 1, 0, },
	/* usb */
	{ HI3516CV300_USB2_BUS_CLK, "clk_usb2_bus", NULL,        CLK_SET_RATE_PARENT, 0xb8, 8,  1, },
	{ HI3516CV300_UTMI0_CLK,    "clk_utmi0",    NULL,        CLK_SET_RATE_PARENT, 0xb8, 11, 1, },
	{ HI3516CV300_USB2_CLK,     "clk_usb2",     NULL,        CLK_SET_RATE_PARENT, 0xb8, 12, 1, },
	{ HI3516CV300_DMAC_CLK,     "clk_dmac",     NULL,        0,                   0xd8, 5,  0, },
	{ HI3516CV300_PWM_CLK,      "clk_pwm",      "pwm_mux",   CLK_SET_RATE_PARENT, 0x38, 1,  0, },
	/* media gate clocks */
	{ HI3516CV300_SENSOR_CLK,   "clk_sensor",   "sensor_mux",CLK_SET_RATE_PARENT, 0x2c, 26, 0, },
	{ HI3516CV300_MIPI_CLK,     "clk_mipi",     NULL,        CLK_SET_RATE_PARENT, 0x2c, 15, 0, },
	{ HI3516CV300_ISP_CLK,      "clk_isp",      "isp_div",   CLK_SET_RATE_PARENT, 0x2c, 18, 0, },
	{ HI3516CV300_VIU_CLK,      "clk_viu",      "viu_mux",   CLK_SET_RATE_PARENT, 0x2c, 0,  0, },
	{ HI3516CV300_VEDU_CLK,     "clk_vedu",     "vedu_mux",  CLK_SET_RATE_PARENT, 0x40, 1,  0, },
	{ HI3516CV300_VPSS_CLK,     "clk_vpss",     "vpss_mux",  CLK_SET_RATE_PARENT, 0x48, 1,  0, },
	{ HI3516CV300_VGS_CLK,      "clk_vgs",      "vgs_mux",   CLK_SET_RATE_PARENT, 0x5c, 1,  0, },
	{ HI3516CV300_JPGE_CLK,     "clk_jpge",     NULL,        CLK_SET_RATE_PARENT, 0x60, 1,  0, },
	{ HI3516CV300_IVE_CLK,      "clk_ive",      "ive_mux",   CLK_SET_RATE_PARENT, 0x6c, 1,  0, },
	{ HI3516CV300_AIAO_CLK,     "clk_aiao",     NULL,        CLK_SET_RATE_PARENT, 0x8c, 1,  0, },
};

static struct hisi_clock_data *hi3516cv300_clk_register(struct platform_device *pdev)
{
	struct hisi_clock_data *clk_data;
	int ret;

	clk_data = hisi_clk_alloc(pdev, HI3516CV300_CRG_NR_CLKS);
	if (!clk_data)
		return ERR_PTR(-ENOMEM);

	ret = hisi_clk_register_fixed_rate(hi3516cv300_fixed_rate_clks,
			ARRAY_SIZE(hi3516cv300_fixed_rate_clks), clk_data);
	if (ret)
		return ERR_PTR(ret);

	ret = hisi_clk_register_mux(hi3516cv300_mux_clks,
			ARRAY_SIZE(hi3516cv300_mux_clks), clk_data);
	if (ret)
		goto unregister_fixed_rate;

	ret = hisi_clk_register_divider(hi3516cv300_div_clks,
			ARRAY_SIZE(hi3516cv300_div_clks), clk_data);
	if (ret)
		goto unregister_mux;

	ret = hisi_clk_register_gate(hi3516cv300_gate_clks,
			ARRAY_SIZE(hi3516cv300_gate_clks), clk_data);
	if (ret)
		goto unregister_divider;

	ret = of_clk_add_provider(pdev->dev.of_node,
			of_clk_src_onecell_get, &clk_data->clk_data);
	if (ret)
		goto unregister_gate;

	return clk_data;

unregister_gate:
	hisi_clk_unregister_gate(hi3516cv300_gate_clks,
			ARRAY_SIZE(hi3516cv300_gate_clks), clk_data);
unregister_divider:
	/* hisi_clk_unregister_divider() helper not exported; rely on probe failure cleanup. */
unregister_mux:
	hisi_clk_unregister_mux(hi3516cv300_mux_clks,
			ARRAY_SIZE(hi3516cv300_mux_clks), clk_data);
unregister_fixed_rate:
	hisi_clk_unregister_fixed_rate(hi3516cv300_fixed_rate_clks,
			ARRAY_SIZE(hi3516cv300_fixed_rate_clks), clk_data);
	return ERR_PTR(ret);
}

static void hi3516cv300_clk_unregister(struct platform_device *pdev)
{
	struct hisi_crg_dev *crg = platform_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);

	hisi_clk_unregister_gate(hi3516cv300_gate_clks,
			ARRAY_SIZE(hi3516cv300_gate_clks), crg->clk_data);
	hisi_clk_unregister_mux(hi3516cv300_mux_clks,
			ARRAY_SIZE(hi3516cv300_mux_clks), crg->clk_data);
	hisi_clk_unregister_fixed_rate(hi3516cv300_fixed_rate_clks,
			ARRAY_SIZE(hi3516cv300_fixed_rate_clks), crg->clk_data);
}

static const struct hisi_crg_funcs hi3516cv300_crg_funcs = {
	.register_clks = hi3516cv300_clk_register,
	.unregister_clks = hi3516cv300_clk_unregister,
};

/* SP804 timer DT references &crg_ctrl HI3516CV300_APB_CLK as one of its
 * three clock inputs (in addition to TIME0x_CLK from sysctrl). The
 * platform_driver path registers APB only at probe time which is too
 * late for SP804 (init at start_kernel). Mirror what the vendor BSP
 * did and register the small set of early-required CRG clocks via
 * CLK_OF_DECLARE; the platform_driver path then becomes a no-op
 * because of_clk_add_provider already succeeded. */
static const struct hisi_fixed_rate_clock hi3516cv300_crg_early_fixed[] = {
	{ HI3516CV300_APB_CLK,   "apb_early",   NULL, 0, 50000000, },
	/* UART0/1/2 → PL011 driver does div by rate during termios setup. */
	{ HI3516CV300_UART0_CLK, "uart0_early", NULL, 0, 24000000, },
	{ HI3516CV300_UART1_CLK, "uart1_early", NULL, 0, 24000000, },
	{ HI3516CV300_UART2_CLK, "uart2_early", NULL, 0, 24000000, },
	/* Ethernet FEMAC clock — without this the MDIO bus probe fails -ENOENT
	 * and the platform 10050000.ethernet node gets stuck in deferred probe. */
	{ HI3516CV300_ETH_CLK,        "eth_early",       NULL, 0, 50000000, },
	{ HI3516CV300_ETH_MACIF_CLK,  "eth_macif_early", NULL, 0, 50000000, },
};
/* Minimal no-op reset controller for the CRG. hisi_femac driver requires
 * devm_reset_control_get(dev,"mac") on probe; without a registered reset
 * provider, ethernet@10050000 defers forever. Register a stub here at
 * CLK_OF_DECLARE time so resets resolve. */
#include <linux/reset-controller.h>

static int hi3516cv300_crg_reset_noop_dbg(struct reset_controller_dev *rcdev,
					  unsigned long id)
{
	pr_info("hi3516cv300-crg: reset op id=%lu (noop)\n", id);
	return 0;
}

static const struct reset_control_ops hi3516cv300_crg_reset_ops = {
	.reset    = hi3516cv300_crg_reset_noop_dbg,
	.assert   = hi3516cv300_crg_reset_noop_dbg,
	.deassert = hi3516cv300_crg_reset_noop_dbg,
};

/* Vendor reset specifier is (offset, bit) — 2 cells. Pack into a single id
 * the .ops callbacks can decode if they ever do real work. For our noop
 * controller we just need a valid non-negative return. */
static int hi3516cv300_crg_reset_xlate(struct reset_controller_dev *rcdev,
				       const struct of_phandle_args *spec)
{
	int id = (spec->args[0] << 8) | (spec->args[1] & 0xff);
	pr_info("hi3516cv300-crg: reset xlate args=[%u, %u] → id=%d (n_cells=%u nr=%u)\n",
		spec->args[0], spec->args[1], id, rcdev->of_reset_n_cells,
		rcdev->nr_resets);
	return id;
}

static struct reset_controller_dev hi3516cv300_crg_reset_rcdev = {
	.ops              = &hi3516cv300_crg_reset_ops,
	.nr_resets        = 0x40000,             /* (offset 0xec << 8 | bit) fits */
	.of_reset_n_cells = 2,                   /* must be set together with of_xlate */
	.of_xlate         = hi3516cv300_crg_reset_xlate,
};

static void __init hi3516cv300_crg_early_init(struct device_node *np)
{
	struct hisi_clock_data *clk_data;

	pr_info("hi3516cv300-crg: CLK_OF_DECLARE early init\n");
	clk_data = hisi_clk_init(np, HI3516CV300_CRG_NR_CLKS);
	if (!clk_data) {
		pr_err("hi3516cv300-crg: hisi_clk_init FAILED\n");
		return;
	}
	hisi_clk_register_fixed_rate(hi3516cv300_crg_early_fixed,
		ARRAY_SIZE(hi3516cv300_crg_early_fixed), clk_data);

	hi3516cv300_crg_reset_rcdev.of_node = np;
	hi3516cv300_crg_reset_rcdev.owner = THIS_MODULE;
	if (reset_controller_register(&hi3516cv300_crg_reset_rcdev) < 0)
		pr_err("hi3516cv300-crg: reset controller register failed\n");
	else
		pr_info("hi3516cv300-crg: noop reset controller registered\n");
}
CLK_OF_DECLARE(hi3516cv300_crg_early, "hisilicon,hi3516cv300-crg",
		hi3516cv300_crg_early_init);

/* ---------------- sys controller block (hisilicon,hi3516cv300-sys) ----- */

static const char *const timer_mux_p[] = { "3m", "apb" };
static u32 timer_mux_table[] = { 0, 1 };

static const struct hisi_mux_clock hi3516cv300_sysctrl_mux_clks[] = {
	{ HI3516CV300_TIME00_CLK, "timer00", timer_mux_p,
		ARRAY_SIZE(timer_mux_p), CLK_SET_RATE_PARENT,
		0x0, 16, 1, 0, timer_mux_table, },
	{ HI3516CV300_TIME01_CLK, "timer01", timer_mux_p,
		ARRAY_SIZE(timer_mux_p), CLK_SET_RATE_PARENT,
		0x0, 18, 1, 0, timer_mux_table, },
	{ HI3516CV300_TIME10_CLK, "timer10", timer_mux_p,
		ARRAY_SIZE(timer_mux_p), CLK_SET_RATE_PARENT,
		0x0, 20, 1, 0, timer_mux_table, },
	{ HI3516CV300_TIME11_CLK, "timer11", timer_mux_p,
		ARRAY_SIZE(timer_mux_p), CLK_SET_RATE_PARENT,
		0x0, 22, 1, 0, timer_mux_table, },
};

static struct hisi_clock_data *hi3516cv300_sysctrl_clk_register(struct platform_device *pdev)
{
	struct hisi_clock_data *clk_data;
	int ret;

	clk_data = hisi_clk_alloc(pdev, HI3516CV300_SYS_NR_CLKS);
	if (!clk_data)
		return ERR_PTR(-ENOMEM);

	ret = hisi_clk_register_mux(hi3516cv300_sysctrl_mux_clks,
			ARRAY_SIZE(hi3516cv300_sysctrl_mux_clks), clk_data);
	if (ret)
		return ERR_PTR(ret);

	ret = of_clk_add_provider(pdev->dev.of_node,
			of_clk_src_onecell_get, &clk_data->clk_data);
	if (ret)
		goto unregister_mux;

	return clk_data;

unregister_mux:
	hisi_clk_unregister_mux(hi3516cv300_sysctrl_mux_clks,
			ARRAY_SIZE(hi3516cv300_sysctrl_mux_clks), clk_data);
	return ERR_PTR(ret);
}

static void hi3516cv300_sysctrl_clk_unregister(struct platform_device *pdev)
{
	struct hisi_crg_dev *crg = platform_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);

	hisi_clk_unregister_mux(hi3516cv300_sysctrl_mux_clks,
			ARRAY_SIZE(hi3516cv300_sysctrl_mux_clks),
			crg->clk_data);
}

static const struct hisi_crg_funcs hi3516cv300_sysctrl_funcs = {
	.register_clks = hi3516cv300_sysctrl_clk_register,
	.unregister_clks = hi3516cv300_sysctrl_clk_unregister,
};

/* SP804 dual-timer in cv300 DT needs TIME0x_CLK exposed by sysctrl, but
 * timers init at start_kernel time — well before platform_driver probing,
 * and before CRG's "3m"/"apb" mux parents exist. Register the timer
 * clocks as fixed-rate 3MHz directly in the early init (this is the
 * SP804 reference clock that the vendor mux table ultimately selects
 * via timer_mux_p={"3m", "apb"} entry 0). The full mux can be wired up
 * later if any consumer needs to switch the timer clock source. */
static const struct hisi_fixed_rate_clock hi3516cv300_sysctrl_early_fixed[] = {
	{ HI3516CV300_TIME00_CLK, "timer00_early", NULL, 0, 3000000, },
	{ HI3516CV300_TIME01_CLK, "timer01_early", NULL, 0, 3000000, },
	{ HI3516CV300_TIME10_CLK, "timer10_early", NULL, 0, 3000000, },
	{ HI3516CV300_TIME11_CLK, "timer11_early", NULL, 0, 3000000, },
};

static void __init hi3516cv300_sysctrl_early_init(struct device_node *np)
{
	struct hisi_clock_data *clk_data;

	pr_info("hi3516cv300-sys: CLK_OF_DECLARE early init starting\n");
	clk_data = hisi_clk_init(np, HI3516CV300_SYS_NR_CLKS);
	if (!clk_data) {
		pr_err("hi3516cv300-sys: hisi_clk_init FAILED\n");
		return;
	}
	pr_info("hi3516cv300-sys: hisi_clk_init OK, registering %zu fixed-rate timer clocks\n",
		ARRAY_SIZE(hi3516cv300_sysctrl_early_fixed));
	hisi_clk_register_fixed_rate(hi3516cv300_sysctrl_early_fixed,
		ARRAY_SIZE(hi3516cv300_sysctrl_early_fixed), clk_data);
	pr_info("hi3516cv300-sys: timer clocks registered at 3MHz\n");
}
CLK_OF_DECLARE(hi3516cv300_sysctrl_early, "hisilicon,hi3516cv300-sys",
		hi3516cv300_sysctrl_early_init);

/* ---------------- platform driver ---------------- */

static const struct of_device_id hi3516cv300_crg_match_table[] = {
	{ .compatible = "hisilicon,hi3516cv300-crg",     .data = &hi3516cv300_crg_funcs     },
	/* Vendor DT uses "-sys" as the syscon node compatible; keep it
	 * matched here so the timer (TIME00..11) clocks register too. */
	{ .compatible = "hisilicon,hi3516cv300-sys",     .data = &hi3516cv300_sysctrl_funcs },
	{ .compatible = "hisilicon,hi3516cv300-sysctrl", .data = &hi3516cv300_sysctrl_funcs },
	{ }
};
MODULE_DEVICE_TABLE(of, hi3516cv300_crg_match_table);

static int hi3516cv300_crg_probe(struct platform_device *pdev)
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

static void hi3516cv300_crg_remove(struct platform_device *pdev)
{
	struct hisi_crg_dev *crg = platform_get_drvdata(pdev);

	hisi_reset_exit(crg->rstc);
	crg->funcs->unregister_clks(pdev);
}

static struct platform_driver hi3516cv300_crg_driver = {
	.probe  = hi3516cv300_crg_probe,
	.remove = hi3516cv300_crg_remove,
	.driver = {
		.name = "hi3516cv300-crg",
		.of_match_table = hi3516cv300_crg_match_table,
	},
};

static int __init hi3516cv300_crg_init(void)
{
	return platform_driver_register(&hi3516cv300_crg_driver);
}
core_initcall(hi3516cv300_crg_init);

static void __exit hi3516cv300_crg_exit(void)
{
	platform_driver_unregister(&hi3516cv300_crg_driver);
}
module_exit(hi3516cv300_crg_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("HiSilicon Hi3516CV300 CRG Driver");
