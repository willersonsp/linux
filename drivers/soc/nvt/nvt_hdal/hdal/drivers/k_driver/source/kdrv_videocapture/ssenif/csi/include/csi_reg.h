/*
    MIPI CSI Controller register header

    MIPI CSI Controller register header

    @file       csi_reg.h
    @ingroup    mIDrvIO_CSI
    @note       Nothing

    Copyright   Novatek Microelectronics Corp. 2012.  All rights reserved.
*/
#ifndef __CSI_REG_H__
#define __CSI_REG_H__

#ifdef __KERNEL__
#include <mach/rcw_macro.h>
#include "kwrap/type.h"
#else
#if defined(__FREERTOS)
#include "rcw_macro.h"
#include "kwrap/type.h"
#else
#include "DrvCommon.h"
#endif
#endif


// 0x00 MIPI-CSI Control Register 0
REGDEF_OFFSET(CSI_CTRL0_REG, 0x00)
REGDEF_BEGIN(CSI_CTRL0_REG)
REGDEF_BIT(CSI_EN, 1)
REGDEF_BIT(EN_SEL, 1)
REGDEF_BIT(FIFO_RST, 1)
REGDEF_BIT(, 1)
REGDEF_BIT(EN_DESKEW, 1)
REGDEF_BIT(, 11)
REGDEF_BIT(DBG_SEL, 5)
REGDEF_BIT(, 7)
REGDEF_BIT(TEST28, 1)
REGDEF_BIT(TEST29, 1)
REGDEF_BIT(TEST30, 1)
REGDEF_BIT(CSI_DBGMUX_EN, 1)
REGDEF_END(CSI_CTRL0_REG)


