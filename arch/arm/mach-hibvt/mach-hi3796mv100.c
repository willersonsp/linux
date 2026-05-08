/*
 * Hi3796M V100 (HiSTB family, Cortex-A7 quad) machine init.
 *
 * Phase 4.6 minimal backport: ports the HiSTB DT_MACHINE shell to Linux
 * 4.9.37 with a stripped-down peripheral set — UART, GIC, sp804 timer.
 * No HiSTB clock controller (uses fixed-rate clocks in DT instead),
 * no power management, no SMP (single-CPU boot).
 *
 * Modeled on mach-hi3536dv100.c for shape; HiSTB-specific IO map.
 */

#include <linux/clocksource.h>
#include <linux/irqchip.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <mach/io.h>

static struct map_desc hi3796mv100_io_desc[] __initdata = {
	{
		.virtual    = HI3796MV100_IOCH1_VIRT,
		.pfn        = __phys_to_pfn(HI3796MV100_IOCH1_PHYS),
		.length     = HI3796MV100_IOCH1_SIZE,
		.type       = MT_DEVICE,
	},
	{
		.virtual    = HI3796MV100_IOCH2_VIRT,
		.pfn        = __phys_to_pfn(HI3796MV100_IOCH2_PHYS),
		.length     = HI3796MV100_IOCH2_SIZE,
		.type       = MT_DEVICE,
	},
};

static void __init hi3796mv100_map_io(void)
{
	iotable_init(hi3796mv100_io_desc, ARRAY_SIZE(hi3796mv100_io_desc));
}

static const char *const hi3796mv100_compat[] __initconst = {
	"hisilicon,hi3796mv100",
	NULL,
};

DT_MACHINE_START(HI3796MV100_DT, "Hisilicon Hi3796M V100 (Flattened Device Tree)")
	.map_io     = hi3796mv100_map_io,
	.dt_compat  = hi3796mv100_compat,
MACHINE_END
