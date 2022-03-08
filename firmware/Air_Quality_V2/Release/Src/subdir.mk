################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/bme680.c \
../Src/bme680_air_quality.c \
../Src/bsec_bme680_interface_app.c \
../Src/bsec_integration.c \
../Src/bsec_serialized_configurations_iaq.c \
../Src/debugPrint.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/main.c \
../Src/spi.c \
../Src/stm32l0xx_hal_msp.c \
../Src/stm32l0xx_it.c \
../Src/syscalls.c \
../Src/system_stm32l0xx.c \
../Src/usart.c 

OBJS += \
./Src/bme680.o \
./Src/bme680_air_quality.o \
./Src/bsec_bme680_interface_app.o \
./Src/bsec_integration.o \
./Src/bsec_serialized_configurations_iaq.o \
./Src/debugPrint.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
./Src/spi.o \
./Src/stm32l0xx_hal_msp.o \
./Src/stm32l0xx_it.o \
./Src/syscalls.o \
./Src/system_stm32l0xx.o \
./Src/usart.o 

C_DEPS += \
./Src/bme680.d \
./Src/bme680_air_quality.d \
./Src/bsec_bme680_interface_app.d \
./Src/bsec_integration.d \
./Src/bsec_serialized_configurations_iaq.d \
./Src/debugPrint.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/main.d \
./Src/spi.d \
./Src/stm32l0xx_hal_msp.d \
./Src/stm32l0xx_it.d \
./Src/syscalls.d \
./Src/system_stm32l0xx.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L072xx -I"C:/Users/Sarah/workspace/BME680_L072RZ_192KB/Inc" -I"C:/Users/Sarah/workspace/BME680_L072RZ_192KB/Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/Sarah/workspace/BME680_L072RZ_192KB/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Sarah/workspace/BME680_L072RZ_192KB/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/Sarah/workspace/BME680_L072RZ_192KB/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


