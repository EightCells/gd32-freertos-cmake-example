/**
 * @file usart.h
 * @author wang.xuhui
 * @brief the header of usart.c
 * @version 0.1
 * @date 2025-05-06
 */

#ifndef __USART_H__
#define __USART_H__

#include "gd32f4xx.h"

#define RX_BUFFER_LENGTH                    128

#define COM_N                               3

#define COM_1_BASE                          USART0
#define COM_1_CLK                           RCU_USART0
#define COM_1_GPIO_CLK                      RCU_GPIOA
#define COM_1_GPIO_AF                       GPIO_AF_7
#define COM_1_TX_PORT                       GPIOA
#define COM_1_TX_PIN                        GPIO_PIN_9
#define COM_1_RX_PORT                       GPIOA
#define COM_1_RX_PIN                        GPIO_PIN_10
#define COM_1_IRQn                          USART0_IRQn
#define COM_1_IRQHandler                    USART0_IRQHandler

#define COM_2_BASE                          USART1
#define COM_2_CLK                           RCU_USART1
#define COM_2_GPIO_CLK                      RCU_GPIOD
#define COM_2_GPIO_AF                       GPIO_AF_7
#define COM_2_TX_PORT                       GPIOD
#define COM_2_TX_PIN                        GPIO_PIN_5
#define COM_2_RX_PORT                       GPIOD
#define COM_2_RX_PIN                        GPIO_PIN_6
#define COM_2_IRQn                          USART1_IRQn
#define COM_2_IRQHandler                    USART1_IRQHandler

#define COM_3_BASE                          USART2
#define COM_3_CLK                           RCU_USART2
#define COM_3_GPIO_CLK                      RCU_GPIOD
#define COM_3_GPIO_AF                       GPIO_AF_7
#define COM_3_TX_PORT                       GPIOD
#define COM_3_TX_PIN                        GPIO_PIN_8
#define COM_3_RX_PORT                       GPIOD
#define COM_3_RX_PIN                        GPIO_PIN_9
#define COM_3_IRQn                          USART2_IRQn
#define COM_3_IRQHandler                    USART2_IRQHandler


typedef enum
{
    MCU_COM,
    LCD_COM,
    PC_COM,
} UsartEnum;

void com_config(void);

void com_send_byte(UsartEnum i, uint8_t byte);
int com_send_buff(UsartEnum i, uint8_t *buff, uint16_t len);

void *get_com_queue(UsartEnum i);

#endif /* __USART_H__ */
