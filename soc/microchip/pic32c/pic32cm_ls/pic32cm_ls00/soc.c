/*
 * Copyright (c) 2026 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <soc.h>

/*
 * SoC-level initialization for PIC32CM LS00 family.
 * Clocks are initialized by the Zephyr clock_control driver.
 */
static int pic32cm_ls00_init(void)
{
	return 0;
}

SYS_INIT(pic32cm_ls00_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
