/*
 * Copyright (c) 2026
 *`
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT sujan_pir

#include <errno.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(sujan_pir, CONFIG_SENSOR_LOG_LEVEL);

/* Configuration (comes from DeviceTree) */
struct pir_config {
	struct gpio_dt_spec gpio;
};


/* Runtime data */
struct pir_data {
	int motion;
};

/* Initialize the PIR GPIO */
static int pir_init(const struct device *dev)
{
	const struct pir_config *cfg = dev->config;

	if (!gpio_is_ready_dt(&cfg->gpio)) {
		LOG_ERR("GPIO device not ready");
		return -ENODEV;
	}

	return gpio_pin_configure_dt(&cfg->gpio, GPIO_INPUT);
}

/* Read the PIR output */
static int pir_sample_fetch(const struct device *dev,
			    enum sensor_channel chan)
{
	struct pir_data *data = dev->data;
	const struct pir_config *cfg = dev->config;

	ARG_UNUSED(chan);

	data->motion = gpio_pin_get_dt(&cfg->gpio);

	if (data->motion < 0) {
		LOG_ERR("Failed to read PIR GPIO");
		return data->motion;
	}

	return 0;
}

/* Return motion status */
static int pir_channel_get(const struct device *dev,
			   enum sensor_channel chan,
			   struct sensor_value *val)
{
	struct pir_data *data = dev->data;

	switch (chan) {
	case SENSOR_CHAN_PROX:
		val->val1 = data->motion;
		val->val2 = 0;
		return 0;

	default:
		return -ENOTSUP;
	}
}

/* Sensor API */
static DEVICE_API(sensor, pir_driver_api) = {
	.sample_fetch = pir_sample_fetch,
	.channel_get = pir_channel_get,
};

/* Create a driver instance for every PIR node in DeviceTree */
#define PIR_INIT(inst)							\
	static struct pir_data pir_data_##inst;			\
								\
	static const struct pir_config pir_cfg_##inst = {	\
		.gpio = GPIO_DT_SPEC_INST_GET(inst, gpios),	\
	};							\
								\
	SENSOR_DEVICE_DT_INST_DEFINE(inst,			\
				     pir_init,		\
				     NULL,		\
				     &pir_data_##inst,	\
				     &pir_cfg_##inst,	\
				     POST_KERNEL,	\
				     CONFIG_SENSOR_INIT_PRIORITY, \
				     &pir_driver_api);

DT_INST_FOREACH_STATUS_OKAY(PIR_INIT)
