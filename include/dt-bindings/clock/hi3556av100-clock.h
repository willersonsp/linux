/*
 * Copyright (c) 2014 Linaro Ltd.
 * Copyright (c) 2014 Hisilicon Limited.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 */

#ifndef __DTS_HI3556AV100_CLOCK_H
#define __DTS_HI3556AV100_CLOCK_H

/* fixed rate */
#define HI3556AV100_FIXED_2376M     1
#define HI3556AV100_FIXED_1188M     2
#define HI3556AV100_FIXED_594M      3
#define HI3556AV100_FIXED_297M      4
#define HI3556AV100_FIXED_148P5M    5
#define HI3556AV100_FIXED_74P25M    6
#define HI3556AV100_FIXED_792M      7
#define HI3556AV100_FIXED_475M      8
#define HI3556AV100_FIXED_340M      9
#define HI3556AV100_FIXED_72M       10
#define HI3556AV100_FIXED_400M      11
#define HI3556AV100_FIXED_200M      12
#define HI3556AV100_FIXED_54M       13
#define HI3556AV100_FIXED_27M       14
#define HI3556AV100_FIXED_37P125M   15
#define HI3556AV100_FIXED_3000M     16
#define HI3556AV100_FIXED_1500M     17
#define HI3556AV100_FIXED_500M      18
#define HI3556AV100_FIXED_250M      19
#define HI3556AV100_FIXED_125M      20
#define HI3556AV100_FIXED_1000M     21
#define HI3556AV100_FIXED_600M      22
#define HI3556AV100_FIXED_750M      23
#define HI3556AV100_FIXED_150M      24
#define HI3556AV100_FIXED_75M       25
#define HI3556AV100_FIXED_300M      26
#define HI3556AV100_FIXED_60M       27
#define HI3556AV100_FIXED_214M      28
#define HI3556AV100_FIXED_107M      29
#define HI3556AV100_FIXED_100M      30
#define HI3556AV100_FIXED_50M       31
#define HI3556AV100_FIXED_25M       32
#define HI3556AV100_FIXED_24M       33
#define HI3556AV100_FIXED_3M        34
#define HI3556AV100_FIXED_100K      35
#define HI3556AV100_FIXED_400K      36
#define HI3556AV100_FIXED_49P5M     37
#define HI3556AV100_FIXED_99M       38
#define HI3556AV100_FIXED_187P5M    39
#define HI3556AV100_FIXED_198M      40

#define HI3556AV100_I2C0_CLK        41
#define HI3556AV100_I2C1_CLK        42
#define HI3556AV100_I2C2_CLK        43
#define HI3556AV100_I2C3_CLK        44
#define HI3556AV100_I2C4_CLK        45
#define HI3556AV100_I2C5_CLK        46
#define HI3556AV100_I2C6_CLK        47
#define HI3556AV100_I2C7_CLK        48
#define HI3556AV100_I2C8_CLK        49
#define HI3556AV100_I2C9_CLK        50

#define HI3556AV100_SPI0_CLK        51
#define HI3556AV100_SPI1_CLK        52
#define HI3556AV100_SPI2_CLK        53
#define HI3556AV100_SPI3_CLK        54
#define HI3556AV100_SPI4_CLK        55

#define HI3556AV100_DMAC0_APB_CLK   56
#define HI3556AV100_DMAC0_AXI_CLK   57
#define HI3556AV100_DMAC1_APB_CLK   58
#define HI3556AV100_DMAC1_AXI_CLK   59
#define HI3556AV100_VDMAC_CLK       60
/* mux clocks */
#define HI3556AV100_FMC_MUX         64
#define HI3556AV100_SYSAPB_MUX      65
#define HI3556AV100_UART0_MUX       66
#define HI3556AV100_SYSBUS_MUX      67
#define HI3556AV100_A53_1_MUX       68
#define HI3556AV100_MMC0_MUX        69
#define HI3556AV100_MMC1_MUX        70
#define HI3556AV100_MMC2_MUX        71
#define HI3556AV100_UART1_MUX       72
#define HI3556AV100_UART2_MUX       73
#define HI3556AV100_UART3_MUX       74
#define HI3556AV100_UART4_MUX       75
#define HI3556AV100_UART5_MUX       76
#define HI3556AV100_UART6_MUX       77
#define HI3556AV100_UART7_MUX       78
#define HI3556AV100_UART8_MUX       79

/*fixed factor clocks*/

/* gate clocks */
#define HI3556AV100_FMC_CLK         129
#define HI3556AV100_UART0_CLK       153
#define HI3556AV100_UART1_CLK       154
#define HI3556AV100_UART2_CLK       155
#define HI3556AV100_UART3_CLK       156
#define HI3556AV100_UART4_CLK       157
#define HI3556AV100_UART5_CLK       158
#define HI3556AV100_UART6_CLK       159
#define HI3556AV100_UART7_CLK       160
#define HI3556AV100_UART8_CLK       161
#define HI3556AV100_MMC0_CLK        162
#define HI3556AV100_MMC1_CLK        163
#define HI3556AV100_MMC2_CLK        164

#define HI3556AV100_ETH_CLK         192
#define HI3556AV100_ETH_MACIF_CLK   193

/* complex */
#define HI3556AV100_SATA_CLK        194
#define HI3556AV100_USB_CLK         195

/* pll clocks */
#define HI3556AV100_APLL_CLK        250

#define HI3556AV100_NR_CLKS         256
#define HI3556AV100_NR_RSTS         256
#endif  /* __DTS_HI3556AV100_CLOCK_H */
