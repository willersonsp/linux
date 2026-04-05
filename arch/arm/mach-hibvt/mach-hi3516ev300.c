/*
 * Copyright (c) 2016-2017 HiSilicon Technologies Co., Ltd.
 *
 * HiSilicon hi3516ev200/ev300 family - ARMv7 Cortex-A7
 * Pure device-tree boot, no static IO mappings needed.
 */

#include <asm/mach/arch.h>

static const char *const hi3516ev300_compat[] __initconst = {
	"hisilicon,hi3516ev200",
	"hisilicon,hi3516ev300",
	"hisilicon,hi3518ev300",
	"hisilicon,hi3516dv200",
	NULL,
};

DT_MACHINE_START(HI3516EV300_DT, "Hisilicon HI3516EV300 (Flattened Device Tree)")
	.dt_compat = hi3516ev300_compat,
MACHINE_END
