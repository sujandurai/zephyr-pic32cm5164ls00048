#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

static const struct device *pir =
	DEVICE_DT_GET(DT_NODELABEL(pir0));

int main(void)
{
	struct sensor_value val;
	int ret;

	if (!device_is_ready(pir)) {
		printk("PIR not ready\n");
		return 0;
	}

	printk("PIR ready\n");

	while (1) {

		ret = sensor_sample_fetch(pir);
		if (ret) {
			printk("Fetch failed: %d\n", ret);
			k_sleep(K_SECONDS(1));
			continue;
		}

		ret = sensor_channel_get(pir, SENSOR_CHAN_ALL, &val);
		if (ret) {
			printk("Get failed: %d\n", ret);
			k_sleep(K_SECONDS(1));
			continue;
		}

		if (val.val1) {
			printk("Motion Detected\n");
		} else {
			printk("No Motion\n");
		}

		k_sleep(K_SECONDS(1));
	}

	return 0;
}
