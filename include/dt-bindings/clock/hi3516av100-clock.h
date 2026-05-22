/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (c) 2016 HiSilicon Technologies Co., Ltd.
 *
 * Hi3516AV100 (and pin-compatible Hi3516DV100) V2A family clock IDs.
 * Kept aligned with the vendor BSP so its 4.9-era DT
 * (arch/arm/boot/dts/hi3516a{.dtsi,-demb.dts}) compiles unchanged
 * against the modern crg-hi3516av100.c driver.
 *
 * V2A generation (Cortex-A7 / ARMv7) — distinct from the V2 cv200/
 * 3518ev20x family which uses ARM926EJ-S. Same CRG layout at
 * 0x20030000 but additional muxes (a7_mux for CPU freq, more fixed
 * rates, APLL for CPU). Mainline port keeps the CPU at the
 * bootloader-configured rate (no APLL programming in this v1).
 */

#ifndef __DTS_HI3516AV100_CLOCK_H
#define __DTS_HI3516AV100_CLOCK_H

/* fixed rate clocks */
#define HI3516AV100_FIXED_3M		1
#define HI3516AV100_FIXED_6M		2
#define HI3516AV100_FIXED_13P5M		3
#define HI3516AV100_FIXED_24M		4
#define HI3516AV100_FIXED_25M		5
#define HI3516AV100_FIXED_27M		6
#define HI3516AV100_FIXED_37P125M	7
#define HI3516AV100_FIXED_50M		8
#define HI3516AV100_FIXED_74P25M	9
#define HI3516AV100_FIXED_75M		10
#define HI3516AV100_FIXED_99M		11
#define HI3516AV100_FIXED_100M		12
#define HI3516AV100_FIXED_125M		13
#define HI3516AV100_FIXED_145M		14
#define HI3516AV100_FIXED_148P5M	15
#define HI3516AV100_FIXED_150M		16
#define HI3516AV100_FIXED_194M		17
#define HI3516AV100_FIXED_198M		18
#define HI3516AV100_FIXED_200M		19
#define HI3516AV100_FIXED_229M		20
#define HI3516AV100_FIXED_237M		21
#define HI3516AV100_FIXED_242M		22
#define HI3516AV100_FIXED_250M		23
#define HI3516AV100_FIXED_297M		24
#define HI3516AV100_FIXED_300M		25
#define HI3516AV100_FIXED_333M		26
#define HI3516AV100_FIXED_400M		27
#define HI3516AV100_FIXED_500M		28
#define HI3516AV100_FIXED_594M		29
#define HI3516AV100_FIXED_600M		30
#define HI3516AV100_FIXED_750M		31
#define HI3516AV100_FIXED_900M		32
#define HI3516AV100_FIXED_1000M		33
#define HI3516AV100_FIXED_1188M		34

/* mux clocks (parent of gates / dividers) */
#define HI3516AV100_SYSAXI_CLK		40
#define HI3516AV100_SNOR_MUX		41
#define HI3516AV100_SNAND_MUX		42
#define HI3516AV100_NAND_MUX		43
#define HI3516AV100_UART_MUX		44
#define HI3516AV100_ETH_PHY_MUX		45
#define HI3516AV100_A7_MUX		46
#define HI3516AV100_MMC0_MUX		47
#define HI3516AV100_MMC1_MUX		48
#define HI3516AV100_USB2_CTRL_UTMI0_REQ	49
#define HI3516AV100_USB2_HRST_REQ	50

/* gate clocks */
#define HI3516AV100_SNOR_CLK		60
#define HI3516AV100_SNAND_CLK		61
#define HI3516AV100_NAND_CLK		62
#define HI3516AV100_UART0_CLK		63
#define HI3516AV100_UART1_CLK		64
#define HI3516AV100_UART2_CLK		65
#define HI3516AV100_UART3_CLK		66
#define HI3516AV100_ETH_CLK		67
#define HI3516AV100_ETH_MACIF_CLK	68
#define HI3516AV100_MMC0_CLK		69
#define HI3516AV100_MMC1_CLK		70
#define HI3516AV100_SPI0_CLK		71
#define HI3516AV100_SPI1_CLK		72
#define HI3516AV100_DMAC_CLK		73

/* pll clock — vendor BSP programs APLL for CPU rate; mainline port
 * leaves it at U-Boot-configured rate and exposes the ID as a stub
 * fixed-rate so the vendor DT compiles. */
#define HI3516AV100_APLL_CLK		80

#define HI3516AV100_CRG_NR_CLKS		96

/* sysctrl (timer mux) clocks — exported via the system-controller provider */
#define HI3516AV100_TIME0_0_CLK		1
#define HI3516AV100_TIME0_1_CLK		2
#define HI3516AV100_TIME1_2_CLK		3
#define HI3516AV100_TIME1_3_CLK		4
#define HI3516AV100_TIME2_4_CLK		5
#define HI3516AV100_TIME2_5_CLK		6
#define HI3516AV100_TIME3_6_CLK		7
#define HI3516AV100_TIME3_7_CLK		8

#define HI3516AV100_SC_NR_CLKS		12

#endif	/* __DTS_HI3516AV100_CLOCK_H */
