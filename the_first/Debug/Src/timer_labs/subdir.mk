################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/timer_labs/thirdlab_B.c 

OBJS += \
./Src/timer_labs/thirdlab_B.o 

C_DEPS += \
./Src/timer_labs/thirdlab_B.d 


# Each subdirectory must supply rules for building sources it contributes
Src/timer_labs/%.o Src/timer_labs/%.su Src/timer_labs/%.cyclo: ../Src/timer_labs/%.c Src/timer_labs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G4 -DSTM32G474VETx -c -I../Inc -I"D:/STM32_LABS/the_first/Inc/CMSIS" -I"D:/STM32_LABS/the_first/Src/GPIO_labs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-timer_labs

clean-Src-2f-timer_labs:
	-$(RM) ./Src/timer_labs/thirdlab_B.cyclo ./Src/timer_labs/thirdlab_B.d ./Src/timer_labs/thirdlab_B.o ./Src/timer_labs/thirdlab_B.su

.PHONY: clean-Src-2f-timer_labs

