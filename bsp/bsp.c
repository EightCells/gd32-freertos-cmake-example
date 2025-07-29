/**
 * @file bsp.c
 * @author wxh
 * @brief bsp
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "bsp.h"

int bsp_init(void)
{
    /* pre 0~1, sub 0~7 */
    nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);

    /* timer 5 */
    timer5_config();

    /* usart config */
    com_config();

    printf("\r\n\r\n");

    /* gpio config */
    gpio_config();
    printf("LED config success.\r\n");

    /* iic config */
    iic_config();
    printf("IIC config success.\r\n");

    printf("Clock SYS : %d.\r\n", rcu_clock_freq_get(CK_SYS));
    printf("Clock AHB : %d.\r\n", rcu_clock_freq_get(CK_AHB));
    printf("Clock APB1: %d.\r\n", rcu_clock_freq_get(CK_APB1));
    printf("Clock APB2: %d.\r\n", rcu_clock_freq_get(CK_APB2));

    printf("\r\n\r\n");
    printf("  / _ \\   / ____|   | | |    \r\n");
    printf(" | (_) | | |     ___| | |___ \r\n");
    printf("  > _ <  | |    / _ \\ | / __|\r\n");
    printf(" | (_) | | |___|  __/ | \\__ \\\r\n");
    printf("  \\___/   \\_____\\___|_|_|___/\r\n");
    printf("\r\n\r\n");

    return 0;
}