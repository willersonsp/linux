/*
 * Copyright (c) 2018 HiSilicon Technologies Co., Ltd.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "drv_hash_v100.h"
#include "drv_hash.h"

#ifdef CHIP_HASH_VER_V100

/*************************** Structure Definition ****************************/
/** \addtogroup     hash */
/** @{ */  /** <!-- [hash] */

/*! \hash 256 result size in word */
#define HASH256_RESULT_SIZE_IN_WORD   (8)

/*! Define the rec read bit mask */
#define HASH_READ_MASK_REC            (0x08)

/*! Define the dma read bit mask */
#define HASH_READ_MASK_DMA            (0x02)

/*! Define the hash read bit mask */
#define HASH_READ_MASK_HASH           (0x01)

/*! hash is busy ot not */
#ifdef MHASH_NONSUPPORT
static hi_u32 hash_busy = HI_FALSE;
#endif

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      hash */
/** @{ */  /** <!--[hash]*/

hi_s32 drv_hash_init(void)
{
    HI_LOG_FUNC_ENTER();

    module_disable(CRYPTO_MODULE_ID_HASH);
    module_enable(CRYPTO_MODULE_ID_HASH);

    HI_LOG_FUNC_EXIT();
    return HI_SUCCESS;
}

hi_s32 drv_hash_deinit(void)
{
    HI_LOG_FUNC_ENTER();
    HI_LOG_FUNC_EXIT();
    return HI_SUCCESS;
}

void drv_hash_resume(void)
{
    HI_LOG_FUNC_ENTER();

    module_enable(CRYPTO_MODULE_ID_HASH);

    HI_LOG_FUNC_EXIT();
    return;
}

void drv_hash_suspend(void)
{
    HI_LOG_FUNC_ENTER();

    module_disable(CRYPTO_MODULE_ID_HASH);

    HI_LOG_FUNC_EXIT();
    return;
}

/* wait hash ready */
static hi_s32 drv_hash_wait_ready(hi_u32 bitmask)
{
    hi_u32 i = 0;
    hash_status ready;

    HI_LOG_FUNC_ENTER();

    /* wait ready */
    for (i = 0; i < CRYPTO_TIME_OUT; i++) {
        ready.u32 = HASH_READ(REG_STATUS);
        if (ready.u32 & bitmask) {
            break;
        }
        if (i <= MS_TO_US) {
            crypto_udelay(1);  /* short waitting for 1000 us */
        } else {
            crypto_msleep(1);  /* long waitting for 5000 ms*/
        }
    }
    if (i >= CRYPTO_TIME_OUT) {
        HI_LOG_ERROR("error, hash wait done timeout\n");
        HI_LOG_PRINT_ERR_CODE(HI_ERR_CIPHER_TIMEOUT);
        return HI_ERR_CIPHER_TIMEOUT;
    }

    HI_LOG_FUNC_EXIT();
    return HI_SUCCESS;
}

