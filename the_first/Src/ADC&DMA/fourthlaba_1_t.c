#include "stm32g474xx.h"

uint16_t data;
uint32_t led_amount_on;
void dummy_delay();
void value_selection();

int main() {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	RCC->CCIPR |= (2U) << RCC_CCIPR_ADC12SEL_Pos;
	RCC->AHB2ENR |= RCC_AHB2ENR_ADC12EN;

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
	while (ADC2->CR & ADC_CR_ADCAL) {}

	ADC2->ISR |= ADC_ISR_ADRDY;
	ADC2->CR |= ADC_CR_ADEN;
	while (!(ADC2->ISR & ADC_ISR_ADRDY)) {}

	ADC2->SMPR1 |= 2 << ADC_SMPR1_SMP6_Pos;
	ADC2->SQR1 |= 0 << ADC_SQR1_L_Pos | 6 << ADC_SQR1_SQ1_Pos;

	ADC2->CR |= ADC_CR_ADSTART;

	while (1) {
		value_selection();
	}
}
void dummy_delay(uint32_t duration) {
	for (uint32_t i = 0; i < duration; i += 1)
		;
}

void value_selection() {
	ADC2->CR |= ADC_CR_ADSTART;
	 while (!(ADC2->ISR & ADC_ISR_EOC));
	if (ADC2->ISR & ADC_ISR_EOC) {
		data = ADC2->DR;
		led_amount_on = data*4/4094;
		GPIOE->BSRR = GPIO_BSRR_BR7 | GPIO_BSRR_BR6 | GPIO_BSRR_BR5 | GPIO_BSRR_BR4;
		GPIOE->BSRR = (1 << led_amount_on + 4) - 1;

	}
}
