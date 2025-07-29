/*
 * FreeRTOS Kernel V11.1.0
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>

/******************************************************************************/
/* Hardware description related definitions. **********************************/
/******************************************************************************/

// 实际CPU内核时钟频率
#define configCPU_CLOCK_HZ    ( ( unsigned long ) 200000000 )

/******************************************************************************/
/* Scheduling behaviour related definitions. **********************************/
/******************************************************************************/

// 1s中断的次数
#define configTICK_RATE_HZ                         ( 1000U )

// 调度器：抢占式 1 协作式 0
#define configUSE_PREEMPTION                       1

// 1 使能时间片调度(默认是使能的)，若设置为0，相同优先级的任务不会自动切换
#define configUSE_TIME_SLICING                     1

// 是否使用硬件计算前导0的方式选择下一个可执行任务
#define configUSE_PORT_OPTIMISED_TASK_SELECTION    1

// 置1：使能低功耗tickless 模式；置0：保持系统节拍（tick）中断一直运行 
#define configUSE_TICKLESS_IDLE                    0

// 可用的最大优先级
#define configMAX_PRIORITIES                       32U

// 任务的堆栈的最小值
#define configMINIMAL_STACK_SIZE                   128U

// 任务名称最大长度
#define configMAX_TASK_NAME_LEN                    16U

// 系统节拍计数器变量的数据类型，可选 TICK_TYPE_WIDTH_16_BITS；TICK_TYPE_WIDTH_32_BITS；TICK_TYPE_WIDTH_64_BITS
#define configTICK_TYPE_WIDTH_IN_BITS              TICK_TYPE_WIDTH_32_BITS

// 空闲任务放弃CPU使用权给其他同级任务（建议所有其他任务的优先级高于空闲任务）
#define configIDLE_SHOULD_YIELD                    1

// 每项 RTOS 任务都有一个任务通知数组可用于设置数组中的索引数。
#define configTASK_NOTIFICATION_ARRAY_ENTRIES      1U

// 队列和信号量的最大数量
#define configQUEUE_REGISTRY_SIZE                  10U

/**
 * FreeRTOS.h 头文件包含一组 #define 宏，用于将 FreeRTOS 8.0.0 之前版本中使用的数据类型名称映射到 FreeRTOS 8.0.0 版本中使用的名称。
 * 借助这些宏，无需修改应用程序代码， 即可将 FreeRTOS 8.0.0 之前的版本更新为 8.0.0 之后版本。将 configENABLE_BACKWARD_COMPATIBILITY
 * 设置为 0（在 FreeRTOSConfig.h 中）可从构建中排除这些宏， 从而确保没有使用 8.0.0 版本之前的名称。
 */
#define configENABLE_BACKWARD_COMPATIBILITY        0

// 设置每项任务的线程本地存储数组中的索引数。
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS    0

// 设置在调用 xTaskCreate() 时用于指定堆栈深度的类型
#define configSTACK_DEPTH_TYPE                     size_t

// FreeRTOS 消息缓冲区使用 类型
#define configMESSAGE_BUFFER_LENGTH_TYPE           size_t

// 是否使能 Newlib 支持
#define configUSE_NEWLIB_REENTRANT                 0

/******************************************************************************/
/* Software timer related definitions. ****************************************/
/******************************************************************************/

// 使能软件定时器
#define configUSE_TIMERS                0
#define configTIMER_TASK_PRIORITY       ( configMAX_PRIORITIES - 1U )
#define configTIMER_TASK_STACK_DEPTH    configMINIMAL_STACK_SIZE
#define configTIMER_QUEUE_LENGTH        10U

/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/

#define configSUPPORT_STATIC_ALLOCATION              1
#define configSUPPORT_DYNAMIC_ALLOCATION             1
#define configTOTAL_HEAP_SIZE                        (1024U * 32)
#define configAPPLICATION_ALLOCATED_HEAP             0
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP    0
#define configUSE_MINI_LIST_ITEM                     0

/******************************************************************************/
/* Interrupt nesting behaviour configuration. *********************************/
/******************************************************************************/

#define configKERNEL_INTERRUPT_PRIORITY          0U
#define configMAX_SYSCALL_INTERRUPT_PRIORITY     0U
#define configMAX_API_CALL_INTERRUPT_PRIORITY    0U
/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/

#define configUSE_IDLE_HOOK                   0
#define configUSE_TICK_HOOK                   0
#define configUSE_MALLOC_FAILED_HOOK          0
#define configUSE_DAEMON_TASK_STARTUP_HOOK    0
#define configCHECK_FOR_STACK_OVERFLOW        0

/******************************************************************************/
/* Run time and task stats gathering related definitions. *********************/
/******************************************************************************/

#define configGENERATE_RUN_TIME_STATS           0
#define configUSE_TRACE_FACILITY                1
#define configUSE_STATS_FORMATTING_FUNCTIONS    1
#define configKERNEL_PROVIDED_STATIC_MEMORY     1
#define configSTATS_BUFFER_MAX_LENGTH           1024U

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/

// 任务通知
#define configUSE_TASK_NOTIFICATIONS           1
// 互斥量
#define configUSE_MUTEXES                      1
// 递归互斥锁
#define configUSE_RECURSIVE_MUTEXES            0
// 计数信号量
#define configUSE_COUNTING_SEMAPHORES          1
// 队列集功能（即 在多个队列和信号量上阻塞或挂起的能力）
#define configUSE_QUEUE_SETS                   0
// 任务标签（Task Tag）功能。
// 任务标签允许用户为每个任务关联一个整数值（通常是一个指针），该值可以被用于多种目的，如任务识别、存储与任务相关的数据或回调函数等。
#define configUSE_APPLICATION_TASK_TAG         0

// 包含更改任务优先级的功能
#define INCLUDE_vTaskPrioritySet               1
// 包含获取任务优先级的功能
#define INCLUDE_uxTaskPriorityGet              1
// 包含删除任务的功能
#define INCLUDE_vTaskDelete                    1
// 包含挂起任务的功能
#define INCLUDE_vTaskSuspend                   1
// 包含任务中断恢复函数，即重新启用挂起的任务
#define INCLUDE_xTaskResumeFromISR             1
// 包含绝对延时函数
#define INCLUDE_vTaskDelayUntil                1
// 包含基础延时函数
#define INCLUDE_vTaskDelay                     1
// 包含调度器状态查询函数
#define INCLUDE_xTaskGetSchedulerState         1
// 包含获取当前任务句柄函数
#define INCLUDE_xTaskGetCurrentTaskHandle      1
// 包含栈高水位检测函数，可检测任务最大栈用量（防溢出）
#define INCLUDE_uxTaskGetStackHighWaterMark    1
// 包含获取空闲任务句柄函数
#define INCLUDE_xTaskGetIdleTaskHandle         1
// 包含任务状态查询函数
#define INCLUDE_eTaskGetState                  1
// 包含事件组中断置位函数
#define INCLUDE_xEventGroupSetBitFromISR       1
// 包含定时器守护任务委托函数
#define INCLUDE_xTimerPendFunctionCall         0
// 包含强制终止任务延时函数
#define INCLUDE_xTaskAbortDelay                1
// 包含任务句柄查询函数，可通过任务名获取其 TCB 指针
#define INCLUDE_xTaskGetHandle                 1

#endif /* FREERTOS_CONFIG_H */
