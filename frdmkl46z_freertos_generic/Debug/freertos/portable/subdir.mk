################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/portable/fsl_tickless_systick.c 

OBJS += \
./freertos/portable/fsl_tickless_systick.o 

C_DEPS += \
./freertos/portable/fsl_tickless_systick.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/portable/%.o: ../freertos/portable/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DFSL_RTOS_FREE_RTOS -DCPU_MKL46Z256VLL4_cm0plus -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_generic\board" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_generic\source" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_generic" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_generic\drivers" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_generic\CMSIS" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_generic\startup" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_generic\utilities" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_generic\amazon-freertos\FreeRTOS\portable" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_generic\freertos\portable" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_generic\amazon-freertos\include" -I"C:\Users\Daniel\Downloads\FreeRTOS_Workspace\frdmkl46z_freertos_generic\board\src" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


