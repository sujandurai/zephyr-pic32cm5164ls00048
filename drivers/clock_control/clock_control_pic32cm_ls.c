/*
 * Copyright (c) 2026 Microchip Technology Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT microchip_pic32cm_ls_clock

#include <zephyr/init.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/device.h>
#include <soc.h>

static int clock_control_pic32cm_ls_on(const struct device *dev,
				       clock_control_subsys_t sys)
{
	return 0;
}

static int clock_control_pic32cm_ls_off(const struct device *dev,
					clock_control_subsys_t sys)
{
	return 0;
}

static int clock_control_pic32cm_ls_get_rate(const struct device *dev,
					     clock_control_subsys_t sys,
					     uint32_t *rate)
{
	*rate = 48000000UL;
	return 0;
}

static const struct clock_control_driver_api clock_control_pic32cm_ls_api = {
	.on = clock_control_pic32cm_ls_on,
	.off = clock_control_pic32cm_ls_off,
	.get_rate = clock_control_pic32cm_ls_get_rate,
};

static int clock_control_pic32cm_ls_init(const struct device *dev)
{
	return 0;
}

DEVICE_DT_INST_DEFINE(0, clock_control_pic32cm_ls_init, NULL, NULL, NULL,
		      PRE_KERNEL_1, CONFIG_CLOCK_CONTROL_INIT_PRIORITY,
		      &clock_control_pic32cm_ls_api);