hi_s32 drv_hash_config(hi_u32 chn_num, hash_mode mode, hi_u32 state[HASH_RESULT_MAX_SIZE_IN_WORD])
{
    hash_ctrl ctrl;
    hi_s32 ret = HI_FAILURE;

    HI_LOG_FUNC_ENTER();

    HI_LOG_CHECK_PARAM(state == HI_NULL);

    CRYPTO_UNUSED(chn_num);

#ifdef MHASH_NONSUPPORT
    if (HI_TRUE == hash_busy) {
        /* the hash already starting, here just return success */
        HI_LOG_FUNC_EXIT();
        return HI_SUCCESS;
    }
    hash_busy = HI_TRUE;
#endif

    /* wait ready */
    ret = drv_hash_wait_ready(HASH_READ_MASK_HASH);
    if (ret != HI_SUCCESS) {
        HI_LOG_PRINT_FUNC_ERR(drv_hash_wait_ready, ret);
        return ret;
    }

    ctrl.u32 = HASH_READ(REG_CTRL);

    /* only support sha1 and sha256 */
    if (mode == HASH_MODE_SHA1) {
        ctrl.bits.sha_sel = 0x00; /* SHA1 */
    } else if ((mode == HASH_MODE_SHA256) || (mode == HASH_MODE_SHA224)) {
        ctrl.bits.sha_sel = 0x01; /* SHA256 */
    } else {
        HI_LOG_ERROR("error, nonsupport hash mode %d\n", mode);
        HI_LOG_PRINT_ERR_CODE(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /* control configure */
    ctrl.bits.read_ctrl = 0;  /* 0:read by DMA, 1: read by CPU */
    ctrl.bits.hmac_flag = 0;  /* 0: raw hash, 1: hmac */
    ctrl.bits.hardkey_sel = 0;/* 0: cpu key, 1: hard key*/
    ctrl.bits.small_end_en = 1;/* 0: big, 1: little */
    ctrl.bits.sha_init_update_en = 1;/* initial hash value from CPU */

    HASH_WRITE(REG_CTRL, ctrl.u32);
    HI_LOG_INFO("REG_CTRL: 0x%x\n", ctrl.u32);

#ifdef MHASH_NONSUPPORT
    {
        sha_start start;

        /* logic don't support config init value of hash
         * here must set it to max vaule
         * then reset hash after compute finished
         */
        HASH_WRITE(REG_TOTALLEN_LOW, 0xFFFFFFFF);
        HASH_WRITE(REG_TOTALLEN_HIGH, 0x00);

        /* ready to working,
         * the hardware still be idle until write the reg of REG_DMA_LEN
         * so must start the hardware before write DMA addr and length.
         */
        start.u32 = HASH_READ(REG_START);
        start.bits.sha_start = 0x01;
        HASH_WRITE(REG_START, start.u32);
        HI_LOG_INFO("REG_START: 0x%x\n", start.u32);

        hash_busy = HI_TRUE;
    }
#else
    {
        hi_u32 i = 0;

        /* write hash initial value */
        for (i = 0; i < HASH256_RESULT_SIZE_IN_WORD; i++) {
            HASH_WRITE(REG_INIT1_UPDATE + i * 4, CPU_TO_BE32(state[i]));
            HI_LOG_DEBUG("Set hash: 0x%x\n", state[i]);
        }
    }
#endif
    HI_LOG_FUNC_EXIT();
    return HI_SUCCESS;

}

hi_s32 drv_hash_start(hi_u32 chn_num, crypto_mem *mem, hi_u32 length)
{
    HI_LOG_FUNC_ENTER();

    /* buffer addr and size must align with word */
    HI_LOG_CHECK_PARAM((length & 0x03) != 0);

    HI_LOG_DEBUG("MMZ phy 0x%x, length 0x%x\n", ADDR_L32(mem->mmz_addr), length);

    CRYPTO_UNUSED(chn_num);

#ifndef MHASH_NONSUPPORT
    {
        sha_start start;

        /* set hash message total length.
         * in nature here we don't know the total length of message,
         * here just set the total length to buf_size each hash calculation.
         * then we can release the hash hardware after each hash calculation.
         */
        HASH_WRITE(REG_TOTALLEN_LOW, length);

        /* max length of msg is 2^32, the high 32bit of length always be zero */
        HASH_WRITE(REG_TOTALLEN_HIGH, 0x00);

        /* ready to working,
         * the hardware still be idle until write the reg of REG_DMA_LEN
         * so must start the hardware before write DMA addr and length.
         */
        start.u32 = HASH_READ(REG_START);
        start.bits.sha_start = 0x01;
        HASH_WRITE(REG_START, start.u32);
        HI_LOG_INFO("REG_START: 0x%x\n", start.u32);
    }
#endif

    /* DMA address and length, at once write the reg of REG_DMA_LEN,
     * the hardware start working immediately.
     */
    HASH_WRITE(REG_DMA_START_ADDR, ADDR_L32(mem->mmz_addr));
    HASH_WRITE(REG_DMA_LEN, length);
    HI_LOG_INFO("Hash PHY: 0x%x, size 0x%x\n", ADDR_L32(mem->mmz_addr), length);

    HI_LOG_FUNC_EXIT();
    return HI_SUCCESS;
}

hi_s32 drv_hash_wait_done(hi_u32 chn_num, hi_u32 *state)
{
    hi_u32 i = 0;
    hi_s32 ret = HI_FAILURE;
    hash_status ready;

    HI_LOG_FUNC_ENTER();

    HI_LOG_CHECK_PARAM(state == HI_NULL);

    CRYPTO_UNUSED(chn_num);

    /* wait ready */
    ret = drv_hash_wait_ready(HASH_READ_MASK_REC);
    if (ret != HI_SUCCESS) {
        HI_LOG_PRINT_FUNC_ERR(drv_hash_wait_ready, ret);
        return ret;
    }

    /* check error code */
    ready.u32 = HASH_READ(REG_STATUS);
    if (ready.bits.len_err) {
        HI_LOG_ERROR("error, hash len err, chn=%d", chn_num);
        return HI_ERR_CIPHER_OVERFLOW;
    }
    HI_LOG_INFO("Status: 0x%x\n", ready.u32);

    /* read hash result */
    for (i = 0; i < HASH256_RESULT_SIZE_IN_WORD; i++) {
        state[i] = HASH_READ(REG_SHA_OUT1 + i * 4);
        HI_LOG_INFO("state[%d] 0x%x\n", i, state[i]);
    }

    HI_LOG_FUNC_EXIT();
    return HI_SUCCESS;
}

void drv_hash_reset(hi_u32 chn_num)
{
    CRYPTO_UNUSED(chn_num);
#ifdef MHASH_NONSUPPORT

    HI_LOG_FUNC_ENTER();

    module_disable(CRYPTO_MODULE_ID_HASH);
    module_enable(CRYPTO_MODULE_ID_HASH);
    hash_busy = HI_FALSE;

    HI_LOG_INFO("Hash reset ...\n");

    HI_LOG_FUNC_EXIT();
#endif
}

hi_s32 drv_hmac256_block(hi_u32 *din, hi_u32 *hamc)
{
    hi_s32 ret = HI_FAILURE;
    hi_u32 i = 0;
    hash_ctrl ctrl;

    HI_LOG_FUNC_ENTER();

    /*1.set hmac padded message ByteLength*/
    HASH_WRITE(REG_TOTALLEN_LOW, 0x40);
    HASH_WRITE(REG_TOTALLEN_HIGH, 0x00);

    /*2.set hash ctrl register*/
    ctrl.u32 = HASH_READ(REG_CTRL);
    ctrl.bits.read_ctrl = 1;
    ctrl.bits.sha_sel = 0x1;
    ctrl.bits.hmac_flag = 1;
    ctrl.bits.hardkey_sel = 0;
    ctrl.bits.small_end_en = 1;
    ctrl.bits.sha_init_update_en = 0;
    HASH_WRITE (REG_CTRL, ctrl.u32);

    /*3.set start*/
    HASH_WRITE (REG_START, 0x01);

    /*ready input data*/
    ret = drv_hash_wait_ready(HASH_READ_MASK_DMA);
    if (ret != HI_SUCCESS) {
        HI_LOG_PRINT_FUNC_ERR(drv_hash_wait_ready, ret);
        return ret;
    }

    /*4.set data_in*/
    for (i = 0; i < HASH_BLOCK_SIZE; i++) {
        HASH_WRITE(REG_DATA_IN, din[i]);
    }

    ret = drv_hash_wait_ready(HASH_READ_MASK_HASH);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    /*5.hash ready*/
    ret = drv_hash_wait_done(HASH_HARD_CHANNEL, hamc);
    if (ret != HI_SUCCESS) {
        HI_LOG_PRINT_FUNC_ERR(drv_hash_wait_done, ret);
        return ret;
    }

    HI_LOG_FUNC_EXIT();
    return HI_SUCCESS;
}

void drv_hash_get_capacity(hash_capacity *capacity)
{
    crypto_memset(capacity, sizeof(hash_capacity), 0,  sizeof(hash_capacity));

    capacity->sha1   = CRYPTO_CAPACITY_SUPPORT;
    capacity->sha256 = CRYPTO_CAPACITY_SUPPORT;

#ifndef MHASH_NONSUPPORT
    capacity->sha224 = CRYPTO_CAPACITY_SUPPORT;
#endif
}

/** @} */  /** <!-- ==== API declaration end ==== */

#endif //End of CHIP_HASH_VER_V100
