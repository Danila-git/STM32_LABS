#include "stm32g474xx.h"

uint32_t button_is_pressed = 0;
uint32_t button_num = 3;

int main(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOEEN;

    GPIOE->MODER &= ~(GPIO_MODER_MODE3_Msk | GPIO_MODER_MODE4_Msk | GPIO_MODER_MODE5_Msk | GPIO_MODER_MODE6_Msk );
    GPIOE->MODER |= 1 << GPIO_MODER_MODE3_Pos | 1 << GPIO_MODER_MODE4_Pos | 1 << GPIO_MODER_MODE5_Pos | 1 << GPIO_MODER_MODE6_Pos;

    GPIOB->MODER &= ~(GPIO_MODER_MODE12_Msk | GPIO_MODER_MODE15_Msk);

    while(1)
    {

    	if((GPIOB->IDR & GPIO_IDR_ID12) == 0 && button_num < 7 && button_is_pressed == 0)
    	{
    		button_is_pressed = 1;
    		GPIOE->BSRR = (1 << button_num);
            button_num +=1;
    	}
    	else if((GPIOB->IDR & GPIO_IDR_ID15) == 0)
    	{
            GPIOE->BSRR = GPIO_BSRR_BR3 | GPIO_BSRR_BR4 | GPIO_BSRR_BR5 | GPIO_BSRR_BR6;
    		button_num = 3;
    	} else if (GPIOB->IDR & GPIO_IDR_ID12)
        {
            button_is_pressed = 0;
        }
    }
}
