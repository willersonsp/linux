#ifndef __HISI_UNCOMPRESS_H__
#define __HISI_UNCOMPRESS_H__
#include <mach/platform.h>

#define AMBA_UART_DR    (*(unsigned char *)(UART0_BASE + 0x0))
#define AMBA_UART_LCRH  (*(unsigned char *)(UART0_BASE + 0x2c))
#define AMBA_UART_CR    (*(unsigned char *)(UART0_BASE + 0x30))
#define AMBA_UART_FR    (*(unsigned char *)(UART0_BASE + 0x18))

/*
 * This does not append a newline
 */
static inline void putc(int c)
{
	while (AMBA_UART_FR & (1 << 5))
		barrier();

	AMBA_UART_DR = c;
}

static inline void flush(void)
{
	while (AMBA_UART_FR & (1 << 3))
		barrier();
}

/*
 * On real boards U-Boot leaves PL011 enabled (CR |= UARTEN|TXE|RXE)
 * before jumping to the kernel. Under QEMU we hand the kernel control
 * directly, so UARTEN stays clear and writes to UART_DR are dropped.
 * Enable it here in the decompressor — it persists into kernel boot
 * and is idempotent on hardware that already had it set.
 */
#define arch_decomp_setup() do {                                \
	*(volatile unsigned int *)(UART0_BASE + 0x30) = 0x301;  \
} while (0)
#define arch_decomp_wdog()

#endif
