#include "stm32g474xx.h"

uint32_t counter = 0;
void Timer_Delay_ms(uint32_t milliseconds);

int main(void) {
	//частота микроконтроллера 16Mгц
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;

	TIM2->PSC = 1599;
	TIM2->ARR = 9;
	TIM2->DIER = TIM_DIER_UIE;
	TIM2->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM2_IRQn);

	GPIOD->MODER &= ~GPIO_MODER_MODE6_Msk;
	GPIOD->MODER |= 1 << GPIO_MODER_MODE6_Pos;

	while (1) {
		GPIOD->ODR ^= GPIO_ODR_OD6;
		//задержка на 1000 миллисекунд
		Timer_Delay_ms(1000);
	}
}

void TIM2_IRQHandler() {
	TIM2->SR &= ~ TIM_SR_UIF;
	counter +=1;
}

//значение параметра функции = времени задержки в миллисекундах
void Timer_Delay_ms(uint32_t milliseconds) {
	if (milliseconds < 2) {
		milliseconds = 2;
	}
	if (milliseconds > 4000) {
		milliseconds = 4000;
	}
	while(milliseconds > counter)
	{}
	counter = 0;
}
