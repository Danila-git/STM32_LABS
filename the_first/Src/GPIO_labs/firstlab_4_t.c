#include "stm32g474xx.h"

uint32_t turnon = 0;
uint32_t pressed1 = 1;
uint32_t time = 300000;
uint32_t click = 0;

int main(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	GPIOD->MODER &= ~(GPIO_MODER_MODE9_Msk | GPIO_MODER_MODE10_Msk
			| GPIO_MODER_MODE11_Msk | GPIO_MODER_MODE12_Msk);
	GPIOD->MODER |= 1 << GPIO_MODER_MODE9_Pos | 1 << GPIO_MODER_MODE10_Pos
			| 1 << GPIO_MODER_MODE11_Pos | 1 << GPIO_MODER_MODE12_Pos;

	GPIOB->MODER &= ~(GPIO_MODER_MODE12_Msk);
	GPIOB->MODER |= 0 << GPIO_MODER_MODE12_Pos;

	while (1) {
		if ((GPIOB->IDR & GPIO_IDR_ID12) == 0 ){
			click+=1;
		}
		if(GPIOB->IDR & GPIO_IDR_ID12 && click < time && click > 0)
			{
			GPIOD->BSRR = GPIO_BSRR_BR9 | GPIO_BSRR_BR10
								| GPIO_BSRR_BR11 | GPIO_BSRR_BR12;
						turnon +=1;
						GPIOD->BSRR = turnon << 9;
						click = 0;
			}
			else if(GPIOB->IDR & GPIO_IDR_ID12 &&  click > time)
		{
				GPIOD->BSRR = GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12;
			click = 0;
			turnon = 0;
		}
	}
}
