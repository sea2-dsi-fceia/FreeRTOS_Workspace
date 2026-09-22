################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../amazon-freertos/FreeRTOS/portable/heap_4.c \
../amazon-freertos/FreeRTOS/portable/port.c 

C_DEPS += \
./amazon-freertos/FreeRTOS/portable/heap_4.d \
./amazon-freertos/FreeRTOS/portable/port.d 

OBJS += \
./amazon-freertos/FreeRTOS/portable/heap_4.o \
./amazon-freertos/FreeRTOS/portable/port.o 


# Each subdirectory must supply rules for building sources it contributes
amazon-freertos/FreeRTOS/portable/%.o: ../amazon-freertos/FreeRTOS/portable/%.c amazon-freertos/FreeRTOS/portable/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DFSL_RTOS_FREE_RTOS -DCPU_MKL46Z256VLL4_cm0plus -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Usuario\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_hello\board" -I"C:\Users\Usuario\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_hello\source" -I"C:\Users\Usuario\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_hello" -I"C:\Users\Usuario\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_hello\drivers" -I"C:\Users\Usuario\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_hello\CMSIS" -I"C:\Users\Usuario\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_hello\startup" -I"C:\Users\Usuario\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_hello\utilities" -I"C:\Users\Usuario\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_hello\amazon-freertos\FreeRTOS\portable" -I"C:\Users\Usuario\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_hello\freertos\portable" -I"C:\Users\Usuario\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_hello\amazon-freertos\include" -I"C:\Users\Usuario\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_hello\board\src" -O0 -fno-common -g -gdwarf-4 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-amazon-2d-freertos-2f-FreeRTOS-2f-portable

clean-amazon-2d-freertos-2f-FreeRTOS-2f-portable:
	-$(RM) ./amazon-freertos/FreeRTOS/portable/heap_4.d ./amazon-freertos/FreeRTOS/portable/heap_4.o ./amazon-freertos/FreeRTOS/portable/port.d ./amazon-freertos/FreeRTOS/portable/port.o

.PHONY: clean-amazon-2d-freertos-2f-FreeRTOS-2f-portable

