#include "stm32g474xx.h"

uint32_t frec_change = 15999;
uint32_t direction = 0;
int main(void) {
	//частота микроконтроллера 16Mгц
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN | RCC_APB1ENR1_TIM3EN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;

	GPIOE->MODER &= ~GPIO_MODER_MODE5_Msk;
	GPIOE->MODER |= 1 << GPIO_MODER_MODE5_Pos;

	//настройка прерывания
	TIM2->PSC = frec_change;
	TIM2->ARR = 1000;

	TIM2->DIER = TIM_DIER_UIE;

	TIM2->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM2_IRQn);

	while (1) {

	}
}

void TIM2_IRQHandler(void) {
	//изменение частоты от 1 Гц до 5 Гц и обратно
	if(frec_change > 3199 && direction == 0)
	{
		frec_change -= 1600;
	}else{
		direction = 1;
	}
    if(frec_change < 15999 && direction == 1)
	{
		frec_change += 1600;
	}else
	{
		direction = 0;
	}
		GPIOE->ODR ^= GPIO_ODR_OD5;
		TIM2->PSC = frec_change;
	TIM2->SR &= ~ TIM_SR_UIF;
}
