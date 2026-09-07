#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

int main(void)
{
	int count = 0;

	if (gpio_is_ready_dt(&led)) {
		gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	}

	while (1) {
		printk("Hello World from PIC32CM LS00 Curiosity Nano! Count: %d\r\n", count++);
		if (gpio_is_ready_dt(&led)) {
			gpio_pin_toggle_dt(&led);
		}
		k_sleep(K_MSEC(1000));
	}

	return 0;
}