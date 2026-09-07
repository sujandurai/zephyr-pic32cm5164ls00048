#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACK_SIZE 1024
#define PRIORITY   5

void task1(void *p1, void *p2, void *p3)
{
    while (1) {
        printk("Task 1: Running every 500 ms\n");
        k_msleep(500);
    }
}

void task2(void *p1, void *p2, void *p3)
{
    while (1) {
        printk("Task 2: Running every 1000 ms\n");
        k_msleep(1000);
    }
}

K_THREAD_DEFINE(task1_id,
                STACK_SIZE,
                task1,
                NULL, NULL, NULL,
                PRIORITY,
                0,
                0);

K_THREAD_DEFINE(task2_id,
                STACK_SIZE,
                task2,
                NULL, NULL, NULL,
                PRIORITY,
                0,
                0);

int main(void)
{
    printk("Zephyr RTOS Thread Example\n");
    return 0;
}
