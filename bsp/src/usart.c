/**
 * @file usart.c
 * @author wang.xuhui
 * @brief usart config.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "bsp.h"
#include "rqueue.h"

#define COM_DEF(name) BSP_DEF(COM, name, COM_N)

COM_DEF(BASE);
COM_DEF(CLK);
COM_DEF(GPIO_CLK);
COM_DEF(GPIO_AF);
COM_DEF(TX_PORT);
COM_DEF(TX_PIN);
COM_DEF(RX_PORT);
COM_DEF(RX_PIN);
COM_DEF(IRQn);

static RoundQueue COM_QUEUE[COM_N];
static uint8_t COM_Q_BUFF[COM_N][RX_BUFFER_LENGTH] = {0};

void usart_config(  UsartEnum i,
                    uint32_t baund,
                    uint8_t nvic_pre_pri,
                    uint8_t nvic_sub_pri)
{
    rcu_periph_clock_enable(COM_CLK[i]);
    rcu_periph_clock_enable(COM_GPIO_CLK[i]);

    gpio_mode_set(COM_TX_PORT[i], GPIO_MODE_AF, GPIO_PUPD_NONE, COM_TX_PIN[i]);
    gpio_output_options_set(COM_TX_PORT[i], GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, COM_TX_PIN[i]);
    gpio_af_set(COM_TX_PORT[i], COM_GPIO_AF[i], COM_TX_PIN[i]);

    gpio_mode_set(COM_RX_PORT[i], GPIO_MODE_AF, GPIO_PUPD_NONE, COM_RX_PIN[i]);
    gpio_output_options_set(COM_RX_PORT[i], GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, COM_RX_PIN[i]);
    gpio_af_set(COM_RX_PORT[i], COM_GPIO_AF[i], COM_RX_PIN[i]);

    usart_deinit(COM_BASE[i]);
    usart_baudrate_set(COM_BASE[i], baund);
    usart_receive_config(COM_BASE[i], USART_RECEIVE_ENABLE);
    usart_transmit_config(COM_BASE[i], USART_TRANSMIT_ENABLE);

    nvic_irq_enable(COM_IRQn[i], nvic_pre_pri, nvic_sub_pri);
    usart_interrupt_enable(COM_BASE[i], USART_INT_RBNE);

    queue_init(&COM_QUEUE[i], COM_Q_BUFF[i], RX_BUFFER_LENGTH, sizeof(uint8_t));

    usart_enable(COM_BASE[i]);
}

void com_config(void)
{
    usart_config(MCU_COM, 115200, 0, 2);
    usart_config(PC_COM, 115200, 0, 2);
    usart_config(LCD_COM, 115200, 0, 2);
}

void com_send_byte(UsartEnum i, uint8_t byte)
{
    usart_data_transmit(COM_BASE[i], byte);
    while (RESET == usart_flag_get(COM_BASE[i], USART_FLAG_TBE));
}

int com_send_buff(UsartEnum i, uint8_t *buff, uint16_t len)
{
    uint8_t ch;
    uint32_t com;
    int timeout = 0x2fff;

    com = COM_BASE[i];

    for (uint16_t j = 0; j < len; ++j)
    {
        ch = (uint8_t)buff[j];
        
        usart_data_transmit(com, ch);
        while (RESET == usart_flag_get(com, USART_FLAG_TBE) && (timeout--));

        if (timeout < 0)
        {
            return -1;
        }

        timeout = 0x2fff;
    }

    return len;
}

void *get_com_queue(UsartEnum i)
{
    return &COM_QUEUE[i];
}

void COM_1_IRQHandler(void)
{
    if (usart_interrupt_flag_get(COM_1_BASE, USART_INT_FLAG_RBNE))
    {
        uint8_t d = usart_data_receive(COM_1_BASE);
        enqueue(&COM_QUEUE[MCU_COM], &d);

        usart_interrupt_flag_clear(COM_1_BASE, USART_INT_FLAG_RBNE);
    }
}

void COM_2_IRQHandler(void)
{
    if (usart_interrupt_flag_get(COM_2_BASE, USART_INT_FLAG_RBNE))
    {
        uint8_t d = usart_data_receive(COM_2_BASE);
        enqueue(&COM_QUEUE[LCD_COM], &d);

        usart_interrupt_flag_clear(COM_2_BASE, USART_INT_FLAG_RBNE);
    }
}

void COM_3_IRQHandler(void)
{
    if (usart_interrupt_flag_get(COM_3_BASE, USART_INT_FLAG_RBNE))
    {
        uint8_t d = usart_data_receive(COM_3_BASE);
        enqueue(&COM_QUEUE[PC_COM], &d);

        usart_interrupt_flag_clear(COM_3_BASE, USART_INT_FLAG_RBNE);
    }
}



#ifdef __IAR_SYSTEMS_ICC__
#include <LowLevelIOInterface.h>
// IAR 9.X 以上要求重写__write函数以重定向printf
size_t __write(int handle, const unsigned char * buffer, size_t len)
{
    if (buffer == 0)
    {
        return 0;
    }
    /* This template only writes to "standard out" and "standard err",
     * for all other file handles it returns failure. */
    if (handle != _LLIO_STDOUT && handle != _LLIO_STDERR)
    {
        return _LLIO_ERROR;
    }
    
    uint8_t ch;
    int timeout = 0x1000;
    for (uint16_t i = 0; i < (uint16_t)len; ++i)
    {
        ch = (uint8_t)buffer[i];
        usart_data_transmit(LOG_USART, ch);
        while (RESET == usart_flag_get(LOG_USART, USART_FLAG_TBE) && (timeout--));
        if (timeout < 0)
        {
            return _LLIO_ERROR;
        }
        
        timeout = 0x1000;
    }
    return len;
}
#elif defined(__GNUC__)
int _write(int handle, const unsigned char * buffer, size_t len)
{
    if (buffer == 0)
    {
        return 0;
    }

    uint8_t ch;
    for (uint16_t i = 0; i < (uint16_t)len; ++i)
    {
        ch = (uint8_t)buffer[i];
        usart_data_transmit(COM_BASE[PC_COM], ch);
        while (RESET == usart_flag_get(COM_BASE[PC_COM], USART_FLAG_TBE));
    }
    return len;
}
#endif
