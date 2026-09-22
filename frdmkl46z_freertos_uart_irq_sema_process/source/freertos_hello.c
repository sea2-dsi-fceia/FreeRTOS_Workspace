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
#include "fsl_port.h"
#include "fsl_lpsci.h"

#include "pin_mux.h"

/* SE2 includes. */
#include "SD2_board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
SemaphoreHandle_t semTask;
static uint8_t rxChar;

/* Task priorities. */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void Blink(void *pvParameters);
static void Uart_Process(void *pvParameters);
static void UART0_init(void);

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

    UART0_init();

    semTask = xSemaphoreCreateBinary();

    if (xTaskCreate(Blink, "Blink", configMINIMAL_STACK_SIZE + 200, NULL, tskIDLE_PRIORITY, NULL) != pdPASS)
    {
    	PRINTF("Task creation failed!.\r\n");
    	while (1)
    		;
    }


    if (xTaskCreate(Uart_Process, "UartProcess", configMINIMAL_STACK_SIZE + 200, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
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
 * @brief Task responsible for printing of "Uart Process." message.
 */
static void Uart_Process(void *pvParameters)
{
	uint32_t i;
	uint32_t cuenta;

	xSemaphoreTake(semTask, 0);

    while (1)
    {
    	xSemaphoreTake(semTask, portMAX_DELAY);

    	for (cuenta = 0; cuenta < 20; cuenta++)
    	{
    		PRINTF("Red Led Toggle.\r\n");
    		board_setLed(BOARD_LED_ID_ROJO, BOARD_LED_MSG_TOGGLE);

    		i = 500000;
    		while (i--);
    	}

    	xSemaphoreTake(semTask, 0);

    }
}



/*!
 * @brief Task responsible for printing of "Blink." message.
 */
static void Blink(void *pvParameters)
{
	while (1)
	{
		vTaskDelay(500 / portTICK_PERIOD_MS);
		PRINTF("Green Led Toggle.\r\n");
		board_setLed(BOARD_LED_ID_VERDE, BOARD_LED_MSG_TOGGLE);

	}
}

extern void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
	while (1);
}

extern void vApplicationIdleHook( void )
{
}



void UART0_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;


	/* If new data arrived. */
    if ((kLPSCI_RxDataRegFullFlag)&LPSCI_GetStatusFlags(UART0))
    {
    	rxChar = LPSCI_ReadByte(UART0);
    	xSemaphoreGiveFromISR(semTask, &xHigherPriorityTaskWoken);

    	/* Yield if xHigherPriorityTaskWoken is true.  The
    	actual macro used here is port specific. */
    	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    }
}



static void UART0_init(void)
{
	lpsci_config_t config;

	CLOCK_SetLpsci0Clock(0x1U);


	/* PORTA1 (pin 35) is configured as UART0_RX */
	PORT_SetPinMux(PORTA, 1U, kPORT_MuxAlt2);

	/* PORTA2 (pin 36) is configured as UART0_TX */
	PORT_SetPinMux(PORTA, 2U, kPORT_MuxAlt2);

	/*
	 * config.parityMode = kLPSCI_ParityDisabled;
	 * config.stopBitCount = kLPSCI_OneStopBit;
	 * config.enableTx = false;
	 * config.enableRx = false;
	 */
	LPSCI_GetDefaultConfig(&config);
	config.baudRate_Bps = 9600;
	config.enableTx = true;
	config.enableRx = true;

	LPSCI_Init(UART0, &config, CLOCK_GetFreq(kCLOCK_CoreSysClk));

	/* Enable RX interrupt. */
	LPSCI_EnableInterrupts(UART0, kLPSCI_RxDataRegFullInterruptEnable);
	EnableIRQ(UART0_IRQn);
}
