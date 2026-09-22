################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../amazon-freertos/FreeRTOS/portable/heap_4.c \
../amazon-freertos/FreeRTOS/portable/port.c 

OBJS += \
./amazon-freertos/FreeRTOS/portable/heap_4.o \
./amazon-freertos/FreeRTOS/portable/port.o 

C_DEPS += \
./amazon-freertos/FreeRTOS/portable/heap_4.d \
./amazon-freertos/FreeRTOS/portable/port.d 


# Each subdirectory must supply rules for building sources it contributes
amazon-freertos/FreeRTOS/portable/%.o: ../amazon-freertos/FreeRTOS/portable/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DFSL_RTOS_FREE_RTOS -DCPU_MKL46Z256VLL4_cm0plus -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_queue\board" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_queue\source" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_queue" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_queue\drivers" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_queue\CMSIS" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_queue\startup" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_queue\utilities" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_queue\amazon-freertos\FreeRTOS\portable" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_queue\freertos\portable" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_queue\amazon-freertos\include" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_queue\board\src" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


