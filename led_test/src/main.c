/*
 * Copyright (c) 2026 Microchip Technology Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <stdint.h>

/* Direct register addresses for PIC32CM LS00 (SAM L10/L11 architecture) */
#define MCLK_BASE         0x40000800UL
#define MCLK_APBAMASK     (*(volatile uint32_t *)(MCLK_BASE + 0x14U))
#define MCLK_APBBMASK     (*(volatile uint32_t *)(MCLK_BASE + 0x18U))
#define MCLK_APBCMASK     (*(volatile uint32_t *)(MCLK_BASE + 0x1CU))

/* PORT A & PORT B Base Registers (Non-Secure and Secure aliases) */
#define PORTA_BASE_NS     0x40003200UL
#define PORTB_BASE_NS     0x40003280UL
#define PORTB_BASE_SEC    0x50003280UL

#define PORT_DIRSET(base)   (*(volatile uint32_t *)((base) + 0x08U))
#define PORT_OUTTGL(base)   (*(volatile uint32_t *)((base) + 0x1CU))
#define PORT_OUTCLR(base)   (*(volatile uint32_t *)((base) + 0x14U))
#define PORT_OUTSET(base)   (*(volatile uint32_t *)((base) + 0x18U))
#define PORT_PINCFG(base, pin) (*(volatile uint8_t *)((base) + 0x40U + (pin)))

#define PB02_MASK  (1U << 2)
#define PA15_MASK  (1U << 15)

/* Zephyr GPIO Devicetree */
#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

/* Software delay loop that works even if SysTick / RTOS timer is not running */
static void delay_cycles(volatile uint32_t count)
{
	while (count--) {
		__asm__ volatile("nop");
	}
}

int main(void)
{
	int count = 0;

	printk("\n");
	printk("********************************************\n");
	printk("PIC32CM5164LS00048 FORCED LED BLINK RUNNING\n");
	printk("********************************************\n");

	/* 1. Ensure all APB peripheral clocks are enabled in MCLK */
	MCLK_APBAMASK = 0xFFFFFFFF;
	MCLK_APBBMASK = 0xFFFFFFFF;
	MCLK_APBCMASK = 0xFFFFFFFF;

	/* 2. Configure PB02 directly on hardware registers (both NS and Secure) */
	PORT_DIRSET(PORTB_BASE_NS) = PB02_MASK;
	PORT_DIRSET(PORTB_BASE_SEC) = PB02_MASK;
	PORT_DIRSET(PORTA_BASE_NS) = PA15_MASK;

	/* Disable PMUX so pin is in GPIO mode */
	PORT_PINCFG(PORTB_BASE_NS, 2) = 0;
	PORT_PINCFG(PORTB_BASE_SEC, 2) = 0;
	PORT_PINCFG(PORTA_BASE_NS, 15) = 0;

	/* 3. Also configure via Zephyr GPIO driver */
	if (gpio_is_ready_dt(&led0)) {
		gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
		printk("Zephyr GPIO driver configured LED0 (PB02)\n");
	} else {
		printk("Zephyr GPIO driver not ready, using direct register fallback\n");
	}

	while (1) {
		count++;

		/* Direct toggle PB02 (Non-Secure and Secure) + PA15 */
		PORT_OUTTGL(PORTB_BASE_NS) = PB02_MASK;
		PORT_OUTTGL(PORTB_BASE_SEC) = PB02_MASK;
		PORT_OUTTGL(PORTA_BASE_NS) = PA15_MASK;

		/* Also toggle via Zephyr API if ready */
		if (gpio_is_ready_dt(&led0)) {
			gpio_pin_toggle_dt(&led0);
		}

		printk("Blink iteration #%d: PB02 Toggled!\n", count);

		/* Reliable delay (500ms equivalent at 48MHz CPU clock) */
		delay_cycles(4000000);
	}

	return 0;
}
