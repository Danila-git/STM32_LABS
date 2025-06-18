#include "stm32g474xx.h"

uint16_t adc_data[2] = { 0 };
uint16_t data;
void dummy_delay();
void setup_adc_dma();

int main() {
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	RCC->CCIPR |= (2U) << RCC_CCIPR_ADC12SEL_Pos;
	RCC->AHB2ENR |= RCC_AHB2ENR_ADC12EN;

	//настройка прерывания таймера каждую секунду
	TIM2->PSC = 15999;
	TIM2->ARR = 999;
    TIM2->DIER = TIM_DIER_UIE;

	NVIC_EnableIRQ(TIM2_IRQn);

	ADC2->CR &= ~(ADC_CR_DEEPPWD);
	ADC2->CR |= ADC_CR_ADVREGEN;
	dummy_delay(10000);

	ADC2->CR |= ADC_CR_ADCAL;
	while (ADC2->CR & ADC_CR_ADCAL) {}

	ADC2->CR |= ADC_CR_ADEN;
	ADC2->ISR |= ADC_ISR_ADRDY;
	while (!(ADC2->ISR & ADC_ISR_ADRDY)) {}

	ADC2->SMPR1 |= 2 << ADC_SMPR1_SMP6_Pos | 2 << ADC_SMPR1_SMP7_Pos;

	ADC2->SQR1 |= 1 << ADC_SQR1_L_Pos | 6 << ADC_SQR1_SQ1_Pos
			| 7 << ADC_SQR1_SQ2_Pos;

	setup_adc_dma(adc_data);

	ADC2->CFGR |= ADC_CFGR_DMAEN | ADC_CFGR_DMACFG;

	TIM2->CR1 |= TIM_CR1_CEN;

	ADC2->CR |= ADC_CR_ADSTART;

	while (1) {

	}
}

void TIM2_IRQHandler(void) {
	ADC2->CR |= ADC_CR_ADSTART;
	ADC2->ISR |= ADC_ISR_EOC;
	if (ADC2->ISR & ADC_ISR_EOC) {
		setup_adc_dma(adc_data);
	}
	TIM2->SR &= ~ TIM_SR_UIF;
}

void setup_adc_dma(uint16_t *array_to_write_to) {
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN | RCC_AHB1ENR_DMAMUX1EN;

	DMA1_Channel1->CPAR = (uint32_t) &(ADC2->DR);

	DMA1_Channel1->CMAR = (uint32_t) array_to_write_to;

	DMA1_Channel1->CNDTR = 2;

	DMA1_Channel1->CCR |= 1 << DMA_CCR_MSIZE_Pos | 1 << DMA_CCR_PSIZE_Pos
			| DMA_CCR_MINC | DMA_CCR_CIRC;

	DMAMUX1_Channel0->CCR |= (36 << DMAMUX_CxCR_DMAREQ_ID_Pos);

	DMA1_Channel1->CCR |= DMA_CCR_EN;
}

void dummy_delay(uint32_t duration) {
	for (uint32_t i = 0; i < duration; i += 1);
}
