################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/GPIO_labs/firstlab_2.c 

OBJS += \
./Src/GPIO_labs/firstlab_2.o 

C_DEPS += \
./Src/GPIO_labs/firstlab_2.d 


# Each subdirectory must supply rules for building sources it contributes
Src/GPIO_labs/%.o Src/GPIO_labs/%.su Src/GPIO_labs/%.cyclo: ../Src/GPIO_labs/%.c Src/GPIO_labs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G4 -DSTM32G474VETx -c -I../Inc -I"D:/Application/CubeIDE/STM32CubeIDE_1.18.1/the_first/Inc/CMSIS" -I"D:/Application/CubeIDE/STM32CubeIDE_1.18.1/the_first/Src/GPIO_labs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-GPIO_labs

clean-Src-2f-GPIO_labs:
	-$(RM) ./Src/GPIO_labs/firstlab_2.cyclo ./Src/GPIO_labs/firstlab_2.d ./Src/GPIO_labs/firstlab_2.o ./Src/GPIO_labs/firstlab_2.su

.PHONY: clean-Src-2f-GPIO_labs

