/**
 * @file timer.h
 * @author wang.xuhui
 * @brief the header of timer.c
 * @version 0.1
 * @date 2024-11-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include "gd32f4xx.h"

extern volatile uint32_t timer5_delay;

void timer5_config(void);

void delay_us(uint32_t n);

#define delay_ms(n)         delay_us(1000 * n)

#endif
