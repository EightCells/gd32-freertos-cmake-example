/**
 * @file main.c
 * @author wang.xuhui
 * @brief main function entry
 * @version 0.1
 * @date 2024-11-18
 */

#include "gd32f4xx.h"
#include "bsp.h"
/* FreeRTOS includes. */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <semphr.h>
#include <FreeRTOS_CLI.h>

/*-----------------------------------------------------------*/
static StaticTask_t LEDTaskTCB;
static StackType_t LEDTaskStack[configMINIMAL_STACK_SIZE];
static void LEDTask( void * parameters )
{
    for( ; ; )
    {
        static bool bit = 0;
        led_light(bit);
        bit = !bit;
        vTaskDelay(500);
    }
}
/*-----------------------------------------------------------*/

void main( void )
{
    bsp_init();

    vRegisterSampleCLICommands(  );
	vUARTCommandConsoleStart(1024, 0);

    xTaskCreateStatic(  LEDTask,
                        "led",
                        configMINIMAL_STACK_SIZE,
                        NULL,
                        0,
                        &(LEDTaskStack[0]),
                        &(LEDTaskTCB));

    /* Start the scheduler. */
    vTaskStartScheduler();

    for( ; ; )
    {
        /* Should not reach here. */
    }
}

