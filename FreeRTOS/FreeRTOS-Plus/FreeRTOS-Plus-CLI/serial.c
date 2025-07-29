/**
 * @file serial.c
 * @author wxh
 * @brief bsp usart to FreeRTOS-CLI serial api convert
 * @version 0.1
 * @date 2025-07-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "serial.h"

UsartEnum xSerialPortInitMinimal(uint32_t baundrate, uint16_t queuelen)
{
    return PC_COM;
}

bool xSerialGetChar(UsartEnum com, uint8_t *ch, uint32_t delay)
{
    RoundQueue_t q = (RoundQueue_t)get_com_queue(com);

    if (queue_empty(q)) return false;

    *ch = *(uint8_t *)dequeue(q);

    return true;
}

