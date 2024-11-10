################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/ECUAL/I2C_LCD/I2C_LCD.c \
../Core/ECUAL/I2C_LCD/I2C_LCD_cfg.c 

C_DEPS += \
./Core/ECUAL/I2C_LCD/I2C_LCD.d \
./Core/ECUAL/I2C_LCD/I2C_LCD_cfg.d 

OBJS += \
./Core/ECUAL/I2C_LCD/I2C_LCD.o \
./Core/ECUAL/I2C_LCD/I2C_LCD_cfg.o 


# Each subdirectory must supply rules for building sources it contributes
Core/ECUAL/I2C_LCD/%.o Core/ECUAL/I2C_LCD/%.su Core/ECUAL/I2C_LCD/%.cyclo: ../Core/ECUAL/I2C_LCD/%.c Core/ECUAL/I2C_LCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu18 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../../Common/Inc -I"C:/Users/Isaac/Documents/Downloads/workspace_1.16.0/workspace_1.16.0/SSE-BluePill/Core/app" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-ECUAL-2f-I2C_LCD

clean-Core-2f-ECUAL-2f-I2C_LCD:
	-$(RM) ./Core/ECUAL/I2C_LCD/I2C_LCD.cyclo ./Core/ECUAL/I2C_LCD/I2C_LCD.d ./Core/ECUAL/I2C_LCD/I2C_LCD.o ./Core/ECUAL/I2C_LCD/I2C_LCD.su ./Core/ECUAL/I2C_LCD/I2C_LCD_cfg.cyclo ./Core/ECUAL/I2C_LCD/I2C_LCD_cfg.d ./Core/ECUAL/I2C_LCD/I2C_LCD_cfg.o ./Core/ECUAL/I2C_LCD/I2C_LCD_cfg.su

.PHONY: clean-Core-2f-ECUAL-2f-I2C_LCD

