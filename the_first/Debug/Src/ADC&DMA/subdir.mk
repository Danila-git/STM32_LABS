################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ADC&DMA/fourthlaba_2.c 

OBJS += \
./Src/ADC&DMA/fourthlaba_2.o 

C_DEPS += \
./Src/ADC&DMA/fourthlaba_2.d 


# Each subdirectory must supply rules for building sources it contributes
Src/ADC&DMA/%.o Src/ADC&DMA/%.su Src/ADC&DMA/%.cyclo: ../Src/ADC&DMA/%.c Src/ADC&DMA/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G4 -DSTM32G474VETx -c -I../Inc -I"D:/STM32_LABS/the_first/Inc/CMSIS" -I"D:/STM32_LABS/the_first/Src/GPIO_labs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-ADC-26-DMA

clean-Src-2f-ADC-26-DMA:
	-$(RM) ./Src/ADC&DMA/fourthlaba_2.cyclo ./Src/ADC&DMA/fourthlaba_2.d ./Src/ADC&DMA/fourthlaba_2.o ./Src/ADC&DMA/fourthlaba_2.su

.PHONY: clean-Src-2f-ADC-26-DMA

