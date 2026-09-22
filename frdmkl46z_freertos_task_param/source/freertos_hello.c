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
typedef struct
{
	uint32_t idLed;
	uint32_t semiPeriodo;
}taskParam_type;

/* Task priorities. */
//#define task_PRIORITY (configMAX_PRIORITIES - 1)
#define task_PRIORITY tskIDLE_PRIORITY + 1
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void Task1(void *pvParameters);

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Application entry point.
 */

taskParam_type taskParam1;
taskParam_type taskParam2 =
{
	.semiPeriodo = 200,
	.idLed = BOARD_LED_ID_VERDE,
};


int main(void)
{
	taskParam1.idLed = BOARD_LED_ID_ROJO;
	taskParam1.semiPeriodo = 500;

	/* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    if (xTaskCreate(Task1, "Task1", configMINIMAL_STACK_SIZE + 100, &taskParam1, tskIDLE_PRIORITY, NULL) != pdPASS)
    {
    	PRINTF("Task creation failed!.\r\n");
    	while (1)
    		;
    }

    if (xTaskCreate(Task1, "Task2", configMINIMAL_STACK_SIZE + 100, &taskParam2, tskIDLE_PRIORITY, NULL) != pdPASS)
    {
    	PRINTF("Task creation failed!.\r\n");
    	while (1)
    		;
    }



    vTaskStartScheduler();
    for (;;)
        ;
}


/*
extern void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
	while (1);
}
*/

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
static void Task1(void *pvParameters)
{

	taskParam_type *pTaskParam;

		pTaskParam = (taskParam_type*)pvParameters;

		while (1)
		{
			vTaskDelay(pTaskParam->semiPeriodo / portTICK_PERIOD_MS);

			board_setLed(pTaskParam->idLed, BOARD_LED_MSG_TOGGLE);
		}
}




