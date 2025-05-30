#include "stm32g474xx.h"

uint32_t frec_change = 1599;
void Timer_Delay_ms(uint32_t milliseconds);

int main(void) {
	//частота микроконтроллера 16Mгц
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;

	//настройка прерывания на каждые 10 милисекунд
	Timer_Delay_ms(10);
	NVIC_EnableIRQ(TIM2_IRQn);

	GPIOD->MODER &= ~GPIO_MODER_MODE6_Msk;
	GPIOD->MODER |= 1 << GPIO_MODER_MODE6_Pos;

	while (1) {

	}
}

void TIM2_IRQHandler(void) {
	GPIOD->ODR ^= GPIO_ODR_OD6;
	TIM2->SR &= ~ TIM_SR_UIF;
}

//значение параметра функции = времени задержки в миллисекундах
void Timer_Delay_ms(uint32_t milliseconds) {
	if (milliseconds < 2) {
		milliseconds = 2;
	}
	if (milliseconds > 4000) {
		milliseconds = 4000;
	}
	TIM2->PSC = frec_change;
	TIM2->ARR = milliseconds - 1;

	TIM2->DIER = TIM_DIER_UIE;

	TIM2->SR &= ~TIM_SR_UIF;

	TIM2->CR1 |= TIM_CR1_CEN;
	while (!(TIM2->SR & TIM_SR_UIF))
		;

}
