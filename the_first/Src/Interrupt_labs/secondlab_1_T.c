#include "stm32g474xx.h"

uint32_t turn_on = 0;
uint32_t turn_off = 0;

int main(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN | RCC_AHB2ENR_GPIOBEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI12_PB;

	    EXTI->IMR1 |= EXTI_IMR1_IM12;
	    EXTI->FTSR1 |= EXTI_FTSR1_FT12;
	    EXTI->RTSR1 |= EXTI_RTSR1_RT12;
	    NVIC_EnableIRQ( EXTI15_10_IRQn );

	GPIOD->MODER &= ~(GPIO_MODER_MODE9_Msk | GPIO_MODER_MODE10_Msk
			| GPIO_MODER_MODE11_Msk | GPIO_MODER_MODE12_Msk);
	GPIOD->MODER |= 1 << GPIO_MODER_MODE9_Pos | 1 << GPIO_MODER_MODE10_Pos
			| 1 << GPIO_MODER_MODE11_Pos | 1 << GPIO_MODER_MODE12_Pos;

	GPIOB->MODER &= ~(GPIO_MODER_MODE12_Msk);

	while (1) {
		if((GPIOB->IDR & GPIO_IDR_ID12) == 0)
		{
			turn_off += 1;
		}
	}
}

void EXTI15_10_IRQHandler()
{
	if((GPIOB->IDR & GPIO_IDR_ID12) == 0 && turn_on < 15)
	{
			    	  turn_on += 1;
			    	  GPIOD->BSRR = GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12;
		GPIOD->BSRR = turn_on << GPIO_BSRR_BS9_Pos;
		turn_off = 0;
	}else if(turn_off >= 1700000)
	{
		GPIOD->BSRR = GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12;
		turn_on = 0;
	}
	EXTI->PR1 |= EXTI_PR1_PIF12;
}









