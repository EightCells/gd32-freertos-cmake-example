/**
 * @file pid.h
 * @author wang.xuhui
 * @brief the header of pid.c
 * @version 0.1
 * @date 2025-01-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __PID_H__
#define __PID_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct st_PID
{
    double    Kp;
    double    Ki;
    double    Kd;

    uint32_t  Ts;

    double    E_k_minus_2;
    double    E_k_minus_1;
    double    E_k;

    double    Target;

    double    Out;
    double    MaxOut;
    double    MinOut;
} PIDCtrller;

void pid_update(PIDCtrller *pid, double feedback);

#endif
