/**
 * @file gpio.c
 * @author wxh
 * @brief GPIO config.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "bsp.h"

#define GPIO_DEF(group, n)  BSP_DEF(group, PORT, n); \
                            BSP_DEF(group, PIN, n); \
                            BSP_DEF(group, CLK, n)


void gpio_clk_config(void)
{
    rcu_periph_clock_enable(LED_CLK);
}

void gpio_config(void)
{
    gpio_clk_config();

    gpio_mode_set(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
    gpio_output_options_set(LED_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LED_PIN);
    gpio_bit_reset(LED_PORT, LED_PIN);
}

void led_light(uint8_t b)
{
    b ? \
    gpio_bit_set(LED_PORT, LED_PIN) : \
    gpio_bit_reset(LED_PORT, LED_PIN);
}
