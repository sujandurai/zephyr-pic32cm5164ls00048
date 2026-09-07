#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#define LED_PIN_PA15 15
#define LED_PIN_PB02 2

static const struct device *porta = DEVICE_DT_GET(DT_NODELABEL(porta));
static const struct device *portb = DEVICE_DT_GET(DT_NODELABEL(portb));

int main(void)
{
	int ret_a = -1, ret_b = -1;

	printk("\n=========================================\n");
	printk("PIC32CM5164LS GPIO BLINK TEST\n");
	printk("=========================================\n");

	if (device_is_ready(porta)) {
		printk("PORTA READY\n");
		ret_a = gpio_pin_configure(porta, LED_PIN_PA15, GPIO_OUTPUT_ACTIVE);
		printk("PA15 (User LED) configure = %d\n", ret_a);
	}

	if (device_is_ready(portb)) {
		printk("PORTB READY\n");
		ret_b = gpio_pin_configure(portb, LED_PIN_PB02, GPIO_OUTPUT_ACTIVE);
		printk("PB02 configure = %d\n", ret_b);
	}

	while (1) {
		printk("LED ON (active low -> pin LOW)\n");
		if (ret_a == 0) {
			gpio_pin_set_raw(porta, LED_PIN_PA15, 0);
		}
		if (ret_b == 0) {
			gpio_pin_set_raw(portb, LED_PIN_PB02, 0);
		}
		k_msleep(500);

		printk("LED OFF (active low -> pin HIGH)\n");
		if (ret_a == 0) {
			gpio_pin_set_raw(porta, LED_PIN_PA15, 1);
		}
		if (ret_b == 0) {
			gpio_pin_set_raw(portb, LED_PIN_PB02, 1);
		}
		k_msleep(500);
	}
}
