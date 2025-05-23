#include "stm32g474xx.h"

void change(uint32_t amount);

int main(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN | RCC_AHB2ENR_GPIOEEN;

    GPIOD->MODER &= ~(GPIO_MODER_MODE14_Msk);
    GPIOD->MODER |= 1 << GPIO_MODER_MODE14_Pos;

    GPIOE->MODER &= ~(GPIO_MODER_MODE0_Msk);
    GPIOE->MODER |= 1 << GPIO_MODER_MODE0_Pos;


    while(1)
    {
        GPIOD->ODR ^= GPIO_ODR_OD14;
        change(500000);
        GPIOE->ODR ^= GPIO_ODR_OD0;
    }
}

void change(uint32_t amount)
    {
    	for(uint32_t i = 0; i < amount; i+=1);
    }
