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

/* Task priorities. */
#define sw_task_PRIORITY 	tskIDLE_PRIORITY
#define blink_task_PRIORITY tskIDLE_PRIORITY
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void sw_task(void *pvParameters);
static void blink_task(void *pvParameters);

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


    board_init();

    if (xTaskCreate(sw_task, "button_task", configMINIMAL_STACK_SIZE + 200, NULL, sw_task_PRIORITY, NULL) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }

    if (xTaskCreate(blink_task, "blink_task", configMINIMAL_STACK_SIZE + 200, NULL, blink_task_PRIORITY, NULL) != pdPASS)
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
 * @brief Task responsible for printing of "sw task." message.
 */
static void sw_task(void *pvParameters)
{
    for (;;)
    {
        if(board_getSw(BOARD_SW_ID_1))
        {
        	PRINTF("Toggle Red Led.\r\n");
        	board_setLed(BOARD_LED_ID_ROJO, BOARD_LED_MSG_TOGGLE);
        	vTaskDelay(250 / portTICK_PERIOD_MS); // Barrido tarea periódica
        }
        vTaskDelay(100 / portTICK_PERIOD_MS); // Barrido tarea periódica
    }
}

/*!
 * @brief Task responsible for printing of "blink task." message.
 */
static void blink_task(void *pvParameters)
{
    for (;;)
    {
        PRINTF("Blink Green Led.\r\n");
        board_setLed(BOARD_LED_ID_VERDE, BOARD_LED_MSG_TOGGLE);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

