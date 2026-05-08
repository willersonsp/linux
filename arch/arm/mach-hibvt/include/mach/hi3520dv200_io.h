#ifndef __HI3520DV200_IO_H
#define __HI3520DV200_IO_H

/* Hi3520DV200 V1-era IO map (Phase 4.7 backport).
 *
 * Vendor mach-hi3520d puts its peripheral cluster at 0x20000000 (V1-era
 * scheme inherited from CV100/AV100 ARM926 family).  A9 mpcore lives at
 * 0x20300000 inside the same cluster.
 */

/* Main peripheral cluster: 0x20000000 — 0x20800000 (covers UART, timer,
 * CRG, sysctl, A9 mpcore, PL310 L2 cache). */
#define HI3520DV200_IOCH1_VIRT  (0xFE000000)
#define HI3520DV200_IOCH1_PHYS  (0x20000000)
#define HI3520DV200_IOCH1_SIZE  (0x00800000)

#define IO_OFFSET_IOCH1   (0xDE000000)  /* 0xfe000000 - 0x20000000 */

#define IO_ADDRESS(x)   ((x) + IO_OFFSET_IOCH1)

#define __io_address(x) (IOMEM(IO_ADDRESS(x)))

#endif /* __HI3520DV200_IO_H */
