#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <stdint.h>

#define PORTB_BASE 0x44800080UL

#define PORT_DIRSET   (*(volatile uint32_t *)(PORTB_BASE + 0x08))
#define PORT_OUTSET   (*(volatile uint32_t *)(PORTB_BASE + 0x18))
#define PORT_OUTCLR   (*(volatile uint32_t *)(PORTB_BASE + 0x14))
#define PORT_OUTTGL   (*(volatile uint32_t *)(PORTB_BASE + 0x1C))

#define PB02 (1U << 2)

int main(void)
{
	printk("\n");
	printk("=================================\n");
	printk("PIC32CM5164LS PB02 DIRECT TEST\n");
	printk("PORTB = 0x%08lx\n", (unsigned long)PORTB_BASE);
	printk("PB02 mask = 0x%08x\n", PB02);
	printk("=================================\n");

	/* PB02 output */
	PORT_DIRSET = PB02;

	printk("PB02 configured as OUTPUT\n");

	while (1) {
		printk("PB02 HIGH\n");
		PORT_OUTSET = PB02;
		k_msleep(1000);

		printk("PB02 LOW\n");
		PORT_OUTCLR = PB02;
		k_msleep(1000);
	}
}
