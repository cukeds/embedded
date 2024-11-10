################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Juan/STM32CubeIDE/workspace_1.16.0/Common/Src/Util.c \
C:/Users/Juan/STM32CubeIDE/workspace_1.16.0/Common/Src/bsp_rf.c \
C:/Users/Juan/STM32CubeIDE/workspace_1.16.0/Common/Src/nrf24.c 

C_DEPS += \
./ExtSrc/Util.d \
./ExtSrc/bsp_rf.d \
./ExtSrc/nrf24.d 

OBJS += \
./ExtSrc/Util.o \
./ExtSrc/bsp_rf.o \
./ExtSrc/nrf24.o 


# Each subdirectory must supply rules for building sources it contributes
ExtSrc/Util.o: C:/Users/Juan/STM32CubeIDE/workspace_1.16.0/Common/Src/Util.c ExtSrc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../../Common/Inc -I"C:/Users/Juan/STM32CubeIDE/workspace_1.16.0/SSE-Disc/Core/app" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ExtSrc/bsp_rf.o: C:/Users/Juan/STM32CubeIDE/workspace_1.16.0/Common/Src/bsp_rf.c ExtSrc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../../Common/Inc -I"C:/Users/Juan/STM32CubeIDE/workspace_1.16.0/SSE-Disc/Core/app" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ExtSrc/nrf24.o: C:/Users/Juan/STM32CubeIDE/workspace_1.16.0/Common/Src/nrf24.c ExtSrc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../../Common/Inc -I"C:/Users/Juan/STM32CubeIDE/workspace_1.16.0/SSE-Disc/Core/app" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ExtSrc

clean-ExtSrc:
	-$(RM) ./ExtSrc/Util.cyclo ./ExtSrc/Util.d ./ExtSrc/Util.o ./ExtSrc/Util.su ./ExtSrc/bsp_rf.cyclo ./ExtSrc/bsp_rf.d ./ExtSrc/bsp_rf.o ./ExtSrc/bsp_rf.su ./ExtSrc/nrf24.cyclo ./ExtSrc/nrf24.d ./ExtSrc/nrf24.o ./ExtSrc/nrf24.su

.PHONY: clean-ExtSrc

