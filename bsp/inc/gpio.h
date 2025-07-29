/**
 * @file gpio.h
 * @author wxh
 * @brief the header of gpio.c.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#include "gd32f4xx.h"

#define LED_PORT            GPIOD
#define LED_PIN             GPIO_PIN_1
#define LED_CLK             RCU_GPIOD

void gpio_config(void);

void led_light(uint8_t b);

#endif
