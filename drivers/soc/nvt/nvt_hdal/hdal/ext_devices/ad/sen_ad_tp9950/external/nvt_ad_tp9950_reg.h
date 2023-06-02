#ifndef _NVT_AD_TP9950_REG_H_
#define _NVT_AD_TP9950_REG_H_
#include "ad_drv.h"

// Bank 0 (Video Channel)
#define AD_TP9950_VIDEO_INPUT_STATUS_REG_OFS 0x01
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_VIDEO_INPUT_STATUS_REG)
AD_DRV_REGDEF_BIT(CDET, 1)		// 0: carrier detected, 1: No carrier detected
AD_DRV_REGDEF_BIT(NINTL, 1)		// 0: Interlaced video, 1: Progressive video
AD_DRV_REGDEF_BIT(EQDET, 1)		// 0: None, 			1: EQ or 50Hz (SD mode) Detected
AD_DRV_REGDEF_BIT(VDET, 1)		// 0: No video, 		1: Video detected
AD_DRV_REGDEF_BIT(SLOCK, 1)		// 0: Not lock, 		1: Carrier PLL Lock
AD_DRV_REGDEF_BIT(HLOCK, 1)		// 0: Not lock, 		1: Horizontal Pll Lock
AD_DRV_REGDEF_BIT(VLOCK, 1)		// 0: Not lock, 		1: Vertical Pll Lock
AD_DRV_REGDEF_BIT(VDLOSS, 1)	// 0: Video present, 	1: Video loss
AD_DRV_REGDEF_END(AD_TP9950_VIDEO_INPUT_STATUS_REG)
#endif

#define AD_TP9950_DECODING_CTRL_REG_OFS 0x02
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_DECODING_CTRL_REG)
AD_DRV_REGDEF_BIT(ITLC, 1)
AD_DRV_REGDEF_BIT(P720, 1)
AD_DRV_REGDEF_BIT(SD, 1)
AD_DRV_REGDEF_BIT(MD656, 1)
AD_DRV_REGDEF_BIT(F444, 1)
AD_DRV_REGDEF_BIT(OPLMT, 1)
AD_DRV_REGDEF_BIT(GMEN, 1)
AD_DRV_REGDEF_BIT(MD1120, 1)
AD_DRV_REGDEF_END(AD_TP9950_DECODING_CTRL_REG)
#endif

#define AD_TP9950_DETECTION_STATUS_REG_OFS 0x03
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_DETECTION_STATUS_REG)
AD_DRV_REGDEF_BIT(CVSTD, 3)
AD_DRV_REGDEF_BIT(SYWD, 1)
AD_DRV_REGDEF_BIT(EQGAIN, 4)
AD_DRV_REGDEF_END(AD_TP9950_DETECTION_STATUS_REG)
#endif

#define AD_TP9950_INTERNAL_STATUS_REG_OFS 0x04
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_INTERNAL_STATUS_REG)
AD_DRV_REGDEF_BIT(STATUS, 3)
AD_DRV_REGDEF_END(AD_TP9950_INTERNAL_STATUS_REG)
#endif

#define AD_TP9950_EQ2_CTRL_REG_OFS 0x07
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_EQ2_CTRL_REG)
AD_DRV_REGDEF_BIT(EQGAIN, 6)
AD_DRV_REGDEF_BIT(EQ_EN, 1)
AD_DRV_REGDEF_BIT(BPASS2, 1)
AD_DRV_REGDEF_END(AD_TP9950_EQ2_CTRL_REG)
#endif

#define AD_TP9950_READ_H_POS_CTRL_REG_OFS 0x1E
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_READ_H_POS_CTRL_REG)
AD_DRV_REGDEF_BIT(HPXL, 7)
AD_DRV_REGDEF_END(AD_TP9950_READ_H_POS_CTRL_REG)
#endif

#define AD_TP9950_READ_V_POS_CTRL_REG_OFS 0x1F
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_READ_V_POS_CTRL_REG)
AD_DRV_REGDEF_BIT(VLNN, 7)
AD_DRV_REGDEF_END(AD_TP9950_READ_V_POS_CTRL_REG)
#endif

#define AD_TP9950_CLAMP_CTRL_REG_OFS 0x26
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_CLAMP_CTRL_REG)
AD_DRV_REGDEF_BIT(CLMD, 1)
AD_DRV_REGDEF_BIT(PSP, 1)
AD_DRV_REGDEF_BIT(CBW, 2)
AD_DRV_REGDEF_BIT(SFLT, 1)
AD_DRV_REGDEF_BIT(GTST, 1)
AD_DRV_REGDEF_BIT(CKLY, 1)
AD_DRV_REGDEF_BIT(CLEN, 1)
AD_DRV_REGDEF_END(AD_TP9950_CLAMP_CTRL_REG)
#endif

