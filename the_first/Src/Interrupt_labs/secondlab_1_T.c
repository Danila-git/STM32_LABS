#include "stm32g474xx.h"

uint32_t turn_on = 0;
uint32_t pressed1 = 1;
uint32_t time = 300000;
uint32_t click = 0;

int main(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN | RCC_AHB2ENR_GPIOBEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI12_PB;

	    EXTI->IMR1 |= EXTI_IMR1_IM12;
	    EXTI->FTSR1 |= EXTI_FTSR1_FT12;
	    NVIC_EnableIRQ( EXTI15_10_IRQn );

	GPIOD->MODER &= ~(GPIO_MODER_MODE9_Msk | GPIO_MODER_MODE10_Msk
			| GPIO_MODER_MODE11_Msk | GPIO_MODER_MODE12_Msk);
	GPIOD->MODER |= 1 << GPIO_MODER_MODE9_Pos | 1 << GPIO_MODER_MODE10_Pos
			| 1 << GPIO_MODER_MODE11_Pos | 1 << GPIO_MODER_MODE12_Pos;

	GPIOB->MODER &= ~(GPIO_MODER_MODE12_Msk);

	while (1) {

	}
}

void EXTI15_10_IRQHandler()
{
	while((GPIOB->IDR & GPIO_IDR_ID12) == 0 )
	{
		click+=1;
	}
		if(GPIOB->IDR & GPIO_IDR_ID12 && click < time && click > 0)
			{
			GPIOD->ODR &= ~(GPIO_ODR_OD9 | GPIO_ODR_OD10
								| GPIO_ODR_OD11 | GPIO_ODR_OD12);
						turn_on +=0b1000000000;
						GPIOD->ODR |= turn_on;
						click = 0;
			}
			else if(GPIOB->IDR & GPIO_IDR_ID12 &&  click > time)
		{
			GPIOD->ODR &= 0b0;
			click = 0;
			turn_on = 0;
		}
}









