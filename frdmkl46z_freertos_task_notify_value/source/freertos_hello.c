/*
 * The Clear BSD License
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"

/* SE2 includes. */
#include "SD2_board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
TaskHandle_t xHandlerTask1;
TaskHandle_t xHandlerTask2;

/* Task priorities. */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void task1(void *pvParameters);
static void task2(void *pvParameters);

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Application entry point.
 */
int main(void)
{
    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();



    if (xTaskCreate(task1, "task1", configMINIMAL_STACK_SIZE + 200, NULL, tskIDLE_PRIORITY + 1, &xHandlerTask1) != pdPASS)
    {
    	PRINTF("Task creation failed!.\r\n");
    	while (1)
    		;
    }


    if (xTaskCreate(task2, "task2", configMINIMAL_STACK_SIZE + 200, NULL, tskIDLE_PRIORITY + 1, &xHandlerTask2) != pdPASS)
    {
    	PRINTF("Task creation failed!.\r\n");
    	while (1)
    	    ;
    }

    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
static void task1(void *pvParameters)
{
	while (1)
	{
		xTaskNotifyGive(xHandlerTask2);
		xTaskNotifyGive(xHandlerTask2);
		xTaskNotifyGive(xHandlerTask2);
		xTaskNotifyGive(xHandlerTask2);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

/*!
 * @brief Task responsible for printing of "Hello world 2." message.
 */
static void task2(void *pvParameters)
{
	int notificationValue;

	while (1)
	{
		//notificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Clear notification on exit
		notificationValue = ulTaskNotifyTake(pdFALSE, portMAX_DELAY); // Don´t clear notification on exit

		if(notificationValue > 0)
		{
			PRINTF("Value Received: %d \r\n", notificationValue);
		}


	}
}

extern void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
	while (1);
}

extern void vApplicationIdleHook( void )
{
	//board_setLed(BOARD_LED_ID_VERDE, BOARD_LED_MSG_ON);
}