#define AD_TP9950_COLOR_HPLL_FREERUN_CTRL_REG_OFS 0x2A
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_COLOR_HPLL_FREERUN_CTRL_REG)
AD_DRV_REGDEF_BIT(HPM, 2)
AD_DRV_REGDEF_BIT(LCS, 1)
AD_DRV_REGDEF_BIT(FCS, 1)
AD_DRV_REGDEF_BIT(CFQ, 3)
AD_DRV_REGDEF_BIT(CKLM, 1)
AD_DRV_REGDEF_END(AD_TP9950_COLOR_HPLL_FREERUN_CTRL_REG)
#endif

#define AD_TP9950_TEST_REG_OFS 0x2F
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_TEST_REG)
AD_DRV_REGDEF_BIT(TEST, 7)
AD_DRV_REGDEF_END(AD_TP9950_TEST_REG)
#endif

#define AD_TP9950_PAGE_REG_OFS 0x40
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_PAGE_REG)
AD_DRV_REGDEF_BIT(, 3)
AD_DRV_REGDEF_BIT(MPAGE, 1)
AD_DRV_REGDEF_END(AD_TP9950_PAGE_REG)
#endif

#define AD_TP9950_AFE_TEST_REG_OFS 0x41
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_AFE_TEST_REG)
AD_DRV_REGDEF_BIT(AIN_SEL, 4)
AD_DRV_REGDEF_BIT(OENAFE, 1)
AD_DRV_REGDEF_BIT(PTZTEST, 1)
AD_DRV_REGDEF_BIT(DIAG_SEL, 2)
AD_DRV_REGDEF_END(AD_TP9950_AFE_TEST_REG)
#endif

#define AD_TP9950_RX_CTRL_REG_OFS 0xA7
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_RX_CTRL_REG)
AD_DRV_REGDEF_BIT(RXEN, 1)
AD_DRV_REGDEF_BIT(RXIRQEN, 1)
AD_DRV_REGDEF_BIT(RXACP, 1)
AD_DRV_REGDEF_BIT(RXDAH, 1)
AD_DRV_REGDEF_BIT(RXPELCO, 1)
AD_DRV_REGDEF_BIT(RXPWM, 1)
AD_DRV_REGDEF_BIT(RXSTFALL, 1)
AD_DRV_REGDEF_BIT(RXIRQMD2, 1)
AD_DRV_REGDEF_END(AD_TP9950_RX_CTRL_REG)
#endif

#define AD_TP9950_SYSTEM_CLOCK_CTRL_REG_OFS 0xF5
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_SYSTEM_CLOCK_CTRL_REG)
AD_DRV_REGDEF_BIT(SYSCLKMD, 1)
AD_DRV_REGDEF_BIT(, 3)
AD_DRV_REGDEF_BIT(VADCKPOL, 1)
AD_DRV_REGDEF_END(AD_TP9950_SYSTEM_CLOCK_CTRL_REG)
#endif

#define AD_TP9950_REVISION_REG_OFS 0xFD
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_REVISION_REG)
AD_DRV_REGDEF_BIT(REVISION, 4)
AD_DRV_REGDEF_BIT(BO7, 1)
AD_DRV_REGDEF_BIT(BOHM, 1)
AD_DRV_REGDEF_BIT(BO4M, 1)
AD_DRV_REGDEF_BIT(SACNTN, 1)
AD_DRV_REGDEF_END(AD_TP9950_REVISION_REG)
#endif

#define AD_TP9950_DEVICE_ID_15_8_REG_OFS 0xFE
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_DEVICE_ID_15_8_REG)
AD_DRV_REGDEF_BIT(DEVICE_ID, 8)
AD_DRV_REGDEF_END(AD_TP9950_DEVICE_ID_15_8_REG)
#endif

#define AD_TP9950_DEVICE_ID_7_0_REG_OFS 0xFF
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_DEVICE_ID_7_0_REG)
AD_DRV_REGDEF_BIT(DEVICE_ID, 8)
AD_DRV_REGDEF_END(AD_TP9950_DEVICE_ID_7_0_REG)
#endif

// Bank 8 (MIPI)
#define AD_TP9950_MIPI_CKEN_REG_OFS 0x02
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_MIPI_CKEN_REG)
AD_DRV_REGDEF_BIT(MIPICKEN, 1)
AD_DRV_REGDEF_BIT(PWD12CK, 1)
AD_DRV_REGDEF_BIT(CKINVSER, 1)
AD_DRV_REGDEF_BIT(CKHINVSER, 1)
AD_DRV_REGDEF_END(AD_TP9950_MIPI_CKEN_REG)
#endif

