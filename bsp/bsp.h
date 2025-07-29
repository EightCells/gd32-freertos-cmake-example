/**
 * @file bsp.h
 * @author wang.xuhui
 * @brief the header of bsp.c
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __BSP_H__
#define __BSP_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "def.h"
#include "gpio.h"
#include "timer.h"
#include "usart.h"
#include "iic.h"

#define BSP_DEF(group, name, n)     static uint32_t group##_##name[n] = {GENERATE_ARRAY_S(group, n, name)}

#define BSP_GET(group, name, n)     group##_##n##_##name

int bsp_init(void);

#endif



