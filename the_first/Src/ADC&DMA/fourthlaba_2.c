#include "stm32g474xx.h"

uint16_t adc_data[2] ={0};
uint16_t data;
void dummy_delay();
void setup_adc_dma();

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

	ADC2->SMPR1 |= 2 << ADC_SMPR1_SMP6_Pos | 2 << ADC_SMPR1_SMP7_Pos;

	ADC2->SQR1 |= 1 << ADC_SQR1_L_Pos | 6 << ADC_SQR1_SQ1_Pos | 7 << ADC_SQR1_SQ2_Pos;

    setup_adc_dma(adc_data);
	ADC2->CR |= ADC_CR_ADSTART;


    ADC2->ISR |= ADC_ISR_EOS;
    while (!(ADC2->ISR & ADC_ISR_EOS)){}

    ADC2->CFGR |= ADC_CFGR_DMAEN | ADC_CFGR_DMACFG;

    while(1)
    {

    }
}

void setup_adc_dma( uint16_t *array_to_write_to )
{
    // Включить тактирование DMA
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN | RCC_AHB1ENR_DMAMUX1EN;


    // Настроить адрес откуда будет происходить чтение
    DMA1_Channel1->CPAR = (uint32_t)&(ADC2->DR);


    // Настроить адрес куда будет происходить записью надо напрямую преобразовать
    // адрес в число типа uin32_t, так как все адреса - 32 значения.
    DMA1_Channel1->CMAR = (uint32_t)array_to_write_to;


    // Настроить количество значений, которые мы хотим считать.
    DMA1_Channel1->CNDTR = 2;


    // Настроить канал DMA: размер данных 16 бит источник и приемник, циклический
    // режим, увеличивать указатель при записи.
    DMA1_Channel1->CCR |= 1 << DMA_CCR_MSIZE_Pos | 1 << DMA_CCR_PSIZE_Pos
                       | DMA_CCR_MINC | DMA_CCR_CIRC;

    // Настроить мультиплексор каналов DMA
    DMAMUX1_Channel1->CCR |= (36 << DMAMUX_CxCR_DMAREQ_ID_Pos);
    // Включить DMA
    DMA1_Channel1->CCR |= DMA_CCR_EN;
}


void dummy_delay(uint32_t duration) {
	for (uint32_t i = 0; i < duration; i+=1);
}

