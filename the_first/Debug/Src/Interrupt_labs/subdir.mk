################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Interrupt_labs/secondlab_3_T.c 

OBJS += \
./Src/Interrupt_labs/secondlab_3_T.o 

C_DEPS += \
./Src/Interrupt_labs/secondlab_3_T.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Interrupt_labs/%.o Src/Interrupt_labs/%.su Src/Interrupt_labs/%.cyclo: ../Src/Interrupt_labs/%.c Src/Interrupt_labs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G4 -DSTM32G474VETx -c -I../Inc -I"D:/STM32_LABS/the_first/Inc/CMSIS" -I"D:/STM32_LABS/the_first/Src/GPIO_labs" -I"D:/STM32_LABS/the_first/Src/Interrupt_labs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Interrupt_labs

clean-Src-2f-Interrupt_labs:
	-$(RM) ./Src/Interrupt_labs/secondlab_3_T.cyclo ./Src/Interrupt_labs/secondlab_3_T.d ./Src/Interrupt_labs/secondlab_3_T.o ./Src/Interrupt_labs/secondlab_3_T.su

.PHONY: clean-Src-2f-Interrupt_labs