#define AD_TP9950_MIPI_OUT_EN_CTRL_REG_OFS 0x08
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_MIPI_OUT_EN_CTRL_REG)
AD_DRV_REGDEF_BIT(MIPIEN0, 1)
AD_DRV_REGDEF_BIT(MIPIEN1, 1)
AD_DRV_REGDEF_BIT(MIPIEN2, 1)
AD_DRV_REGDEF_BIT(MIPIEN3, 1)
AD_DRV_REGDEF_BIT(PWD_0, 1)
AD_DRV_REGDEF_BIT(PWD_1, 1)
AD_DRV_REGDEF_BIT(PWD_2, 1)
AD_DRV_REGDEF_BIT(PWD_3, 1)
AD_DRV_REGDEF_END(AD_TP9950_MIPI_OUT_EN_CTRL_REG)
#endif

#define AD_TP9950_MIPI_PLL_CTRL_REG_OFS 0x10
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_MIPI_PLL_CTRL_REG)
AD_DRV_REGDEF_BIT(LOCK_VREF, 3)
AD_DRV_REGDEF_BIT(LOCK_ENB, 1)
AD_DRV_REGDEF_BIT(DIV_FIN, 2)
AD_DRV_REGDEF_BIT(PWDPLL, 1)
AD_DRV_REGDEF_BIT(RST_PLL_REG, 1)
AD_DRV_REGDEF_END(AD_TP9950_MIPI_PLL_CTRL_REG)
#endif

#define AD_TP9950_MIPI_NUM_LANES_REG_OFS 0x20
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_MIPI_NUM_LANES_REG)
AD_DRV_REGDEF_BIT(NUMLANES, 3)
AD_DRV_REGDEF_BIT(PSFM, 1)
AD_DRV_REGDEF_BIT(NUM_CHANNELS, 3)
AD_DRV_REGDEF_END(AD_TP9950_MIPI_NUM_LANES_REG)
#endif

#define AD_TP9950_MIPI_STOPCLK_REG_OFS 0x23
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_MIPI_STOPCLK_REG)
AD_DRV_REGDEF_BIT(UPMCLK, 1)
AD_DRV_REGDEF_BIT(STOPCLK, 1) 	// this reg has higher priority than AD_TP9950_MIPI_CKEN_REG.MIPICKEN
AD_DRV_REGDEF_BIT(TP_ENA, 1)
AD_DRV_REGDEF_BIT(PCLKPOL, 1)
AD_DRV_REGDEF_BIT(YC16BIT, 1)
AD_DRV_REGDEF_BIT(FRAME_NUM_ENA, 1)
AD_DRV_REGDEF_BIT(SKIP_FRAMING, 1)
AD_DRV_REGDEF_END(AD_TP9950_MIPI_STOPCLK_REG)
#endif

#define AD_TP9950_MIPI_T_LPX_REG_OFS 0x25
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_MIPI_T_LPX_REG)
AD_DRV_REGDEF_BIT(T_LPX, 8)
AD_DRV_REGDEF_END(AD_TP9950_MIPI_T_LPX_REG)
#endif

#define AD_TP9950_MIPI_T_PREP_REG_OFS 0x26
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_MIPI_T_PREP_REG)
AD_DRV_REGDEF_BIT(T_PREP, 8)
AD_DRV_REGDEF_END(AD_TP9950_MIPI_T_PREP_REG)
#endif

#define AD_TP9950_MIPI_T_TRAIL_REG_OFS 0x27
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_MIPI_T_TRAIL_REG)
AD_DRV_REGDEF_BIT(T_TRAIL, 8)
AD_DRV_REGDEF_END(AD_TP9950_MIPI_T_TRAIL_REG)
#endif

#define AD_TP9950_MIPI_VIRTUAL_CHANNEL_ID_REG_OFS 0x34
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_MIPI_VIRTUAL_CHANNEL_ID_REG)
AD_DRV_REGDEF_BIT(CH1_VCI, 2)
AD_DRV_REGDEF_BIT(CH2_VCI, 2)
AD_DRV_REGDEF_BIT(CH3_VCI, 2)
AD_DRV_REGDEF_BIT(CH4_VCI, 2)
AD_DRV_REGDEF_END(AD_TP9950_MIPI_VIRTUAL_CHANNEL_ID_REG)
#endif

#define AD_TP9950_MIPI_UNDERFLOW_REG_OFS 0x38
#ifndef AD_DRV_DUMMY_DEF
AD_DRV_REGDEF_BEGIN(AD_TP9950_MIPI_UNDERFLOW_REG)
AD_DRV_REGDEF_BIT(UNDERFLOW, 1)
AD_DRV_REGDEF_END(AD_TP9950_MIPI_UNDERFLOW_REG)
#endif

#endif //_NVT_AD_TP9950_REG_H_