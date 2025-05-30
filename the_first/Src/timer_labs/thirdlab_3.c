#include "stm32g474xx.h"

void setup_clock();

uint32_t percent = 20;

int main (void)
{
	setup_clock();

	    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN | RCC_APB1ENR1_TIM2EN;

	    GPIOE->MODER &= ~(GPIO_MODER_MODE5_Msk);
	    GPIOE->MODER |=  2 << GPIO_MODER_MODE5_Pos;

	    //настраиваю прерывания каждые 2 секунды
	    TIM2->PSC = 7999;
	    TIM2->ARR = 1999;
	    TIM2->DIER |= TIM_DIER_UIE;

	    GPIOE->AFR[0] |=  2 << GPIO_AFRL_AFSEL5_Pos;

	    TIM3->PSC = 0;
	    TIM3->ARR = 799; // Частота 10кГц


	    // Настроить таймер в режим ШИМ
	    TIM3->CCMR2 |=  TIM_CCMR2_OC4PE | 6 << TIM_CCMR2_OC4M_Pos;
	    TIM3->CCMR2 |=  TIM_CCMR2_OC3PE | 6 << TIM_CCMR2_OC3M_Pos;
	    TIM3->CCER |=  TIM_CCER_CC4E;
	    TIM3->CR1 |= TIM_CR1_ARPE;
	    TIM3->CCR4 = (800 * percent) / 100;

	    TIM3->CR1 |= TIM_CR1_CEN;
	    TIM2->CR1 |= TIM_CR1_CEN;
	    NVIC_EnableIRQ (TIM2_IRQn);

    while ( 1 )
    {

    }
}

void TIM2_IRQHandler (void)
{
	if (percent < 80) {
		percent += 20;
	} else {
		percent = 20;
	}
	TIM3->CCR4 = (800 * percent) / 100;
    TIM2->SR &= ~ TIM_SR_UIF;
}



//устанавливаю частоту процессора 8МГц
void setup_clock()
{

  RCC->CR |= RCC_CR_HSEON;
  while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY) {}

  RCC->CFGR |= RCC_CFGR_SW_Msk;
  RCC->CFGR &= ~(RCC_CFGR_SW_Msk ^ RCC_CFGR_SW_HSE);

  while ((RCC->CFGR & RCC_CFGR_SWS_HSE) != RCC_CFGR_SWS_HSE){}
}

