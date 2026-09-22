################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c \
../utilities/fsl_debug_console.c \
../utilities/fsl_io.c \
../utilities/fsl_log.c \
../utilities/fsl_str.c 

OBJS += \
./utilities/fsl_assert.o \
./utilities/fsl_debug_console.o \
./utilities/fsl_io.o \
./utilities/fsl_log.o \
./utilities/fsl_str.o 

C_DEPS += \
./utilities/fsl_assert.d \
./utilities/fsl_debug_console.d \
./utilities/fsl_io.d \
./utilities/fsl_log.d \
./utilities/fsl_str.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DFSL_RTOS_FREE_RTOS -DCPU_MKL46Z256VLL4_cm0plus -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_uart_irq_sema_process\board" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_uart_irq_sema_process\source" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_uart_irq_sema_process" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_uart_irq_sema_process\drivers" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_uart_irq_sema_process\CMSIS" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_uart_irq_sema_process\startup" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_uart_irq_sema_process\utilities" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_uart_irq_sema_process\amazon-freertos\FreeRTOS\portable" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_uart_irq_sema_process\freertos\portable" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_uart_irq_sema_process\amazon-freertos\include" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_uart_irq_sema_process\board\src" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


