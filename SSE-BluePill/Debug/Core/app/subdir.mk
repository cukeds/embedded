################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/app/app.c \
../Core/app/bsp.c 

C_DEPS += \
./Core/app/app.d \
./Core/app/bsp.d 

OBJS += \
./Core/app/app.o \
./Core/app/bsp.o 


# Each subdirectory must supply rules for building sources it contributes
Core/app/%.o Core/app/%.su Core/app/%.cyclo: ../Core/app/%.c Core/app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu18 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../../Common/Inc -I"C:/Users/Isaac/Documents/Downloads/workspace_1.16.0/workspace_1.16.0/SSE-BluePill/Core/app" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-app

clean-Core-2f-app:
	-$(RM) ./Core/app/app.cyclo ./Core/app/app.d ./Core/app/app.o ./Core/app/app.su ./Core/app/bsp.cyclo ./Core/app/bsp.d ./Core/app/bsp.o ./Core/app/bsp.su

.PHONY: clean-Core-2f-app

