#include "stm32g474xx.h"

uint16_t adc_data[2] ={0};
uint16_t data;
void dummy_delay();
void setup_adc_dma();
void shim_setup();

int main()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN | RCC_AHB2ENR_GPIOCEN;
	// ADC and clock
	RCC->AHB2ENR |= RCC_AHB2ENR_ADC12EN;
	RCC->CCIPR |= (2U) << RCC_CCIPR_ADC12SEL_Pos;
	// Timers
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;

	// GPIOE4, E5 как альтернативная функция для TIM3_CH3 и CH4
	GPIOE->MODER &= ~(GPIO_MODER_MODE4_Msk | GPIO_MODER_MODE5_Msk);
	GPIOE->MODER |= 2 << GPIO_MODER_MODE4_Pos | 2 << GPIO_MODER_MODE5_Pos;
	GPIOE->AFR[0] |= (2 << GPIO_AFRL_AFSEL4_Pos) | (2 << GPIO_AFRL_AFSEL5_Pos); // AF2 for TIM3

	dummy_delay(10000);

	// АЦП
	ADC2->CR &= ~ADC_CR_DEEPPWD;
	ADC2->CR |= ADC_CR_ADVREGEN;
	dummy_delay(10000);

	ADC2->CR |= ADC_CR_ADCAL;
	while (ADC2->CR & ADC_CR_ADCAL);

	ADC2->CR |= ADC_CR_ADEN;
	while (!(ADC2->ISR & ADC_ISR_ADRDY));

	// Настройка DMA
	setup_adc_dma(adc_data);

	// Настройка ADC на 2 канала
	ADC2->SMPR1 |= 2 << ADC_SMPR1_SMP6_Pos | 2 << ADC_SMPR1_SMP7_Pos;
	ADC2->SQR1 |= 1 << ADC_SQR1_L_Pos | 6 << ADC_SQR1_SQ1_Pos | 7 << ADC_SQR1_SQ2_Pos;

	// Включить DMA в ADC
	ADC2->CFGR |= ADC_CFGR_CONT | ADC_CFGR_DMAEN | ADC_CFGR_DMACFG;
	ADC2->CR |= ADC_CR_ADSTART;

	// ШИМ настройка TIM3 CH3 и CH4
	TIM3->PSC = 0;
	TIM3->ARR = 4095;
	TIM3->CCMR2 |= TIM_CCMR2_OC3PE | (6 << TIM_CCMR2_OC3M_Pos) | TIM_CCMR2_OC4PE | (6 << TIM_CCMR2_OC4M_Pos);
	TIM3->CCER |= TIM_CCER_CC3E | TIM_CCER_CC4E;
	TIM3->CCR3 = 0;
	TIM3->CCR4 = 0;
	TIM3->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;

	while (1) {
	    shim_setup();
	}
}
void dummy_delay(uint32_t duration) {
	for (uint32_t i = 0; i < duration; i+=1);
}

void shim_setup()
{
			TIM3->CCR3 = adc_data[0];
			TIM3->CCR4 = adc_data[1];
}

void setup_adc_dma( uint16_t *array_to_write_to )
{
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN | RCC_AHB1ENR_DMAMUX1EN;

    DMA1_Channel1->CPAR = (uint32_t)&(ADC2->DR);

    DMA1_Channel1->CMAR = (uint32_t)array_to_write_to;

    DMA1_Channel1->CNDTR = 2;

    DMA1_Channel1->CCR |= 1 << DMA_CCR_MSIZE_Pos | 1 << DMA_CCR_PSIZE_Pos
                       | DMA_CCR_MINC | DMA_CCR_CIRC;

    DMAMUX1_Channel0->CCR |= (36 << DMAMUX_CxCR_DMAREQ_ID_Pos);

    DMA1_Channel1->CCR |= DMA_CCR_EN;
}
