################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mkl46z4.c 

OBJS += \
./startup/startup_mkl46z4.o 

C_DEPS += \
./startup/startup_mkl46z4.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DFSL_RTOS_FREE_RTOS -DCPU_MKL46Z256VLL4_cm0plus -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_task_param\board" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_task_param\source" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_task_param" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_task_param\drivers" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_task_param\CMSIS" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_task_param\startup" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_task_param\utilities" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_task_param\amazon-freertos\FreeRTOS\portable" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_task_param\freertos\portable" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_task_param\amazon-freertos\include" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_task_param\board\src" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


