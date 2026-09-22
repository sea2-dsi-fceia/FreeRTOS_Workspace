################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/system_MKL46Z4.c 

OBJS += \
./CMSIS/system_MKL46Z4.o 

C_DEPS += \
./CMSIS/system_MKL46Z4.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/%.o: ../CMSIS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DFSL_RTOS_FREE_RTOS -DCPU_MKL46Z256VLL4_cm0plus -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Daniel\Downloads\RTOS_Workspace\frdmkl46z_freertos_event\board" -I"C:\Users\Daniel\Downloads\RTOS_Workspace\frdmkl46z_freertos_event\source" -I"C:\Users\Daniel\Downloads\RTOS_Workspace\frdmkl46z_freertos_event" -I"C:\Users\Daniel\Downloads\RTOS_Workspace\frdmkl46z_freertos_event\drivers" -I"C:\Users\Daniel\Downloads\RTOS_Workspace\frdmkl46z_freertos_event\CMSIS" -I"C:\Users\Daniel\Downloads\RTOS_Workspace\frdmkl46z_freertos_event\startup" -I"C:\Users\Daniel\Downloads\RTOS_Workspace\frdmkl46z_freertos_event\utilities" -I"C:\Users\Daniel\Downloads\RTOS_Workspace\frdmkl46z_freertos_event\amazon-freertos\FreeRTOS\portable" -I"C:\Users\Daniel\Downloads\RTOS_Workspace\frdmkl46z_freertos_event\freertos\portable" -I"C:\Users\Daniel\Downloads\RTOS_Workspace\frdmkl46z_freertos_event\amazon-freertos\include" -I"C:\Users\Daniel\Downloads\RTOS_Workspace\frdmkl46z_freertos_event\board\src" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


