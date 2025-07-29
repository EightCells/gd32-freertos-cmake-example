/**
 * @file timer.c
 * @author wang.xuhui
 * @brief timer config, provide 1us delay
 * @version 0.1
 * @date 2024-12-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "bsp.h"

volatile uint32_t timer5_delay = 0;

void timer5_config(void)
{
    rcu_periph_clock_enable(RCU_TIMER5);

    timer_parameter_struct timer_para;
    timer_para.prescaler = 99;
    timer_para.period = 1;
    timer_para.clockdivision = TIMER_CKDIV_DIV1;
    timer_para.alignedmode = TIMER_COUNTER_EDGE;
    timer_para.counterdirection = TIMER_COUNTER_UP;
    timer_para.repetitioncounter = 0;
    timer_init(TIMER5, &timer_para);

    nvic_irq_enable(TIMER5_DAC_IRQn, 0, 0);
    timer_interrupt_flag_clear(TIMER5, TIMER_INT_FLAG_UP);
    timer_interrupt_enable(TIMER5, TIMER_INT_UP);

    timer_enable(TIMER5);
}

void delay_us(uint32_t n)
{
    timer5_delay = n;
    while (timer5_delay);
}

void TIMER5_DAC_IRQHandler(void)
{
    static uint16_t g_sum = 0;
    if (SET == timer_interrupt_flag_get(TIMER5, TIMER_INT_FLAG_UP))
    {
        timer_interrupt_flag_clear(TIMER5, TIMER_INT_FLAG_UP);

        if (0U != timer5_delay) timer5_delay--;
    }
}
