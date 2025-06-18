#include "stm32g474xx.h"

uint32_t count = 0;
uint32_t pressed1 = 1;
uint32_t pressed2  =1;

int main(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN | RCC_AHB2ENR_GPIOBEN;

	GPIOD->MODER &= ~(GPIO_MODER_MODE9_Msk | GPIO_MODER_MODE10_Msk
			| GPIO_MODER_MODE11_Msk | GPIO_MODER_MODE12_Msk);
	GPIOD->MODER |= 1 << GPIO_MODER_MODE9_Pos | 1 << GPIO_MODER_MODE10_Pos
			| 1 << GPIO_MODER_MODE11_Pos | 1 << GPIO_MODER_MODE12_Pos;

	GPIOB->MODER &= ~(GPIO_MODER_MODE12_Msk | GPIO_MODER_MODE13_Msk
			| GPIO_MODER_MODE14_Msk);
	GPIOB->MODER |= 0 << GPIO_MODER_MODE12_Pos | 0 << GPIO_MODER_MODE13_Pos
			| 0 << GPIO_MODER_MODE14_Pos;

	while (1) {
		if ((GPIOB->IDR & GPIO_IDR_ID12) == 0 && pressed1 && count < 15){
			GPIOD->BSRR = GPIO_BSRR_BR9 | GPIO_BSRR_BR10
					| GPIO_BSRR_BR11 | GPIO_BSRR_BR12;
			count += 1;
			GPIOD->BSRR = count << 9;
			pressed1 = 0;
		}else if(GPIOB->IDR & GPIO_IDR_ID12)
		{
			pressed1 = 1;
		}
		if ((GPIOB->IDR & GPIO_IDR_ID13) == 0 && pressed2 && count > 0){
			GPIOD->BSRR = GPIO_BSRR_BR9 | GPIO_BSRR_BR10
								| GPIO_BSRR_BR11 | GPIO_BSRR_BR12;
					count -=1;
					GPIOD->BSRR = count << 9;
					pressed2 = 0;
				}else if(GPIOB->IDR & GPIO_IDR_ID13)
				{
					pressed2 = 1;
				}
		if ((GPIOB->IDR & GPIO_IDR_ID14) == 0){
							GPIOD->BSRR = GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12;
							count = 0;
		}
	}
}






