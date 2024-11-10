################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/bsp_encoder.c \
../Core/Src/bsp_hcsr501.c \
../Core/Src/bsp_lcd.c \
../Core/Src/bsp_rc522.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/rc522.c \
../Core/Src/spi.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tim.c 

C_DEPS += \
./Core/Src/bsp_encoder.d \
./Core/Src/bsp_hcsr501.d \
./Core/Src/bsp_lcd.d \
./Core/Src/bsp_rc522.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/rc522.d \
./Core/Src/spi.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tim.d 

OBJS += \
./Core/Src/bsp_encoder.o \
./Core/Src/bsp_hcsr501.o \
./Core/Src/bsp_lcd.o \
./Core/Src/bsp_rc522.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/rc522.o \
./Core/Src/spi.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tim.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu18 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../../Common/Inc -I"C:/Users/Isaac/Documents/Downloads/workspace_1.16.0/workspace_1.16.0/SSE-BluePill/Core/app" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/bsp_encoder.cyclo ./Core/Src/bsp_encoder.d ./Core/Src/bsp_encoder.o ./Core/Src/bsp_encoder.su ./Core/Src/bsp_hcsr501.cyclo ./Core/Src/bsp_hcsr501.d ./Core/Src/bsp_hcsr501.o ./Core/Src/bsp_hcsr501.su ./Core/Src/bsp_lcd.cyclo ./Core/Src/bsp_lcd.d ./Core/Src/bsp_lcd.o ./Core/Src/bsp_lcd.su ./Core/Src/bsp_rc522.cyclo ./Core/Src/bsp_rc522.d ./Core/Src/bsp_rc522.o ./Core/Src/bsp_rc522.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/rc522.cyclo ./Core/Src/rc522.d ./Core/Src/rc522.o ./Core/Src/rc522.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su

.PHONY: clean-Core-2f-Src

