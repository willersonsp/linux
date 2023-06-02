/* Copyright (c) 2018-2019 Sigmastar Technology Corp.
 All rights reserved.

 Unless otherwise stipulated in writing, any and all information contained
herein regardless in any format shall remain the sole proprietary of
Sigmastar Technology Corp. and be kept in strict confidence
(Sigmastar Confidential Information) by the recipient.
Any unauthorized act including without limitation unauthorized disclosure,
copying, use, reproduction, sale, distribution, modification, disassembling,
reverse engineering and compiling of the contents of Sigmastar Confidential
Information is unlawful and strictly prohibited. Sigmastar hereby reserves the
rights to any and all damages, losses, costs and expenses resulting therefrom.
*/

#define  HAL_CAMCLKTBL_C
#include "hal_camclk_if.h"
#include "hal_camclk_complex.h"
#include "reg_clks.h"
#include "hal_camclk_util.h"

const HalCamClkNode_t gCamClkSrcNode[HAL_CAMCLK_SRC_Id_MAX] =
{
    {HAL_CAMCLK_SRC_CLK_VOID, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={1}},
    {HAL_CAMCLK_SRC_CLK_utmi_480m, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={480000000}},
    {HAL_CAMCLK_SRC_CLK_mpll_432m, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={432000000}},
    {HAL_CAMCLK_SRC_CLK_mpll_345m, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={345000000}},
    {HAL_CAMCLK_SRC_CLK_upll_384m, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_upll,5,4}},
    {HAL_CAMCLK_SRC_CLK_upll_320m, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_upll,3,2}},
    {HAL_CAMCLK_SRC_CLK_mpll_288m, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={288000000}},
    {HAL_CAMCLK_SRC_CLK_utmi_240m, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_utmi,2,1}},
    {HAL_CAMCLK_SRC_CLK_mpll_216m, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={216000000}},
    {HAL_CAMCLK_SRC_CLK_utmi_192m, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_utmi,5,2}},
    {HAL_CAMCLK_SRC_CLK_mpll_172m, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={172800000}},
    {HAL_CAMCLK_SRC_CLK_utmi_160m, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_utmi,3,1}},
    {HAL_CAMCLK_SRC_CLK_mpll_123m, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={123400000}},
    {HAL_CAMCLK_SRC_CLK_mpll_86m, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={86400000}},
    {HAL_CAMCLK_SRC_CLK_mpll_288m_div2, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mpll_288m,2,1}},
    {HAL_CAMCLK_SRC_CLK_mpll_288m_div4, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mpll_288m,4,1}},
    {HAL_CAMCLK_SRC_CLK_mpll_288m_div8, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mpll_288m,8,1}},
    {HAL_CAMCLK_SRC_CLK_mpll_216m_div2, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mpll_216m,2,1}},
    {HAL_CAMCLK_SRC_CLK_mpll_216m_div4, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mpll_216m,4,1}},
    {HAL_CAMCLK_SRC_CLK_mpll_216m_div8, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mpll_216m,8,1}},
    {HAL_CAMCLK_SRC_CLK_mpll_123m_div2, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mpll_123m,2,1}},
    {HAL_CAMCLK_SRC_CLK_mpll_86m_div2, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mpll_86m,2,1}},
    {HAL_CAMCLK_SRC_CLK_mpll_86m_div4, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mpll_86m,4,1}},
    {HAL_CAMCLK_SRC_CLK_mpll_86m_div16, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mpll_86m,16,1}},
    {HAL_CAMCLK_SRC_CLK_utmi_192m_div4, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_utmi_192m,4,1}},
    {HAL_CAMCLK_SRC_CLK_utmi_160m_div4, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_utmi_160m,4,1}},
    {HAL_CAMCLK_SRC_CLK_utmi_160m_div5, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_utmi_160m,5,1}},
    {HAL_CAMCLK_SRC_CLK_utmi_160m_div8, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_utmi_160m,8,1}},
    {HAL_CAMCLK_SRC_CLK_xtali_12m, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={12000000}},
    {HAL_CAMCLK_SRC_CLK_xtali_12m_div8, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_xtali_12m,8,1}},
    {HAL_CAMCLK_SRC_CLK_xtali_12m_div16, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_xtali_12m,16,1}},
    {HAL_CAMCLK_SRC_CLK_xtali_12m_div40, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_xtali_12m,40,1}},
    {HAL_CAMCLK_SRC_CLK_xtali_12m_div64, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_xtali_12m,64,1}},
    {HAL_CAMCLK_SRC_CLK_xtali_12m_div128, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_xtali_12m,128,1}},
    {HAL_CAMCLK_SRC_CLK_xtali_24m, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={24000000}},
    {HAL_CAMCLK_SRC_CLK_RTC_CLK_32K, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={32000}},
    {HAL_CAMCLK_SRC_CLK_pm_riu_w_clk_in, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mcu,1,1}},
    {HAL_CAMCLK_SRC_CLK_lpll_clk_div2, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_lpll_clk,2,1}},
    {HAL_CAMCLK_SRC_CLK_lpll_clk_div4, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_lpll_clk,4,1}},
    {HAL_CAMCLK_SRC_CLK_lpll_clk_div8, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_lpll_clk,8,1}},
    {HAL_CAMCLK_SRC_CLK_armpll_37p125m, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mpll_432m,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu_w_clk_in, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mcu,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu_w_clk_top, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mcu,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu_w_clk_sc_gp, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mcu,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu_w_clk_vhe_gp, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mcu,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu_w_clk_hemcu_gp, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mcu,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu_w_clk_mipi_if_gp, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mcu,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu_w_clk_mcu_if_gp, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mcu,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_p, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu,1,1}},
    {HAL_CAMCLK_SRC_CLK_mspi0_p, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mspi0,1,1}},
    {HAL_CAMCLK_SRC_CLK_mspi1_p, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mspi1,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_vhe_gp_p, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_vhe_gp,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_sc_gp_p, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu2x_p, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu2x,1,1}},
    {HAL_CAMCLK_SRC_CLK_mcu_p, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mcu,1,1}},
    {HAL_CAMCLK_SRC_CLK_mcu_pm_p, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mcu_pm,1,1}},
    {HAL_CAMCLK_SRC_CLK_isp_p, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_isp,1,1}},
    {HAL_CAMCLK_SRC_CLK_fclk1_p, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_fclk1,1,1}},
    {HAL_CAMCLK_SRC_CLK_fclk2_p, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_fclk2,1,1}},
    {HAL_CAMCLK_SRC_CLK_sdio_p, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_sdio,1,1}},
    {HAL_CAMCLK_SRC_CLK_tck_buf, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={1}},
    {HAL_CAMCLK_SRC_CLK_pad2isp_sr_pclk, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={1}},
    {HAL_CAMCLK_SRC_CLK_ccir_in_clk, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={1}},
    {HAL_CAMCLK_SRC_CLK_eth_buf, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={1}},
    {HAL_CAMCLK_SRC_CLK_rmii_buf, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={1}},
    {HAL_CAMCLK_SRC_CLK_emac_testrx125_in_lan, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={1}},
    {HAL_CAMCLK_SRC_CLK_miu_ff, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_sc_gp, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_vhe_gp, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_dig, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_xd2miu, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_urdma, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_bdma, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_vhe, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_vhe_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_mfeh, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_mfe, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_jpe1, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_jpe0, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_bach, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_file, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_uhc0, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_emac, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_cmdq, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_isp_dnr, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_isp_rot, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_isp_dma, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_isp_sta, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_gop, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_sc_dnr, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_sc_dnr_sad, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_sc_crop, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_sc1_frm, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_sc1_snp, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_sc1_snpi, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_sc1_dbg, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_sc2_frm, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_sc2_snpi, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_sc3_frm, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_fcie, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_sdio, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu_ive, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_sc_gp_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_riu_w_clk_top,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu_nogating, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_riu_w_clk_in,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu_sc_gp, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_riu_w_clk_sc_gp,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu_vhe_gp, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_riu_w_clk_vhe_gp,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu_hemcu_gp, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_riu_w_clk_hemcu_gp,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu_mipi_gp, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_riu_w_clk_mipi_if_gp,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu_mcu_if, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_riu_w_clk_mcu_if_gp,1,1}},
    {HAL_CAMCLK_SRC_CLK_miu2x, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_ddrpll_clk,1,1}},
    {HAL_CAMCLK_SRC_CLK_axi2x, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu2x_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_tck, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_tck_buf,1,1}},
    {HAL_CAMCLK_SRC_CLK_imi, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_miu_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_gop0, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_fclk1_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_gop1, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_fclk1_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_gop2, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_fclk2_p,1,1}},
    {HAL_CAMCLK_SRC_CLK_mpll_144m, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={144000000}},
    {HAL_CAMCLK_SRC_CLK_mpll_144m_div2, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mpll_144m,2,1}},
    {HAL_CAMCLK_SRC_CLK_mpll_144m_div4, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_mpll_144m,4,1}},
    {HAL_CAMCLK_SRC_CLK_xtali_12m_div2, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_xtali_12m,2,1}},
    {HAL_CAMCLK_SRC_CLK_xtali_12m_div4, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_xtali_12m,4,1}},
    {HAL_CAMCLK_SRC_CLK_xtali_12m_div12, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_xtali_12m,12,1}},
    {HAL_CAMCLK_SRC_CLK_rtc_32k, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={32000}},
    {HAL_CAMCLK_SRC_CLK_rtc_32k_div4, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_rtc_32k,4,1}},
    {HAL_CAMCLK_SRC_CLK_live_pm, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_xtali_24m,1,1}},
    {HAL_CAMCLK_SRC_CLK_riu_pm, HAL_CAMCLK_TYPE_FIXED_FACTOR, .attribute.stFixedFac={HAL_CAMCLK_SRC_CLK_pm_riu_w_clk_in,1,1}},
    {HAL_CAMCLK_SRC_CLK_miupll_clk, HAL_CAMCLK_TYPE_COMPLEX, .attribute.stComplex={HAL_CAMCLK_SRC_CLK_xtali_24m, &gMiupllOps}},
    {HAL_CAMCLK_SRC_CLK_ddrpll_clk, HAL_CAMCLK_TYPE_COMPLEX, .attribute.stComplex={HAL_CAMCLK_SRC_CLK_ddr_syn,&gDdrpllOps}},
    {HAL_CAMCLK_SRC_CLK_lpll_clk, HAL_CAMCLK_TYPE_COMPLEX, .attribute.stComplex={HAL_CAMCLK_SRC_CLK_mpll_432m,&gLpllOps}},
    {HAL_CAMCLK_SRC_CLK_cpupll_clk, HAL_CAMCLK_TYPE_COMPLEX, .attribute.stComplex={HAL_CAMCLK_SRC_CLK_mpll_432m,&gCpupllOps}},
    {HAL_CAMCLK_SRC_CLK_utmi, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={480000000}},
    {HAL_CAMCLK_SRC_CLK_upll, HAL_CAMCLK_TYPE_FIXED, .attribute.stFixed={480000000}},
    {HAL_CAMCLK_SRC_CLK_fuart0_synth_out, HAL_CAMCLK_TYPE_COMPLEX, .attribute.stComplex={HAL_CAMCLK_SRC_CLK_fuart0_synth_in,&gFuart0Ops}},
    {HAL_CAMCLK_SRC_CLK_csi2_mac_p, HAL_CAMCLK_TYPE_COMPLEX, .attribute.stComplex={HAL_CAMCLK_SRC_CLK_csi_mac,&gCsi2Ops}},
    {HAL_CAMCLK_SRC_CLK_miu, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_ddrpll_clk,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_miupll_clk,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m},REG_CKG_MIU_BASE,camclk_BIT0,camclk_BIT4,2,2,1}},
    {HAL_CAMCLK_SRC_CLK_ddr_syn, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_432m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_DDR_SYN_BASE,camclk_BIT0,0,2,2,1}},
    {HAL_CAMCLK_SRC_CLK_miu_rec, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div8,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div16,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div64,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div128},REG_CKG_MIU_REC_BASE,camclk_BIT0,0,2,2,1}},
    {HAL_CAMCLK_SRC_CLK_mcu, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_432m,(u8)HAL_CAMCLK_SRC_CLK_upll_320m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div2},REG_CKG_MCU_BASE,camclk_BIT0,camclk_BIT4,2,2,1}},
    {HAL_CAMCLK_SRC_CLK_riubrdg, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mcu_p,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_RIUBRDG_BASE,camclk_BIT8,0,2,10,1}},
    {HAL_CAMCLK_SRC_CLK_bdma, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_miu_p,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_BDMA_BASE,camclk_BIT0,0,2,2,0}},
    {HAL_CAMCLK_SRC_CLK_spi, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div2,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div4},REG_CKG_SPI_BASE,camclk_BIT0,camclk_BIT4,2,2,1}},
    {HAL_CAMCLK_SRC_CLK_uart0, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div2,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_UART0_BASE,camclk_BIT0,0,2,2,0}},
    {HAL_CAMCLK_SRC_CLK_uart1, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div2,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_UART1_BASE,camclk_BIT8,0,2,10,0}},
    {HAL_CAMCLK_SRC_CLK_fuart0_synth_in, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_432m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_FUART0_SYNTH_IN_BASE,camclk_BIT4,0,2,6,0}},
    {HAL_CAMCLK_SRC_CLK_fuart, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div2,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_fuart0_synth_out},REG_CKG_FUART_BASE,camclk_BIT0,0,2,2,0}},
    {HAL_CAMCLK_SRC_CLK_mspi0, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div2,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div4,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div2},REG_CKG_MSPI0_BASE,camclk_BIT0,0,2,2,0}},
    {HAL_CAMCLK_SRC_CLK_mspi1, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div2,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div4,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div2},REG_CKG_MSPI1_BASE,camclk_BIT8,0,2,10,0}},
    {HAL_CAMCLK_SRC_CLK_mspi, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mspi0_p,(u8)HAL_CAMCLK_SRC_CLK_mspi1_p},REG_CKG_MSPI_BASE,camclk_BIT12,0,1,14,0}},
    {HAL_CAMCLK_SRC_CLK_miic0, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div4,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div4,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_MIIC0_BASE,camclk_BIT0,0,2,2,0}},
    {HAL_CAMCLK_SRC_CLK_miic1, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div4,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div4,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_MIIC1_BASE,camclk_BIT8,0,2,10,0}},
    {HAL_CAMCLK_SRC_CLK_bist, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div2,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div4,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m},REG_CKG_BIST_BASE,camclk_BIT0,0,2,2,0}},
    {HAL_CAMCLK_SRC_CLK_pwr_ctl, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div16,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div8,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_PWR_CTL_BASE,camclk_BIT0,0,2,2,0}},
    {HAL_CAMCLK_SRC_CLK_xtali, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_XTALI_BASE,camclk_BIT0,0,2,2,1}},
    {HAL_CAMCLK_SRC_CLK_live, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_LIVE_BASE,camclk_BIT8,0,2,10,1}},
    {HAL_CAMCLK_SRC_CLK_sr_mclk, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div8,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div4,(u8)HAL_CAMCLK_SRC_CLK_mpll_123m_div2,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div4,(u8)HAL_CAMCLK_SRC_CLK_utmi_192m_div4,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m_div2,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div8,(u8)HAL_CAMCLK_SRC_CLK_xtali_24m,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m_div4,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m_div16,(u8)HAL_CAMCLK_SRC_CLK_lpll_clk,(u8)HAL_CAMCLK_SRC_CLK_lpll_clk_div2,(u8)HAL_CAMCLK_SRC_CLK_lpll_clk_div4,(u8)HAL_CAMCLK_SRC_CLK_lpll_clk_div8,(u8)HAL_CAMCLK_SRC_CLK_armpll_37p125m},REG_CKG_SR_MCLK_BASE,camclk_BIT8,0,4,10,0}},
    {HAL_CAMCLK_SRC_CLK_bist_vhe_gp, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_288m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div2,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m},REG_CKG_BIST_VHE_GP_BASE,camclk_BIT8,0,2,10,0}},
    {HAL_CAMCLK_SRC_CLK_vhe, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_288m,(u8)HAL_CAMCLK_SRC_CLK_upll_320m,(u8)HAL_CAMCLK_SRC_CLK_mpll_345m,(u8)HAL_CAMCLK_SRC_CLK_upll_384m,(u8)HAL_CAMCLK_SRC_CLK_utmi_240m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div2},REG_CKG_VHE_BASE,camclk_BIT0,0,3,2,0}},
    {HAL_CAMCLK_SRC_CLK_vhe_vpu, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_288m,(u8)HAL_CAMCLK_SRC_CLK_upll_320m,(u8)HAL_CAMCLK_SRC_CLK_mpll_345m,(u8)HAL_CAMCLK_SRC_CLK_upll_384m,(u8)HAL_CAMCLK_SRC_CLK_utmi_240m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div2},REG_CKG_VHE_VPU_BASE,camclk_BIT0,0,3,2,0}},
    {HAL_CAMCLK_SRC_CLK_xtali_sc_gp, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_XTALI_SC_GP_BASE,camclk_BIT4,0,2,6,1}},
    {HAL_CAMCLK_SRC_CLK_bist_sc_gp, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div2,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div4,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m},REG_CKG_BIST_SC_GP_BASE,camclk_BIT0,0,2,2,1}},
    {HAL_CAMCLK_SRC_CLK_emac_ahb, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div2,(u8)HAL_CAMCLK_SRC_CLK_mpll_123m,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m,(u8)HAL_CAMCLK_SRC_CLK_emac_testrx125_in_lan},REG_CKG_EMAC_AHB_BASE,camclk_BIT0,0,2,2,0}},
    {HAL_CAMCLK_SRC_CLK_jpe, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_utmi_480m,(u8)HAL_CAMCLK_SRC_CLK_mpll_432m,(u8)HAL_CAMCLK_SRC_CLK_upll_384m,(u8)HAL_CAMCLK_SRC_CLK_upll_320m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_JPE_BASE,camclk_BIT0,0,3,2,0}},
    {HAL_CAMCLK_SRC_CLK_aesdma, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_86m,(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_AESDMA_BASE,camclk_BIT0,camclk_BIT4,2,2,0}},
    {HAL_CAMCLK_SRC_CLK_sdio, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_utmi_192m_div4,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m_div2,(u8)HAL_CAMCLK_SRC_CLK_utmi_160m_div4,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div8,(u8)HAL_CAMCLK_SRC_CLK_utmi_160m_div5,(u8)HAL_CAMCLK_SRC_CLK_utmi_160m_div8,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div40},REG_CKG_SDIO_BASE,camclk_BIT0,0,3,2,0}},
    {HAL_CAMCLK_SRC_CLK_sd, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_utmi_192m_div4,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m_div2,(u8)HAL_CAMCLK_SRC_CLK_utmi_160m_div4,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div8,(u8)HAL_CAMCLK_SRC_CLK_utmi_160m_div5,(u8)HAL_CAMCLK_SRC_CLK_utmi_160m_div8,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div40},REG_CKG_SD_BASE,camclk_BIT0,0,3,2,0}},
    {HAL_CAMCLK_SRC_CLK_isp, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_123m,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div4,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div2,(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_utmi_192m,(u8)HAL_CAMCLK_SRC_CLK_utmi_240m},REG_CKG_ISP_BASE,camclk_BIT8,0,3,10,0}},
    {HAL_CAMCLK_SRC_CLK_fclk1, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_utmi_240m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m,(u8)HAL_CAMCLK_SRC_CLK_upll_320m,(u8)HAL_CAMCLK_SRC_CLK_mpll_172m},REG_CKG_FCLK1_BASE,camclk_BIT0,0,2,2,0}},
    {HAL_CAMCLK_SRC_CLK_fclk2, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_FCLK2_BASE,camclk_BIT0,0,2,2,0}},
    {HAL_CAMCLK_SRC_CLK_odclk, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_86m,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m_div2,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m_div4,(u8)HAL_CAMCLK_SRC_CLK_lpll_clk},REG_CKG_ODCLK_BASE,camclk_BIT0,0,2,2,0}},
    {HAL_CAMCLK_SRC_CLK_dip, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_upll_320m,(u8)HAL_CAMCLK_SRC_CLK_upll_384m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_utmi_192m,(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_utmi_160m,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_DIP_BASE,camclk_BIT0,0,3,2,0}},
    {HAL_CAMCLK_SRC_CLK_ive, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_mpll_123m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m},REG_CKG_IVE_BASE,camclk_BIT8,0,2,10,0}},
    {HAL_CAMCLK_SRC_CLK_nlm, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_miu_p,(u8)HAL_CAMCLK_SRC_CLK_fclk1_p},REG_CKG_NLM_BASE,camclk_BIT8,0,1,10,1}},
    {HAL_CAMCLK_SRC_CLK_emac_tx, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_eth_buf,(u8)HAL_CAMCLK_SRC_CLK_rmii_buf},REG_CKG_EMAC_TX_BASE,camclk_BIT0,0,1,2,0}},
    {HAL_CAMCLK_SRC_CLK_emac_rx, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_eth_buf,(u8)HAL_CAMCLK_SRC_CLK_rmii_buf},REG_CKG_EMAC_RX_BASE,camclk_BIT0,0,1,2,0}},
    {HAL_CAMCLK_SRC_CLK_emac_tx_ref, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_rmii_buf,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_EMAC_TX_REF_BASE,camclk_BIT8,0,1,10,0}},
    {HAL_CAMCLK_SRC_CLK_emac_rx_ref, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_rmii_buf,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_EMAC_RX_REF_BASE,camclk_BIT8,0,1,10,0}},
    {HAL_CAMCLK_SRC_CLK_hemcu_216m, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_216m},REG_CKG_HEMCU_216M_BASE,camclk_BIT0,0,0,0,0}},
    {HAL_CAMCLK_SRC_CLK_csi_mac, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m,(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_mpll_123m,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_CSI_MAC_BASE,camclk_BIT0,0,3,2,0}},
    {HAL_CAMCLK_SRC_CLK_mac_lptx, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m,(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_mpll_123m,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_MAC_LPTX_BASE,camclk_BIT8,0,3,10,0}},
    {HAL_CAMCLK_SRC_CLK_ns, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_NS_BASE,camclk_BIT0,0,2,2,0}},
    {HAL_CAMCLK_SRC_CLK_mcu_pm, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_mpll_216m,(u8)HAL_CAMCLK_SRC_CLK_utmi_192m,(u8)HAL_CAMCLK_SRC_CLK_mpll_172m,(u8)HAL_CAMCLK_SRC_CLK_utmi_160m,(u8)HAL_CAMCLK_SRC_CLK_mpll_288m_div2,(u8)HAL_CAMCLK_SRC_CLK_mpll_123m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div2,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_rtc_32k,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div8,(u8)HAL_CAMCLK_SRC_CLK_xtali_24m,(u8)HAL_CAMCLK_SRC_CLK_rtc_32k_div4,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div16,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div2,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div4},REG_CKG_MCU_PM_BASE,camclk_BIT0,camclk_BIT7,4,2,1}},
    {HAL_CAMCLK_SRC_CLK_spi_pm, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_rtc_32k,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div8,(u8)HAL_CAMCLK_SRC_CLK_mpll_144m_div4,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m_div2,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div4,(u8)HAL_CAMCLK_SRC_CLK_mpll_144m_div2,(u8)HAL_CAMCLK_SRC_CLK_mpll_86m,(u8)HAL_CAMCLK_SRC_CLK_mpll_216m_div2,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div8,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div12,(u8)HAL_CAMCLK_SRC_CLK_rtc_32k_div4,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div16,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div2,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div4,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_xtali_24m},REG_CKG_SPI_PM_BASE,camclk_BIT8,camclk_BIT14,4,10,1}},
    {HAL_CAMCLK_SRC_CLK_pm_sleep, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_rtc_32k,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div8,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div12,(u8)HAL_CAMCLK_SRC_CLK_rtc_32k_div4,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div16,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div2,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div4},REG_CKG_PM_SLEEP_BASE,0,0,3,12,0}},
    {HAL_CAMCLK_SRC_CLK_sar, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_rtc_32k,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div8,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div12,(u8)HAL_CAMCLK_SRC_CLK_rtc_32k_div4,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div16,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div2,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div4},REG_CKG_SAR_BASE,camclk_BIT5,0,3,7,1}},
    {HAL_CAMCLK_SRC_CLK_rtc, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_rtc_32k,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID,(u8)HAL_CAMCLK_SRC_CLK_VOID},REG_CKG_RTC_BASE,camclk_BIT0,0,3,2,1}},
    {HAL_CAMCLK_SRC_CLK_ir, HAL_CAMCLK_TYPE_COMPOSITE, .attribute.stComposite={{(u8)HAL_CAMCLK_SRC_CLK_xtali_12m,(u8)HAL_CAMCLK_SRC_CLK_rtc_32k,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div8,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div12,(u8)HAL_CAMCLK_SRC_CLK_rtc_32k_div4,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div16,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div2,(u8)HAL_CAMCLK_SRC_CLK_xtali_12m_div4},REG_CKG_IR_BASE,camclk_BIT5,0,3,7,1}},
};

#undef  HAL_CAMCLKTBL_C
