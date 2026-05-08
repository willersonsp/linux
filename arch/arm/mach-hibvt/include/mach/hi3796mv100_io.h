#ifndef __HI3796MV100_IO_H
#define __HI3796MV100_IO_H

/* HiSTB peripheral IO map for Hi3796M V100.
 * Phase 4.6 minimal — covers UART0 + timer + GIC.
 */

/* HiSTB peripheral cluster: 0xf8000000-0xf8c00000 */
#define HI3796MV100_IOCH1_VIRT  (0xFE000000)
#define HI3796MV100_IOCH1_PHYS  (0xF8000000)
#define HI3796MV100_IOCH1_SIZE  (0x00C00000)

/* GIC at 0xf1000000 (separate physical cluster) */
#define HI3796MV100_IOCH2_VIRT  (0xFEC00000)
#define HI3796MV100_IOCH2_PHYS  (0xF1000000)
#define HI3796MV100_IOCH2_SIZE  (0x00010000)

#define IO_OFFSET_IOCH1   (0x06000000)  /* 0xfe000000 - 0xf8000000 */
#define IO_OFFSET_IOCH2   (0x0DC00000)  /* 0xfec00000 - 0xf1000000 */

#define IO_ADDRESS(x) \
	((x) >= HI3796MV100_IOCH1_PHYS ? (x) + IO_OFFSET_IOCH1 : \
	                                 (x) + IO_OFFSET_IOCH2)

#define __io_address(x) (IOMEM(IO_ADDRESS(x)))

#endif /* __HI3796MV100_IO_H */
