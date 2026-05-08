/*
 * Hi3536 flagship (Cortex-A17 quad + A7 video coprocessor) machine init.
 *
 * Phase 4.5 backport: ports the vendor 3.10 mach-hi3536 to Linux 4.9.37
 * DT-based boot.  Single-CPU mode for boot-to-shell (max_cpus=1) — vendor
 * pen-release SMP requires more wiring and is a follow-up.
 *
 * Modeled on mach-hi3536dv100.c (also single-CPU A7 in this tree).
 */

#include <linux/clocksource.h>
#include <linux/irqchip.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <mach/io.h>

static struct map_desc hi3536_io_desc[] __initdata = {
	{
		.virtual    = HI3536_IOCH1_VIRT,
		.pfn        = __phys_to_pfn(HI3536_IOCH1_PHYS),
		.length     = HI3536_IOCH1_SIZE,
		.type       = MT_DEVICE,
	},
	{
		.virtual    = HI3536_IOCH2_VIRT,
		.pfn        = __phys_to_pfn(HI3536_IOCH2_PHYS),
		.length     = HI3536_IOCH2_SIZE,
		.type       = MT_DEVICE,
	},
	{
		.virtual    = HI3536_IOCH3_VIRT,
		.pfn        = __phys_to_pfn(HI3536_IOCH3_PHYS),
		.length     = HI3536_IOCH3_SIZE,
		.type       = MT_DEVICE,
	},
};

static void __init hi3536_map_io(void)
{
	iotable_init(hi3536_io_desc, ARRAY_SIZE(hi3536_io_desc));
}

static const char *const hi3536_compat[] __initconst = {
	"hisilicon,hi3536",
	NULL,
};

DT_MACHINE_START(HI3536_DT, "Hisilicon Hi3536 (Flattened Device Tree)")
	.map_io     = hi3536_map_io,
	.dt_compat  = hi3536_compat,
MACHINE_END
