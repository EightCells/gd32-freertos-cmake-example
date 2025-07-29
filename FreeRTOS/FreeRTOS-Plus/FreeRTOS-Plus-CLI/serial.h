/**
 * @file serial.h
 * @author wxh
 * @brief FreeRTOS-CLI need
 * @version 0.1
 * @date 2025-07-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "bsp.h"
#include "rqueue.h"

#define xComPortHandle  UsartEnum

UsartEnum xSerialPortInitMinimal(uint32_t baundrate, uint16_t queuelen);

#define xSerialPutChar(com,ch,delay)        com_send_buff(com,&ch,1)
#define vSerialPutString(com,buf,len)       com_send_buff(com,buf,len)

bool xSerialGetChar(UsartEnum com, uint8_t *ch, uint32_t delay);

#endif
