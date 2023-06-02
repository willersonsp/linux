/**
	NVT hardware description
	To define NVT platform IO address
	@file      hardware.h
	@ingroup
	@note

	Copyright   Novatek Microelectronics Corp. 2019.  All rights reserved.
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License version 2 as
	published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_PLAT_HARDWARE_H
#define __ASM_ARCH_PLAT_HARDWARE_H

/*
 * ----------------------------------------------------------------------------
 * Interrupts (GIC)
 * ----------------------------------------------------------------------------
 */
#define NVT_GIC_DIST_PHYS_BASE	(0xf1501000)
#define NVT_GIC_CPU_PHYS_BASE	(0xf1502000)

#define NVT_CPU_REG_BASE_PHYS	(NVT_PERIPHERAL_PHYS_BASE + 0x1400000)
#define NVT_CPU_REG_BASE_VIRT	(NVT_PERIPHERAL_VIRT_BASE + 0x1400000)
/*
 * ----------------------------------------------------------------------------
 * Peripheral mapping address
 * ----------------------------------------------------------------------------
 */
#define NVT_PERIPHERAL_PHYS_BASE	(0xf0000000)
#define NVT_PERIPHERAL_VIRT_BASE	IOMEM(0xfD000000)
#define NVT_PERIPHERAL_SIZE		0x2000000

#define NVT_TOP_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0010000)
#define NVT_TOP_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0010000)

#define NVT_CG_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0020000)
#define NVT_CG_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0020000)

#define NVT_PAD_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0030000)
#define NVT_PAD_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0030000)

#define NVT_TIMER_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0040000)
#define NVT_TIMER_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0040000)

#define NVT_GPIO_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0070000)
#define NVT_GPIO_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0070000)

#define NVT_RTC_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0090000)
#define NVT_RTC_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0090000)

#define NVT_I2C1_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0220000)
#define NVT_I2C1_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0220000)

#define NVT_I2C2_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0350000)
#define NVT_I2C2_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0350000)

#define NVT_I2C3_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x03A0000)
#define NVT_I2C3_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x03A0000)

#define NVT_I2C4_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x03B0000)
#define NVT_I2C4_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x03B0000)

#define NVT_I2C5_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x03C0000)
#define NVT_I2C5_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x03C0000)

#define NVT_I2C6_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x03D0000)
#define NVT_I2C6_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x03D0000)

#define NVT_I2C7_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x03E0000)
#define NVT_I2C7_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x03E0000)

#define NVT_SPI1_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0230000)
#define NVT_SPI1_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0230000)

#define NVT_SPI2_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0320000)
#define NVT_SPI2_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0320000)

#define NVT_SPI3_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0340000)
#define NVT_SPI3_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0340000)

#define NVT_SPI4_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0360000)
#define NVT_SPI4_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0360000)

#define NVT_SPI5_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0390000)
#define NVT_SPI5_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0390000)

#define NVT_UART1_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0290000)
#define NVT_UART1_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0290000)

#define NVT_UART2_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0300000)
#define NVT_UART2_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0300000)

#define NVT_UART3_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0310000)
#define NVT_UART3_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0310000)

#define NVT_UART4_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0380000)
#define NVT_UART4_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0380000)

#define NVT_NAND_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0400000)
#define NVT_NAND_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0400000)

#define NVT_SDIO1_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0420000)
#define NVT_SDIO1_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0420000)

#define NVT_SDIO2_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0500000)
#define NVT_SDIO2_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0500000)

#define NVT_SDIO3_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0510000)
#define NVT_SDIO3_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0510000)

#define NVT_USB1_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0600000)
#define NVT_USB1_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0600000)

#define NVT_USB3_CTRL_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x0670000)
#define NVT_USB3_CTRL_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x0670000)

#define NVT_USB3_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x1700000)
#define NVT_USB3_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x1700000)

#define NVT_CC_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x00090000)
#define NVT_CC_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x00090000)

#define NVT_ETH_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x002B0000)
#define NVT_ETH_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x002B0000)

#define NVT_WDT_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x00050000)
#define NVT_WDT_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x00050000)

#define NVT_PWM_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x00210000)
#define NVT_PWM_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x00210000)

#define NVT_TGE_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x00CC0000)
#define NVT_TGE_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x00CC0000)

#define NVT_EFUSE_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x00660000)
#define NVT_EFUSE_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x00660000)

#define NVT_DDR1_PHY_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x00001000)
#define NVT_DDR1_PHY_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x00001000)

#define NVT_DDR2_PHY_BASE_PHYS		(NVT_PERIPHERAL_PHYS_BASE + 0x00101000)
#define NVT_DDR2_PHY_BASE_VIRT		(NVT_PERIPHERAL_VIRT_BASE + 0x00101000)
#endif	/* __ASM_ARCH_PLAT_HARDWARE_H */
