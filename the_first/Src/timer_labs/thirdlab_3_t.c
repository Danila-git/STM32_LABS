#include "stm32g474xx.h"

uint32_t percent = 10;
uint32_t direction = 1;

int main (void)
{

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN | RCC_APB1ENR1_TIM2EN;

	GPIOE->MODER &= ~(GPIO_MODER_MODE5_Msk);
	GPIOE->MODER |= 2 << GPIO_MODER_MODE5_Pos;

	//делаю задержку 0,5 секунды
	TIM2->PSC = 15999;
	TIM2->ARR = 499;
	TIM2->DIER |= TIM_DIER_UIE;

	GPIOE->AFR[0] |= 2 << GPIO_AFRL_AFSEL5_Pos;

	TIM3->PSC = 0;
	TIM3->ARR = 799; // Частота 10кГц


	    // Настроить таймер в режим ШИМ
	TIM3->CCMR2 |= TIM_CCMR2_OC4PE | 6 << TIM_CCMR2_OC4M_Pos;
	TIM3->CCMR2 |= TIM_CCMR2_OC3PE | 6 << TIM_CCMR2_OC3M_Pos;
	TIM3->CCER |= TIM_CCER_CC4E;
	TIM3->CR1 |= TIM_CR1_ARPE;
	TIM3->CCR4 = (799 * percent) / 100;

	TIM3->CR1 |= TIM_CR1_CEN;
	TIM2->CR1 |= TIM_CR1_CEN;


	    NVIC_EnableIRQ (TIM2_IRQn);
    while ( 1 )
    {

    }
}


void TIM2_IRQHandler (void)
{
	if (percent < 100 && direction) {
		percent += 10;
	} else {
		direction = 0;
	}
	if (percent > 10 && direction == 0) {
		percent -= 10;
	} else {
		direction = 1;
	}
	TIM3->CCR4 = (800 * percent) / 100;
    TIM2->SR &= ~ TIM_SR_UIF;
}

