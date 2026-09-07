#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include "gpio.h"

#define GPIOA_NODE DT_NODELABEL(gpioa)
#define GPIOC_NODE DT_NODELABEL(gpioc)

#define INPUT_PIN   13    /* PC13 */
#define OUTPUT_PIN   0    /* PA0 */

void gpio_task(void)
{
    const struct device *gpioa = DEVICE_DT_GET(GPIOA_NODE);
    const struct device *gpioc = DEVICE_DT_GET(GPIOC_NODE);

    if (!device_is_ready(gpioa) || !device_is_ready(gpioc)) {
        return;
    }

    gpio_pin_configure(gpioc, INPUT_PIN, GPIO_INPUT);
    gpio_pin_configure(gpioa, OUTPUT_PIN, GPIO_OUTPUT_INACTIVE);

    while (1) {

        int value = gpio_pin_get(gpioc, INPUT_PIN);

        if (value) {
            gpio_pin_set(gpioa, OUTPUT_PIN, 1);
        } else {
            gpio_pin_set(gpioa, OUTPUT_PIN, 0);
        }

        k_msleep(100);
    }
}
