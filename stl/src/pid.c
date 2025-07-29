/**
 * @file pid.c
 * @author wang.xuhui
 * @brief PID control.
 * @version 0.1
 * @date 2025-01-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "pid.h"

// 0:Incremental 1:Positonal
#define PID_METHOD      1

void pid_update(PIDCtrller *pid, double feedback)
{
    // update error list
    pid->E_k_minus_2 = pid->E_k_minus_1;
    pid->E_k_minus_1 = pid->E_k;
    pid->E_k = pid->Target - feedback;

#if PID_METHOD
    static double EkSum = 0;
    EkSum += pid->E_k;
    pid->Out = pid->Kp * pid->E_k + pid->Ki * EkSum + pid->Kd * (pid->E_k - pid->E_k_minus_1);
#else
    double E1 = pid->E_k - pid->E_k_minus_1;
    double E2 = pid->E_k;
    double E3 = pid->E_k - 2 * pid->E_k_minus_1 + pid->E_k_minus_2;

    pid->Out += pid->Kp * E1 + pid->Ki * E2 + pid->Kd * E3;
#endif
    pid->Out = pid->Out > pid->MaxOut ? pid->MaxOut : pid->Out;
    pid->Out = pid->Out < pid->MinOut ? pid->MinOut : pid->Out;
}

