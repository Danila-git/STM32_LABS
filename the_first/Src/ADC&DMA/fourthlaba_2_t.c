#include "stm32g474xx.h"

uint16_t data;
uint16_t frequency_change;
uint32_t current_led = 0;
void dummy_delay();
void value_selection();

int main() {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	RCC->CCIPR |= (2U) << RCC_CCIPR_ADC12SEL_Pos;
	RCC->AHB2ENR |= RCC_AHB2ENR_ADC12EN;
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

//настройка светодиодов
	GPIOE->MODER &= ~(GPIO_MODER_MODE4_Msk | GPIO_MODER_MODE5_Msk
			| GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE7_Msk);
	GPIOE->MODER |= 1 << GPIO_MODER_MODE4_Pos | 1 << GPIO_MODER_MODE5_Pos
			| 1 << GPIO_MODER_MODE6_Pos | 1 << GPIO_MODER_MODE7_Pos;

	//настройка преобразователя
	ADC2->CR &= ~(ADC_CR_DEEPPWD);
	ADC2->CR |= ADC_CR_ADVREGEN;
	dummy_delay(10000);

	ADC2->CR |= ADC_CR_ADCAL;
	while (ADC2->CR & ADC_CR_ADCAL) {
	}

	ADC2->CR |= ADC_CR_ADEN;
	ADC2->ISR |= ADC_ISR_ADRDY;

	ADC2->SMPR1 |= 2 << ADC_SMPR1_SMP6_Pos;
	ADC2->SQR1 |= 0 << ADC_SQR1_L_Pos | 6 << ADC_SQR1_SQ1_Pos;

	ADC2->CFGR |= ADC_CFGR_CONT;
	ADC2->CR |= ADC_CR_ADSTART;

	//настройка таймера и его прерывания
	TIM2->PSC = 15999;
	TIM2->ARR = 1999;
	TIM2->DIER |= TIM_DIER_UIE;
	TIM2->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM2_IRQn);
	while (1) {

	}

}
void dummy_delay(uint32_t duration) {
	for (uint32_t i = 0; i < duration; i += 1)
		;
}

void TIM2_IRQHandler(void) {
	ADC2->ISR |= ADC_ISR_EOC;
	data = ADC2->DR;

	//формула для преобразования промежутка [0;4095] в промежуток [99;1999]
	frequency_change = 99 + ((uint32_t) data * (1999 - 99)) / 4095;
	TIM2->ARR = (uint32_t) frequency_change;
	GPIOE->BSRR = GPIO_BSRR_BR4 | GPIO_BSRR_BR5 | GPIO_BSRR_BR6 | GPIO_BSRR_BR7;
	switch (current_led) {
	case 0:
		GPIOE->BSRR = GPIO_BSRR_BS7;
		break;
	case 1:
		GPIOE->BSRR = GPIO_BSRR_BS6;
		break;
	case 2:
		GPIOE->BSRR = GPIO_BSRR_BS5;
		break;
	case 3:
		GPIOE->BSRR = GPIO_BSRR_BS4;
		break;
	}
	current_led++;
	if (current_led > 3) {
		current_led = 0;
	}
	TIM2->SR &= ~ TIM_SR_UIF;
}

