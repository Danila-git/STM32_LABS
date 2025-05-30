#include "stm32g474xx.h"

uint32_t impulse_counter = 0;

int main(void) {
	//частота микроконтроллера 16Mгц
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN | RCC_APB1ENR1_TIM3EN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;

	GPIOE->MODER &= ~GPIO_MODER_MODE5_Msk;
	GPIOE->MODER |= 2 << GPIO_MODER_MODE5_Pos;
	GPIOE->AFR[0] |= 2 << GPIO_AFRL_AFSEL5_Pos;

	//настройка частоты 0,5 Гц
	TIM2->PSC = 15999;
	TIM2->ARR = 1999;

	TIM2->DIER = TIM_DIER_UIE;

	//настройка тамера 3
	TIM3->PSC = 0;
	TIM3->ARR = 799;

	// Настроить таймер в режим ШИМ
	TIM3->CCMR2 |= TIM_CCMR2_OC4PE | 6 << TIM_CCMR2_OC4M_Pos;
	TIM3->CCER |= TIM_CCER_CC4E;
	TIM3->CR1 |= TIM_CR1_ARPE;
	TIM3->CCR4 = 400;

	TIM3->CR1 |= TIM_CR1_CEN;
	TIM2->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM2_IRQn);

	while (1) {

	}
}

void TIM2_IRQHandler(void) {
	impulse_counter += 1;
	if (impulse_counter > 20) {
		TIM2->CR1 &= ~TIM_CR1_CEN;
		TIM3->CR1 &= ~TIM_CR1_CEN;
	}
	TIM2->SR &= ~ TIM_SR_UIF;
}
