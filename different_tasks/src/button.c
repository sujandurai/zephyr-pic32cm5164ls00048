#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include "button.h"

#define GPIOA_NODE DT_NODELABEL(gpioa)

#define BUTTON_PIN 0    /* PA0 - USER Button */
#define LED_PIN    5    /* PA5 - LD2 */

void button_task(void)
{
    const struct device *gpioa = DEVICE_DT_GET(GPIOA_NODE);

    if (!device_is_ready(gpioa)) {
        return;
    }

    gpio_pin_configure(gpioa, BUTTON_PIN, GPIO_INPUT);
    gpio_pin_configure(gpioa, LED_PIN, GPIO_OUTPUT_INACTIVE);

    while (1) {
        int value = gpio_pin_get(gpioa, BUTTON_PIN);

        gpio_pin_set(gpioa, LED_PIN, value);

        k_msleep(100);
    }
}
