#include "stm32g474xx.h"

int main(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN | RCC_AHB2ENR_GPIOEEN | RCC_AHB2ENR_GPIOBEN;

    GPIOD->MODER &= ~(GPIO_MODER_MODE9_Msk);
    GPIOD->MODER |= 1 << GPIO_MODER_MODE9_Pos;

    GPIOE->MODER &= ~(GPIO_MODER_MODE7_Msk);
    GPIOE->MODER |= 1 << GPIO_MODER_MODE7_Pos;

    GPIOB->MODER &= ~(GPIO_MODER_MODE15_Msk | GPIO_MODER_MODE13_Msk);
    GPIOB->MODER |= 0 << GPIO_MODER_MODE15_Pos | 0 << GPIO_MODER_MODE13_Pos;

    while(1)
    {
    	if((GPIOB->IDR & GPIO_IDR_ID15) == 0)
    	{
    		GPIOE->BSRR = GPIO_BSRR_BS7;
    	}else
    	{
    		GPIOE->BSRR = GPIO_BSRR_BR7;
    	}
        if((GPIOB->IDR & GPIO_IDR_ID13) == 0)
    	{
    		GPIOD->BSRR = GPIO_BSRR_BS9;
    	}else
    	{
    		GPIOD->BSRR = GPIO_BSRR_BR9;
    	}

    }
}
