################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32L0xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: BME680_L072RZ_192KB.elf

# Tool invocations
BME680_L072RZ_192KB.elf: $(OBJS) $(USER_OBJS) ../STM32L072KZTx_FLASH.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -L"C:\Users\Sarah\workspace\BME680_L072RZ_192KB\Libraries" -specs=nosys.specs -specs=nano.specs -u _printf_float -T"../STM32L072KZTx_FLASH.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "BME680_L072RZ_192KB.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating hex and Printing size information:'
	arm-none-eabi-objcopy -O ihex "BME680_L072RZ_192KB.elf" "BME680_L072RZ_192KB.hex"
	arm-none-eabi-size "BME680_L072RZ_192KB.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
