#include "stm32g474xx.h"

uint32_t arr2_value = 999;
uint32_t direction = 0;

int main(void)
{
	//частота микроконтроллера 16Mгц
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN | RCC_APB1ENR1_TIM3EN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;

	GPIOE->MODER &= ~GPIO_MODER_MODE6_Msk;
		    GPIOE->MODER |= 1 << GPIO_MODER_MODE6_Pos;

	GPIOE->MODER &= ~GPIO_MODER_MODE5_Msk;
	    GPIOE->MODER |= 2 << GPIO_MODER_MODE5_Pos;
	    GPIOE->AFR[0] |=  2 << GPIO_AFRL_AFSEL5_Pos;

	//настройка частоты 1 Гц
	TIM2->PSC = 15999;
	TIM2->ARR = 999;

	TIM2->DIER = TIM_DIER_UIE;

	   //настройка тамера 3
	  TIM3->PSC = 0;
	   	    TIM3->ARR = 799;

	   	    // Настроить таймер в режим ШИМ
	   	    TIM3->CCMR2 |=  TIM_CCMR2_OC4PE | 6 << TIM_CCMR2_OC4M_Pos;
	   	    TIM3->CCER |=  TIM_CCER_CC4E;
	   	    TIM3->CR1 |= TIM_CR1_ARPE;
	   	    TIM3->CCR4 = 400;

	TIM3->CR1 |= TIM_CR1_CEN;
	TIM2->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM2_IRQn);

	while(1)
	{

	}
}

void TIM2_IRQHandler(void)
{
	if (arr2_value < 1000 && direction) {
		arr2_value += 100;

		        } else {
		        	direction=0;
		        }
		if(arr2_value > 100  && direction == 0)
		{
			arr2_value -= 100;
		}else
		{
			direction = 1;
		        }
	TIM2->ARR = arr2_value;
	GPIOE->ODR ^= GPIO_ODR_OD6;
	TIM2->SR &= ~ TIM_SR_UIF;
}
