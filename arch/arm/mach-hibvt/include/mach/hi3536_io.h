#ifndef __HI3536_IO_H
#define __HI3536_IO_H

/* Hi3536 flagship IO map (Phase 4.5 Linux 4.9 backport).
 *
 * Same low-band peripheral block as Hi3531A (0x10000000..0x1071_0000)
 * + AMBA peripheral cluster (0x12000000..0x122F_0000) + media (0x13000000),
 * but A17 mpcore is at 0x1FFF_0000 (vs A9's 0x10300000).
 */

#define HI3536_IOCH1_VIRT  (0xFE000000)
#define HI3536_IOCH1_PHYS  (0x10000000)
#define HI3536_IOCH1_SIZE  (0x00710000)

#define HI3536_IOCH2_VIRT  (0xFE780000)
#define HI3536_IOCH2_PHYS  (0x12000000)
#define HI3536_IOCH2_SIZE  (0x002F0000)

/* Cortex-A17 mpcore peripheral block (SCU + GIC + private regs) */
#define HI3536_IOCH3_VIRT  (0xFEA80000)
#define HI3536_IOCH3_PHYS  (0x1FFF0000)
#define HI3536_IOCH3_SIZE  (0x00010000)

#define IO_OFFSET_IOCH1    (0xEE000000)
#define IO_OFFSET_IOCH2    (0xEC780000)
#define IO_OFFSET_IOCH3    (0xDEA90000)

#define IO_ADDR_IOCH1(x)   ((x) + IO_OFFSET_IOCH1)
#define IO_ADDR_IOCH2(x)   ((x) + IO_OFFSET_IOCH2)
#define IO_ADDR_IOCH3(x)   ((x) + IO_OFFSET_IOCH3)

#define IO_ADDRESS(x) \
	((x) >= HI3536_IOCH3_PHYS ? IO_ADDR_IOCH3(x) : \
	 (x) >= HI3536_IOCH2_PHYS ? IO_ADDR_IOCH2(x) : \
	                            IO_ADDR_IOCH1(x))

#define __io_address(x) (IOMEM(IO_ADDRESS(x)))

#endif /* __HI3536_IO_H */
