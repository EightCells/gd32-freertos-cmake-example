/**
 * @file iic.h
 * @author wang.xuhui
 * @brief the header of iic.c
 * @version 0.1
 * @date 2024-12-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __IIC_H__
#define __IIC_H__

#include "gd32f4xx.h"

#define IIC_N                   1

#define IIC_1_SCL_PORT          GPIOG
#define IIC_1_SDA_PORT          GPIOG
#define IIC_1_SCL_RCU           RCU_GPIOG
#define IIC_1_SDA_RCU           RCU_GPIOG
#define IIC_1_SCL_PIN           GPIO_PIN_1
#define IIC_1_SDA_PIN           GPIO_PIN_0

typedef enum
{
    IIC_1,
} IICxEnum;

void iic_config(void);

void IIC_send(IICxEnum x, \
              uint8_t *write_bytes, uint8_t write_count, \
              uint8_t *read_bytes, uint8_t read_count);

#endif
