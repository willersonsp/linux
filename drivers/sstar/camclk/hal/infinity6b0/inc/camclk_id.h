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

#ifndef __CAMCLK_ID_H__
#define __CAMCLK_ID_H__
typedef enum
{
    HAL_CAMCLK_SRC_CLK_VOID, 
    HAL_CAMCLK_SRC_CLK_utmi_480m, 
    HAL_CAMCLK_SRC_CLK_mpll_432m, 
    HAL_CAMCLK_SRC_CLK_mpll_345m, 
    HAL_CAMCLK_SRC_CLK_upll_384m, 
    HAL_CAMCLK_SRC_CLK_upll_320m, 
    HAL_CAMCLK_SRC_CLK_mpll_288m, 
    HAL_CAMCLK_SRC_CLK_utmi_240m, 
    HAL_CAMCLK_SRC_CLK_mpll_216m, 
    HAL_CAMCLK_SRC_CLK_utmi_192m, 
    HAL_CAMCLK_SRC_CLK_mpll_172m, 
    HAL_CAMCLK_SRC_CLK_utmi_160m, 
    HAL_CAMCLK_SRC_CLK_mpll_123m, 
    HAL_CAMCLK_SRC_CLK_mpll_86m, 
    HAL_CAMCLK_SRC_CLK_mpll_288m_div2, 
    HAL_CAMCLK_SRC_CLK_mpll_288m_div4, 
    HAL_CAMCLK_SRC_CLK_mpll_288m_div8, 
    HAL_CAMCLK_SRC_CLK_mpll_216m_div2, 
    HAL_CAMCLK_SRC_CLK_mpll_216m_div4, 
    HAL_CAMCLK_SRC_CLK_mpll_216m_div8, 
    HAL_CAMCLK_SRC_CLK_mpll_123m_div2, 
    HAL_CAMCLK_SRC_CLK_mpll_86m_div2, 
    HAL_CAMCLK_SRC_CLK_mpll_86m_div4, 
    HAL_CAMCLK_SRC_CLK_mpll_86m_div16, 
    HAL_CAMCLK_SRC_CLK_utmi_192m_div4, 
    HAL_CAMCLK_SRC_CLK_utmi_160m_div4, 
    HAL_CAMCLK_SRC_CLK_utmi_160m_div5, 
    HAL_CAMCLK_SRC_CLK_utmi_160m_div8, 
    HAL_CAMCLK_SRC_CLK_xtali_12m, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div8, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div16, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div40, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div64, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div128, 
    HAL_CAMCLK_SRC_CLK_xtali_24m, 
    HAL_CAMCLK_SRC_CLK_RTC_CLK_32K, 
    HAL_CAMCLK_SRC_CLK_pm_riu_w_clk_in, 
    HAL_CAMCLK_SRC_CLK_lpll_clk_div2, 
    HAL_CAMCLK_SRC_CLK_lpll_clk_div4, 
    HAL_CAMCLK_SRC_CLK_lpll_clk_div8, 
    HAL_CAMCLK_SRC_CLK_armpll_37p125m, 
    HAL_CAMCLK_SRC_CLK_riu_w_clk_in, 
    HAL_CAMCLK_SRC_CLK_riu_w_clk_top, 
    HAL_CAMCLK_SRC_CLK_riu_w_clk_sc_gp, 
    HAL_CAMCLK_SRC_CLK_riu_w_clk_vhe_gp, 
    HAL_CAMCLK_SRC_CLK_riu_w_clk_hemcu_gp, 
    HAL_CAMCLK_SRC_CLK_riu_w_clk_mipi_if_gp, 
    HAL_CAMCLK_SRC_CLK_riu_w_clk_mcu_if_gp, 
    HAL_CAMCLK_SRC_CLK_miu_p, 
    HAL_CAMCLK_SRC_CLK_mspi0_p, 
    HAL_CAMCLK_SRC_CLK_mspi1_p, 
    HAL_CAMCLK_SRC_CLK_miu_vhe_gp_p, 
    HAL_CAMCLK_SRC_CLK_miu_sc_gp_p, 
    HAL_CAMCLK_SRC_CLK_miu2x_p, 
    HAL_CAMCLK_SRC_CLK_mcu_p, 
    HAL_CAMCLK_SRC_CLK_mcu_pm_p, 
    HAL_CAMCLK_SRC_CLK_isp_p, 
    HAL_CAMCLK_SRC_CLK_fclk1_p, 
    HAL_CAMCLK_SRC_CLK_fclk2_p, 
    HAL_CAMCLK_SRC_CLK_sdio_p, 
    HAL_CAMCLK_SRC_CLK_tck_buf, 
    HAL_CAMCLK_SRC_CLK_pad2isp_sr_pclk, 
    HAL_CAMCLK_SRC_CLK_ccir_in_clk, 
    HAL_CAMCLK_SRC_CLK_eth_buf, 
    HAL_CAMCLK_SRC_CLK_rmii_buf, 
    HAL_CAMCLK_SRC_CLK_emac_testrx125_in_lan, 
    HAL_CAMCLK_SRC_CLK_miu_ff, 
    HAL_CAMCLK_SRC_CLK_miu_sc_gp, 
    HAL_CAMCLK_SRC_CLK_miu_vhe_gp, 
    HAL_CAMCLK_SRC_CLK_miu_dig, 
    HAL_CAMCLK_SRC_CLK_miu_xd2miu, 
    HAL_CAMCLK_SRC_CLK_miu_urdma, 
    HAL_CAMCLK_SRC_CLK_miu_bdma, 
    HAL_CAMCLK_SRC_CLK_miu_vhe, 
    HAL_CAMCLK_SRC_CLK_miu_mfeh, 
    HAL_CAMCLK_SRC_CLK_miu_mfe, 
    HAL_CAMCLK_SRC_CLK_miu_jpe1, 
    HAL_CAMCLK_SRC_CLK_miu_jpe0, 
    HAL_CAMCLK_SRC_CLK_miu_bach, 
    HAL_CAMCLK_SRC_CLK_miu_file, 
    HAL_CAMCLK_SRC_CLK_miu_uhc0, 
    HAL_CAMCLK_SRC_CLK_miu_emac, 
    HAL_CAMCLK_SRC_CLK_miu_cmdq, 
    HAL_CAMCLK_SRC_CLK_miu_isp_dnr, 
    HAL_CAMCLK_SRC_CLK_miu_isp_rot, 
    HAL_CAMCLK_SRC_CLK_miu_isp_dma, 
    HAL_CAMCLK_SRC_CLK_miu_isp_sta, 
    HAL_CAMCLK_SRC_CLK_miu_gop, 
    HAL_CAMCLK_SRC_CLK_miu_sc_dnr, 
    HAL_CAMCLK_SRC_CLK_miu_sc_dnr_sad, 
    HAL_CAMCLK_SRC_CLK_miu_sc_crop, 
    HAL_CAMCLK_SRC_CLK_miu_sc1_frm, 
    HAL_CAMCLK_SRC_CLK_miu_sc1_snp, 
    HAL_CAMCLK_SRC_CLK_miu_sc1_snpi, 
    HAL_CAMCLK_SRC_CLK_miu_sc1_dbg, 
    HAL_CAMCLK_SRC_CLK_miu_sc2_frm, 
    HAL_CAMCLK_SRC_CLK_miu_sc2_snpi, 
    HAL_CAMCLK_SRC_CLK_miu_sc3_frm, 
    HAL_CAMCLK_SRC_CLK_miu_fcie, 
    HAL_CAMCLK_SRC_CLK_miu_sdio, 
    HAL_CAMCLK_SRC_CLK_miu_ive, 
    HAL_CAMCLK_SRC_CLK_riu, 
    HAL_CAMCLK_SRC_CLK_riu_nogating, 
    HAL_CAMCLK_SRC_CLK_riu_sc_gp, 
    HAL_CAMCLK_SRC_CLK_riu_vhe_gp, 
    HAL_CAMCLK_SRC_CLK_riu_hemcu_gp, 
    HAL_CAMCLK_SRC_CLK_riu_mipi_gp, 
    HAL_CAMCLK_SRC_CLK_riu_mcu_if, 
    HAL_CAMCLK_SRC_CLK_miu2x, 
    HAL_CAMCLK_SRC_CLK_axi2x, 
    HAL_CAMCLK_SRC_CLK_tck, 
    HAL_CAMCLK_SRC_CLK_imi, 
    HAL_CAMCLK_SRC_CLK_gop0, 
    HAL_CAMCLK_SRC_CLK_gop1, 
    HAL_CAMCLK_SRC_CLK_gop2, 
    HAL_CAMCLK_SRC_CLK_mpll_144m, 
    HAL_CAMCLK_SRC_CLK_mpll_144m_div2, 
    HAL_CAMCLK_SRC_CLK_mpll_144m_div4, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div2, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div4, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div12, 
    HAL_CAMCLK_SRC_CLK_rtc_32k, 
    HAL_CAMCLK_SRC_CLK_rtc_32k_div4, 
    HAL_CAMCLK_SRC_CLK_live_pm, 
    HAL_CAMCLK_SRC_CLK_riu_pm, 
    HAL_CAMCLK_SRC_CLK_miupll_clk, 
    HAL_CAMCLK_SRC_CLK_ddrpll_clk, 
    HAL_CAMCLK_SRC_CLK_lpll_clk, 
    HAL_CAMCLK_SRC_CLK_cpupll_clk, 
    HAL_CAMCLK_SRC_CLK_utmi, 
    HAL_CAMCLK_SRC_CLK_upll, 
    HAL_CAMCLK_SRC_CLK_fuart0_synth_out, 
    HAL_CAMCLK_SRC_CLK_csi2_mac_p, 
    HAL_CAMCLK_SRC_CLK_miu, 
    HAL_CAMCLK_SRC_CLK_ddr_syn, 
    HAL_CAMCLK_SRC_CLK_miu_rec, 
    HAL_CAMCLK_SRC_CLK_mcu, 
    HAL_CAMCLK_SRC_CLK_riubrdg, 
    HAL_CAMCLK_SRC_CLK_bdma, 
    HAL_CAMCLK_SRC_CLK_spi, 
    HAL_CAMCLK_SRC_CLK_uart0, 
    HAL_CAMCLK_SRC_CLK_uart1, 
    HAL_CAMCLK_SRC_CLK_fuart0_synth_in, 
    HAL_CAMCLK_SRC_CLK_fuart, 
    HAL_CAMCLK_SRC_CLK_mspi0, 
    HAL_CAMCLK_SRC_CLK_mspi1, 
    HAL_CAMCLK_SRC_CLK_mspi, 
    HAL_CAMCLK_SRC_CLK_miic0, 
    HAL_CAMCLK_SRC_CLK_miic1, 
    HAL_CAMCLK_SRC_CLK_bist, 
    HAL_CAMCLK_SRC_CLK_pwr_ctl, 
    HAL_CAMCLK_SRC_CLK_xtali, 
    HAL_CAMCLK_SRC_CLK_live, 
    HAL_CAMCLK_SRC_CLK_sr_mclk, 
    HAL_CAMCLK_SRC_CLK_bist_vhe_gp, 
    HAL_CAMCLK_SRC_CLK_vhe, 
    HAL_CAMCLK_SRC_CLK_vhe_vpu, 
    HAL_CAMCLK_SRC_CLK_xtali_sc_gp, 
    HAL_CAMCLK_SRC_CLK_bist_sc_gp, 
    HAL_CAMCLK_SRC_CLK_emac_ahb, 
    HAL_CAMCLK_SRC_CLK_jpe, 
    HAL_CAMCLK_SRC_CLK_aesdma, 
    HAL_CAMCLK_SRC_CLK_sdio, 
    HAL_CAMCLK_SRC_CLK_sd, 
    HAL_CAMCLK_SRC_CLK_isp, 
    HAL_CAMCLK_SRC_CLK_fclk1, 
    HAL_CAMCLK_SRC_CLK_fclk2, 
    HAL_CAMCLK_SRC_CLK_odclk, 
    HAL_CAMCLK_SRC_CLK_dip, 
    HAL_CAMCLK_SRC_CLK_ive, 
    HAL_CAMCLK_SRC_CLK_nlm, 
    HAL_CAMCLK_SRC_CLK_emac_tx, 
    HAL_CAMCLK_SRC_CLK_emac_rx, 
    HAL_CAMCLK_SRC_CLK_emac_tx_ref, 
    HAL_CAMCLK_SRC_CLK_emac_rx_ref, 
    HAL_CAMCLK_SRC_CLK_hemcu_216m, 
    HAL_CAMCLK_SRC_CLK_csi_mac, 
    HAL_CAMCLK_SRC_CLK_mac_lptx, 
    HAL_CAMCLK_SRC_CLK_ns, 
    HAL_CAMCLK_SRC_CLK_mcu_pm, 
    HAL_CAMCLK_SRC_CLK_spi_pm, 
    HAL_CAMCLK_SRC_CLK_pm_sleep, 
    HAL_CAMCLK_SRC_CLK_sar, 
    HAL_CAMCLK_SRC_CLK_rtc, 
    HAL_CAMCLK_SRC_CLK_ir, 
    HAL_CAMCLK_SRC_Id_MAX
} HalCamClkSrcId_e;
#endif
