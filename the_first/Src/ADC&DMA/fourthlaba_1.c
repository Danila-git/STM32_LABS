#include "stm32g474xx.h"

uint16_t data;
void dummy_delay();

int main()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	RCC->CCIPR |= (2U) << RCC_CCIPR_ADC12SEL_Pos;

	RCC->AHB2ENR |= RCC_AHB2ENR_ADC12EN;

	ADC2->CR &= ~(ADC_CR_DEEPPWD);
	ADC2->CR |= ADC_CR_ADVREGEN;
	 dummy_delay( 10000 );

	ADC2->CR |= ADC_CR_ADCAL;
	while(ADC2->CR & ADC_CR_ADCAL){}

	ADC2->ISR |= ADC_ISR_ADRDY;
	ADC2->CR |= ADC_CR_ADEN;
	while(!(ADC2->CR & ADC_ISR_ADRDY)){}

	ADC2->SMPR1 |= 2 << ADC_SMPR1_SMP6_Pos;
	ADC2->SQR1 |= 0 << ADC_SQR1_L_Pos | 6 << ADC_SQR1_SQ1_Pos;

	ADC2->CR |= ADC_CR_ADSTART;
    while ( !(ADC2->ISR & ADC_ISR_EOS) ){}

    ADC2->ISR |= ADC_ISR_EOS;

    data = ADC2->DR;

    while(1)
    {

    }
}
void dummy_delay(uint32_t duration) {
	for (uint32_t i = 0; i < duration; i+=1);
}

