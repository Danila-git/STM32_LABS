#include "stm32g474xx.h"

uint32_t impulse_counter = 0;

int main(void) {
	//частота микроконтроллера 16Mгц
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN | RCC_APB1ENR1_TIM3EN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;

	GPIOE->MODER &= ~GPIO_MODER_MODE5_Msk;
	GPIOE->MODER |= 1 << GPIO_MODER_MODE5_Pos;

	//настройка прерывания каждую секунду
	TIM2->PSC = 15999;
	TIM2->ARR = 999;

	TIM2->DIER = TIM_DIER_UIE;

	TIM2->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM2_IRQn);

	while (1) {

	}
}

void TIM2_IRQHandler(void) {
	impulse_counter += 1;
	//импульс с коэффициентов 0.5 и частотой 0.5Гц=2 секунды
	if (impulse_counter <= 40) {
		GPIOE->ODR ^= GPIO_ODR_OD5;
	} else {
		TIM2->CR1 &= ~TIM_CR1_CEN;
	}
	TIM2->SR &= ~ TIM_SR_UIF;
}
