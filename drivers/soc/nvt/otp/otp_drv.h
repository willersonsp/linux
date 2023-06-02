#ifndef __MODULE_OTP_DRV_H__
#define __MODULE_OTP_DRV_H__
#include <linux/io.h>
#include <linux/spinlock.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <linux/completion.h>
#include <linux/clk.h>
#include <mach/nvt_type.h>
#include <mach/rcw_macro.h>
//extern void arb_isr(void);
//extern void arb2_isr(void);


#define MODULE_IRQ_NUM          1
#define MODULE_REG_NUM  		1
#define MODULE_CLK_NUM          1

#define WRITE_REG(VALUE, ADDR)  iowrite32(VALUE, ADDR)
#define READ_REG(ADDR)          ioread32(ADDR)

typedef struct module_info {
	struct completion xxx_completion;
	struct semaphore xxx_sem;
	struct clk *pclk[MODULE_CLK_NUM];
	struct tasklet_struct xxx_tasklet;
	void __iomem *io_addr[MODULE_REG_NUM];
	int iinterrupt_id[MODULE_IRQ_NUM];
	wait_queue_head_t xxx_wait_queue;
	spinlock_t xxx_spinlock;
} MODULE_INFO, *PMODULE_INFO;

int nvt_otp_drv_open(PMODULE_INFO pmodule_info, unsigned char if_id);
int nvt_otp_drv_release(PMODULE_INFO pmodule_info, unsigned char if_id);
int nvt_otp_drv_init(PMODULE_INFO pmodule_info);
int nvt_otp_drv_remove(PMODULE_INFO pmodule_info);
int nvt_otp_drv_suspend(MODULE_INFO *pmodule_info);
int nvt_otp_drv_resume(MODULE_INFO *pmodule_info);
int nvt_otp_drv_ioctl(unsigned char if_id, MODULE_INFO *pmodule_info, unsigned int cmd, unsigned long argc);

//int nvt_ddr_arb_drv_write_reg(PMODULE_INFO pmodule_info, unsigned long addr, unsigned long value);
//int nvt_ddr_arb_drv_read_reg(PMODULE_INFO pmodule_info, unsigned long addr);
#endif