// 0x04 MIPI-CSI Control Register 1
REGDEF_OFFSET(CSI_CTRL1_REG, 0x04)
REGDEF_BEGIN(CSI_CTRL1_REG)
REGDEF_BIT(LPKT_AUTO_EN, 1)
REGDEF_BIT(LPKT_MANUAL_EN, 1)
REGDEF_BIT(LPKT_MANUAL2_EN, 1)
REGDEF_BIT(LPKT_MANUAL3_EN, 1)
REGDEF_BIT(, 4)
REGDEF_BIT(LINE_SYNC_METHOD, 1)
REGDEF_BIT(VD_GEN_WITH_HD, 1)
REGDEF_BIT(CH_ID_MODE, 1)
REGDEF_BIT(ROUND_EN, 1)
REGDEF_BIT(VIRTUAL_ID, 4)
REGDEF_BIT(DLANE_NUM, 2)
REGDEF_BIT(VD_ISSUE_TWO, 2)
REGDEF_BIT(MAN_DEPACK, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(MANUAL_DI, 6)
REGDEF_BIT(HD_GATING, 1)
REGDEF_BIT(, 1)
REGDEF_END(CSI_CTRL1_REG)

// 0x08 MIPI-CSI Control Register 2
REGDEF_OFFSET(CSI_CTRL2_REG, 0x08)
REGDEF_BEGIN(CSI_CTRL2_REG)
REGDEF_BIT(MANUAL_DI2, 6)
REGDEF_BIT(, 2)
REGDEF_BIT(MANUAL_DI3, 6)
REGDEF_BIT(, 2)
REGDEF_BIT(MAN_DEPACK2, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(MAN_DEPACK3, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(VIRTUAL_ID2, 4)
REGDEF_BIT(DISABLE_SRC, 2)
REGDEF_BIT(, 2)
REGDEF_END(CSI_CTRL2_REG)


// 0x0C MIPI-CSI Control Counter Register 0
REGDEF_OFFSET(CSI_COUNT_REG, 0x0C)
REGDEF_BEGIN(CSI_COUNT_REG)
REGDEF_BIT(FRMEND_LINE_CNT, 16)
REGDEF_BIT(, 16)
REGDEF_END(CSI_COUNT_REG)


// 0x10 MIPI-CSI interrupt Enable Register 0
REGDEF_OFFSET(CSI_INTEN0_REG, 0x10)
REGDEF_BEGIN(CSI_INTEN0_REG)
REGDEF_BIT(ECC_ERR, 1)
REGDEF_BIT(CRC_ERR, 1)
REGDEF_BIT(INVALID_DI, 1)
REGDEF_BIT(ECC_CORRECTED, 1)
REGDEF_BIT(FS_SYNC_ERR, 1)
REGDEF_BIT(LS_SYNC_ERR, 1)
REGDEF_BIT(FS_GOT, 1)
REGDEF_BIT(FE_GOT, 1)
REGDEF_BIT(GEN_GOT, 1)
REGDEF_BIT(DATA_LT_WC, 1)
REGDEF_BIT(LS_GOT, 1)
REGDEF_BIT(, 1)
REGDEF_BIT(SOT_SYNC_ERR0, 1)
REGDEF_BIT(SOT_SYNC_ERR1, 1)
REGDEF_BIT(SOT_SYNC_ERR2, 1)
REGDEF_BIT(SOT_SYNC_ERR3, 1)
REGDEF_BIT(ESC_RDY0, 1)
REGDEF_BIT(ESC_RDY1, 1)
REGDEF_BIT(ESC_RDY2, 1)
REGDEF_BIT(ESC_RDY3, 1)
REGDEF_BIT(STATE_ERR0, 1)
REGDEF_BIT(STATE_ERR1, 1)
REGDEF_BIT(STATE_ERR2, 1)
REGDEF_BIT(STATE_ERR3, 1)
REGDEF_BIT(ULPS_LEAVE0, 1)
REGDEF_BIT(ULPS_LEAVE1, 1)
REGDEF_BIT(ULPS_LEAVE2, 1)
REGDEF_BIT(ULPS_LEAVE3, 1)
REGDEF_BIT(ULPS_LEAVEC, 1)
REGDEF_BIT(ULPS_ENTERC, 1)
REGDEF_BIT(STATE_ERRC, 1)
REGDEF_BIT(, 1)
REGDEF_END(CSI_INTEN0_REG)


// 0x14 MIPI-CSI interrupt Enable Register 1
REGDEF_OFFSET(CSI_INTEN1_REG, 0x14)
REGDEF_BEGIN(CSI_INTEN1_REG)
REGDEF_BIT(ESC0_DATA_LT, 1)
REGDEF_BIT(ESC1_DATA_LT, 1)
REGDEF_BIT(ESC2_DATA_LT, 1)
REGDEF_BIT(ESC3_DATA_LT, 1)
REGDEF_BIT(HS_EOT_TIMEOUT0, 1)
REGDEF_BIT(HS_EOT_TIMEOUT1, 1)
REGDEF_BIT(HS_EOT_TIMEOUT2, 1)
REGDEF_BIT(HS_EOT_TIMEOUT3, 1)
REGDEF_BIT(SOT_SYNC_CORRECTED0, 1)
REGDEF_BIT(SOT_SYNC_CORRECTED1, 1)
REGDEF_BIT(SOT_SYNC_CORRECTED2, 1)
REGDEF_BIT(SOT_SYNC_CORRECTED3, 1)
REGDEF_BIT(CLK_TERM_CHG_10, 1)
REGDEF_BIT(CLK_TERM_CHG_01, 1)
REGDEF_BIT(, 2)
REGDEF_BIT(FRMEND, 1)
REGDEF_BIT(FRMEND2, 1)
REGDEF_BIT(FRMEND3, 1)
REGDEF_BIT(FRMEND4, 1)
REGDEF_BIT(, 8)
REGDEF_BIT(FIFO_OV, 1)
REGDEF_BIT(FIFO2_OV, 1)
REGDEF_BIT(FIFO3_OV, 1)
REGDEF_BIT(FIFO4_OV, 1)
REGDEF_END(CSI_INTEN1_REG)


// 0x18 MIPI-CSI interrupt Status Register 0
REGDEF_OFFSET(CSI_INTSTS0_REG, 0x18)
REGDEF_BEGIN(CSI_INTSTS0_REG)
REGDEF_BIT(ECC_ERR, 1)
REGDEF_BIT(CRC_ERR, 1)
REGDEF_BIT(INVALID_DI, 1)
REGDEF_BIT(ECC_CORRECTED, 1)
REGDEF_BIT(FS_SYNC_ERR, 1)
REGDEF_BIT(LS_SYNC_ERR, 1)
REGDEF_BIT(FS_GOT, 1)
REGDEF_BIT(FE_GOT, 1)
REGDEF_BIT(GEN_GOT, 1)
REGDEF_BIT(DATA_LT_WC, 1)
REGDEF_BIT(LS_GOT, 1)
REGDEF_BIT(, 1)
REGDEF_BIT(SOT_SYNC_ERR0, 1)
REGDEF_BIT(SOT_SYNC_ERR1, 1)
REGDEF_BIT(SOT_SYNC_ERR2, 1)
REGDEF_BIT(SOT_SYNC_ERR3, 1)
REGDEF_BIT(ESC_RDY0, 1)
REGDEF_BIT(ESC_RDY1, 1)
REGDEF_BIT(ESC_RDY2, 1)
REGDEF_BIT(ESC_RDY3, 1)
REGDEF_BIT(STATE_ERR0, 1)
REGDEF_BIT(STATE_ERR1, 1)
REGDEF_BIT(STATE_ERR2, 1)
REGDEF_BIT(STATE_ERR3, 1)
REGDEF_BIT(ULPS_LEAVE0, 1)
REGDEF_BIT(ULPS_LEAVE1, 1)
REGDEF_BIT(ULPS_LEAVE2, 1)
REGDEF_BIT(ULPS_LEAVE3, 1)
REGDEF_BIT(ULPS_LEAVEC, 1)
REGDEF_BIT(ULPS_ENTERC, 1)
REGDEF_BIT(STATE_ERRC, 1)
REGDEF_BIT(, 1)
REGDEF_END(CSI_INTSTS0_REG)


// 0x1C MIPI-CSI interrupt Status Register 1
REGDEF_OFFSET(CSI_INTSTS1_REG, 0x1C)
REGDEF_BEGIN(CSI_INTSTS1_REG)
REGDEF_BIT(ESC0_DATA_LT, 1)
REGDEF_BIT(ESC1_DATA_LT, 1)
REGDEF_BIT(ESC2_DATA_LT, 1)
REGDEF_BIT(ESC3_DATA_LT, 1)
REGDEF_BIT(HS_EOT_TIMEOUT0, 1)
REGDEF_BIT(HS_EOT_TIMEOUT1, 1)
REGDEF_BIT(HS_EOT_TIMEOUT2, 1)
REGDEF_BIT(HS_EOT_TIMEOUT3, 1)
REGDEF_BIT(SOT_SYNC_CORRECTED0, 1)
REGDEF_BIT(SOT_SYNC_CORRECTED1, 1)
REGDEF_BIT(SOT_SYNC_CORRECTED2, 1)
REGDEF_BIT(SOT_SYNC_CORRECTED3, 1)
REGDEF_BIT(CLK_TERM_CHG_10, 1)
REGDEF_BIT(CLK_TERM_CHG_01, 1)
REGDEF_BIT(, 2)
REGDEF_BIT(FRMEND, 1)
REGDEF_BIT(FRMEND2, 1)
REGDEF_BIT(FRMEND3, 1)
REGDEF_BIT(FRMEND4, 1)
REGDEF_BIT(, 8)
REGDEF_BIT(FIFO_OV, 1)
REGDEF_BIT(FIFO2_OV, 1)
REGDEF_BIT(FIFO3_OV, 1)
REGDEF_BIT(FIFO4_OV, 1)
REGDEF_END(CSI_INTSTS1_REG)


// 0x20 MIPI-CSI High Speed Data Timeout Register 0
REGDEF_OFFSET(CSI_HSTIMEOUT_REG, 0x20)
REGDEF_BEGIN(CSI_HSTIMEOUT_REG)
REGDEF_BIT(HS_EOT_TIMEOUT_VALUE, 16)
REGDEF_BIT(, 16)
REGDEF_END(CSI_HSTIMEOUT_REG)


// 0x24 MIPI-CSI Received Packet DI Register
REGDEF_OFFSET(CSI_RXDI_REG, 0x24)
REGDEF_BEGIN(CSI_RXDI_REG)
REGDEF_BIT(PKT_VALID_DI, 8)
REGDEF_BIT(PKT_INVALID_DI, 8)
REGDEF_BIT(, 16)
REGDEF_END(CSI_RXDI_REG)


// 0x28 MIPI-CSI Received Short Packet Data Register 0
REGDEF_OFFSET(CSI_RXSPKT0_REG, 0x28)
REGDEF_BEGIN(CSI_RXSPKT0_REG)
REGDEF_BIT(FRM_NUMBER, 16)
REGDEF_BIT(LINE_NUMBER, 16)
REGDEF_END(CSI_RXSPKT0_REG)


// 0x2C MIPI-CSI Received Short Packet Data Register 1
REGDEF_OFFSET(CSI_RXSPKT1_REG, 0x2C)
REGDEF_BEGIN(CSI_RXSPKT1_REG)
REGDEF_BIT(GEN_DI, 8)
REGDEF_BIT(GEN_DATA, 16)
REGDEF_BIT(, 8)
REGDEF_END(CSI_RXSPKT1_REG)

// 0x30 MIPI-CSI Escape Command Code Register 0
REGDEF_OFFSET(CSI_ESCCMD_REG, 0x30)
REGDEF_BEGIN(CSI_ESCCMD_REG)
REGDEF_BIT(ESC_CMD0, 8)
REGDEF_BIT(ESC_CMD1, 8)
REGDEF_BIT(ESC_CMD2, 8)
REGDEF_BIT(ESC_CMD3, 8)
REGDEF_END(CSI_ESCCMD_REG)

// 0x34 MIPI-CSI Control Counter Register 1
REGDEF_OFFSET(CSI_COUNT2_REG, 0x34)
REGDEF_BEGIN(CSI_COUNT2_REG)
REGDEF_BIT(FRMEND2_LINE_CNT, 16)
REGDEF_BIT(, 16)
REGDEF_END(CSI_COUNT2_REG)

// 0x38 MIPI-CSI LI Control Register 0
REGDEF_OFFSET(CSI_LI_REG, 0x38)
REGDEF_BEGIN(CSI_LI_REG)
REGDEF_BIT(CHID_BIT0_OFS, 4)
REGDEF_BIT(CHID_BIT1_OFS, 4)
REGDEF_BIT(CHID_BIT2_OFS, 4)
REGDEF_BIT(CHID_BIT3_OFS, 4)
REGDEF_BIT(, 16)
REGDEF_END(CSI_LI_REG)

// 0x3C MIPI-CSI Control Register 3
REGDEF_OFFSET(CSI_CTRL3_REG, 0x3C)
REGDEF_BEGIN(CSI_CTRL3_REG)
REGDEF_BIT(VIRTUAL_ID3, 4)
REGDEF_BIT(VIRTUAL_ID4, 4)
REGDEF_BIT(, 24)
REGDEF_END(CSI_CTRL3_REG)

// 0x40 MIPI-CSI Control Counter Register 2
REGDEF_OFFSET(CSI_COUNT3_REG, 0x40)
REGDEF_BEGIN(CSI_COUNT3_REG)
REGDEF_BIT(FRMEND3_LINE_CNT, 16)
REGDEF_BIT(FRMEND4_LINE_CNT, 16)
REGDEF_END(CSI_COUNT3_REG)

// 0x44 MIPI-CSI Control Counter Register 3
REGDEF_OFFSET(CSI_LINECOUNT_REG, 0x44)
REGDEF_BEGIN(CSI_LINECOUNT_REG)
REGDEF_BIT(HW_RECV_LINES_FRAME,  16)
REGDEF_BIT(HW_RECV_LINES_FRAME2, 16)
REGDEF_END(CSI_LINECOUNT_REG)

// 0x48 MIPI-CSI PHY Reset Control Register
REGDEF_OFFSET(CSI_PHYRST_REG, 0x48)
REGDEF_BEGIN(CSI_PHYRST_REG)
REGDEF_BIT(PHY_RSTB0, 1)
REGDEF_BIT(PHY_RSTB1, 1)
REGDEF_BIT(, 30)
REGDEF_END(CSI_PHYRST_REG)

// 0x4C MIPI-CSI PHY Done Control Register
REGDEF_OFFSET(CSI_PHYDONE_REG, 0x4C)
REGDEF_BEGIN(CSI_PHYDONE_REG)
REGDEF_BIT(PHY_DONE0, 1)
REGDEF_BIT(PHY_DONE1, 1)
REGDEF_BIT(PHY_DONE2, 1)
REGDEF_BIT(PHY_DONE3, 1)
REGDEF_BIT(, 28)
REGDEF_END(CSI_PHYDONE_REG)

// 0x50 MIPI-CSI Input Lane Swap Control Register 0
REGDEF_OFFSET(CSI_INSWAP_REG, 0x50)
REGDEF_BEGIN(CSI_INSWAP_REG)
REGDEF_BIT(LANE0_SEL, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(LANE1_SEL, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(LANE2_SEL, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(LANE3_SEL, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(D0_SEL, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(D1_SEL, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(D2_SEL, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(D3_SEL, 3)
REGDEF_BIT(, 1)
REGDEF_END(CSI_INSWAP_REG)







// 0x54 MIPI-CSI Debug Register 0
REGDEF_OFFSET(CSI_DEBUG_REG, 0x54)
REGDEF_BEGIN(CSI_DEBUG_REG)
REGDEF_BIT(ANALOG_BIT_ORD, 1)
REGDEF_BIT(PIX_DEPACK_BYTE_ORD, 1)
REGDEF_BIT(PIX_DEPACK_BIT_ORD, 1)
REGDEF_BIT(, 1)
REGDEF_BIT(ULPS_CTRL, 1)
REGDEF_BIT(, 3)
REGDEF_BIT(D0ULPS, 1)
REGDEF_BIT(D1ULPS, 1)
REGDEF_BIT(D2ULPS, 1)
REGDEF_BIT(D3ULPS, 1)
REGDEF_BIT(CULPS, 1)
REGDEF_BIT(, 3)
REGDEF_BIT(PH_ECC_BIT_ORD, 1)
REGDEF_BIT(PH_ECC_WC_BYTE_ORD, 1)
REGDEF_BIT(PH_ECC_FIELD_ORD, 1)
REGDEF_BIT(, 13)
REGDEF_END(CSI_DEBUG_REG)


// 0x58 MIPI-CSI LANE STATE Register 0
REGDEF_OFFSET(CSI_LANESTATE0_REG, 0x58)
REGDEF_BEGIN(CSI_LANESTATE0_REG)
REGDEF_BIT(D0_LP, 2)
REGDEF_BIT(D0_HS, 1)
REGDEF_BIT(, 1)
REGDEF_BIT(D1_LP, 2)
REGDEF_BIT(D1_HS, 1)
REGDEF_BIT(, 1)
REGDEF_BIT(D2_LP, 2)
REGDEF_BIT(D2_HS, 1)
REGDEF_BIT(, 1)
REGDEF_BIT(D3_LP, 2)
REGDEF_BIT(D3_HS, 1)
REGDEF_BIT(, 1)
REGDEF_BIT(C_LP, 2)
REGDEF_BIT(C_HS, 1)
REGDEF_BIT(, 13)
REGDEF_END(CSI_LANESTATE0_REG)


// 0x5C MIPI-CSI LANE STATE Register 1
REGDEF_OFFSET(CSI_LANESTATE1_REG, 0x5C)
REGDEF_BEGIN(CSI_LANESTATE1_REG)
REGDEF_BIT(D0_STA_ERR, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(D1_STA_ERR, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(D2_STA_ERR, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(D3_STA_ERR, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(C_STA_ERR, 3)
REGDEF_BIT(, 13)
REGDEF_END(CSI_LANESTATE1_REG)


//0x64 MIPI-CSI FSM Control Register 0
REGDEF_OFFSET(CSI_FSM_REG, 0x64)
REGDEF_BEGIN(CSI_FSM_REG)
REGDEF_BIT(, 24)
REGDEF_BIT(CLK2_FORCE_FSM, 1)
REGDEF_BIT(, 7)
REGDEF_END(CSI_FSM_REG)


// 0x80 MIPI-CSI Analog Delay Control Register 0
REGDEF_OFFSET(CSI_DLY0_REG, 0x80)
REGDEF_BEGIN(CSI_DLY0_REG)
REGDEF_BIT(OCLK_EDGE, 1)
REGDEF_BIT(, 7)
REGDEF_BIT(EN_HSDATA0_DLY, 7)
REGDEF_BIT(, 17)
REGDEF_END(CSI_DLY0_REG)


// 0x84 MIPI-CSI Analog Delay Control Register 1
REGDEF_OFFSET(CSI_DLY1_REG, 0x84)
REGDEF_BEGIN(CSI_DLY1_REG)
REGDEF_BIT(DLY_CNT, 4)
REGDEF_BIT(, 28)
REGDEF_END(CSI_DLY1_REG)


// 0x88 MIPI-CSI PHY Control Register 0
REGDEF_OFFSET(CSI_PHYCTRL0_REG, 0x88)
REGDEF_BEGIN(CSI_PHYCTRL0_REG)
REGDEF_BIT(RESET, 1)
REGDEF_BIT(EN_BIAS, 1)
REGDEF_BIT(DLY_EN, 1)
REGDEF_BIT(, 1)
REGDEF_BIT(CLK_DESKEW, 3)
REGDEF_BIT(, 25)
REGDEF_END(CSI_PHYCTRL0_REG)


// 0x8C MIPI-CSI PHY Control Register 0
REGDEF_OFFSET(CSI_PHYCTRL1_REG, 0x8C)
REGDEF_BEGIN(CSI_PHYCTRL1_REG)
REGDEF_BIT(DL0_DESKEW, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(DL1_DESKEW, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(DL2_DESKEW, 3)
REGDEF_BIT(, 1)
REGDEF_BIT(DL3_DESKEW, 3)
REGDEF_BIT(IADJ, 2)
REGDEF_BIT(CLKO_HS_EDGE, 1)
REGDEF_BIT(CURR_DIV2, 1)
REGDEF_BIT(, 1)
REGDEF_BIT(CLK_FORCE_HS, 1)
REGDEF_BIT(CLK_FORCE_FSM, 1)
REGDEF_BIT(, 10)
REGDEF_END(CSI_PHYCTRL1_REG)

// 0x90 MIPI-CSI PATTERN Gen Control Register 0
REGDEF_OFFSET(CSI_PATGEN_REG, 0x90)
REGDEF_BEGIN(CSI_PATGEN_REG)
REGDEF_BIT(PATGEN_EN, 1)
REGDEF_BIT(, 3)
REGDEF_BIT(PATGEN_MODE, 3)
REGDEF_BIT(, 9)
REGDEF_BIT(PATGEN_VAL, 16)
REGDEF_END(CSI_PATGEN_REG)

// ECO MIPI-RESET Control Register
REGDEF_OFFSET(CSI_SIE_REG, 0x18)
REGDEF_BEGIN(CSI_SIE_REG)
REGDEF_BIT(, 9)
REGDEF_BIT(CSI_HWRESET, 1)
REGDEF_BIT(, 22)
REGDEF_END(CSI_SIE_REG)



#endif
