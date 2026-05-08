/*
 * Hi3520DV200 (Cortex-A9 single, V1-era DVR/NVR) machine init.
 *
 * Phase 4.7 backport: ports the vendor 3.0 mach-hi3520d to Linux 4.9.37
 * DT-based boot.  No clock controller driver — DT uses fixed-rate clocks.
 * Single-CPU only (silicon is single-core anyway).
 */

#include <linux/clocksource.h>
#include <linux/irqchip.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <mach/io.h>

static struct map_desc hi3520dv200_io_desc[] __initdata = {
	{
		.virtual    = HI3520DV200_IOCH1_VIRT,
		.pfn        = __phys_to_pfn(HI3520DV200_IOCH1_PHYS),
		.length     = HI3520DV200_IOCH1_SIZE,
		.type       = MT_DEVICE,
	},
};

static void __init hi3520dv200_map_io(void)
{
	iotable_init(hi3520dv200_io_desc, ARRAY_SIZE(hi3520dv200_io_desc));
}

static const char *const hi3520dv200_compat[] __initconst = {
	"hisilicon,hi3520dv200",
	NULL,
};

DT_MACHINE_START(HI3520DV200_DT, "Hisilicon Hi3520DV200 (Flattened Device Tree)")
	.map_io     = hi3520dv200_map_io,
	.dt_compat  = hi3520dv200_compat,
MACHINE_END
