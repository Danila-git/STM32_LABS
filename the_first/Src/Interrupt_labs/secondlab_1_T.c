#include "stm32g474xx.h"

uint32_t turn_on = 0;
uint32_t frec_change = 15999;

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
	//частота микроконтроллера 16Mгц
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

	//настройка прерывания на каждые 2 секунды
 	TIM2->PSC = frec_change;
	TIM2->ARR = 1999;
	TIM2->DIER = TIM_DIER_UIE;

	NVIC_EnableIRQ(TIM2_IRQn);
	while (1) {

	}
}

void EXTI15_10_IRQHandler()
{
	if((GPIOB->IDR & GPIO_IDR_ID12) == 0 )
	{
		 TIM2->CNT = 0;
			    	  TIM2->CR1 |= TIM_CR1_CEN;
			    	  turn_on += 1;
			    	  GPIOD->BSRR = GPIO_BSRR_BR9 | GPIO_BSRR_BR10
			    	  								| GPIO_BSRR_BR11 | GPIO_BSRR_BR12;
		GPIOD->BSRR = turn_on << 9;
	}else
	{
		TIM2->CR1 &= ~TIM_CR1_CEN;
	}
	EXTI->PR1 |= EXTI_PR1_PIF12;
}
void TIM2_IRQHandler(void)
  {
	  GPIOD->BSRR = GPIO_BSRR_BR9 | GPIO_BSRR_BR10
	  								| GPIO_BSRR_BR11 | GPIO_BSRR_BR12;
		turn_on = 0;
  	TIM2->CR1 &= ~TIM_CR1_CEN;
  	TIM2->SR &= ~ TIM_SR_UIF;
  }








