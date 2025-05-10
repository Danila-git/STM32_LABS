#include "stm32g474xx.h"

char key[5] = "";
char key_word[5] = "abcd";
int enter_nums = 0;

uint32_t pressed1 = 0;
uint32_t pressed2 = 0;
uint32_t pressed3 = 0;
uint32_t pressed4 = 0;
uint32_t exception = 0;

void victory();
void defeat();
void dummy_delay();
void try();

int main() {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN | RCC_AHB2ENR_GPIOBEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI12_PB | SYSCFG_EXTICR4_EXTI13_PB | SYSCFG_EXTICR4_EXTI14_PB | SYSCFG_EXTICR4_EXTI15_PB;

    EXTI->IMR1 |= EXTI_IMR1_IM12 | EXTI_IMR1_IM13 | EXTI_IMR1_IM14 | EXTI_IMR1_IM15;
  	    EXTI->FTSR1 |= EXTI_FTSR1_FT12 | EXTI_FTSR1_FT13 | EXTI_FTSR1_FT14 | EXTI_FTSR1_FT15;
  	  NVIC_EnableIRQ( EXTI15_10_IRQn );

	GPIOE->MODER &= ~(GPIO_MODER_MODE0_Msk | GPIO_MODER_MODE1_Msk
			| GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);
	GPIOE->MODER |= 1 << GPIO_MODER_MODE0_Pos | 1 << GPIO_MODER_MODE1_Pos
			| 1 << GPIO_MODER_MODE2_Pos | 1 << GPIO_MODER_MODE3_Pos;

	GPIOB->MODER &= ~(GPIO_MODER_MODE12_Msk | GPIO_MODER_MODE13_Msk
			| GPIO_MODER_MODE14_Msk | GPIO_MODER_MODE15_Msk);

	while (1) {

	}

}

void EXTI15_10_IRQHandler()
{
	if (exception < 3) {
				try();
			} else {
				defeat();
			}
			if (pressed1 == 1 && pressed2 == 1 && pressed3 == 1 && pressed4 == 1) {
				if (strncmp(key, key_word, 5) == 0) {
					victory();
				} else {
					defeat();
					exception++;
					pressed1 = 0;
					pressed2 = 0;
					pressed3 = 0;
					pressed4 = 0;
					enter_nums = 0;
				}
			}
}

void dummy_delay(uint32_t duration) {
	for (uint32_t i = 0; i < duration; i+=1);
}

void victory() {
	GPIOE->ODR |= GPIO_ODR_OD0 | GPIO_ODR_OD3;
	dummy_delay(200000);
	GPIOE->ODR &= ~(GPIO_ODR_OD0 | GPIO_ODR_OD3);
	dummy_delay(200000);
	GPIOE->ODR |= GPIO_ODR_OD1 | GPIO_ODR_OD2;
	dummy_delay(200000);
	GPIOE->ODR &= ~(GPIO_ODR_OD1 | GPIO_ODR_OD2);
}
void defeat() {
	for (int i = 0; i <= 4; i++) {
		GPIOE->ODR |= GPIO_ODR_OD0;
		dummy_delay(100000);
		GPIOE->ODR &= ~GPIO_ODR_OD0;
		GPIOE->ODR |= GPIO_ODR_OD1;
		dummy_delay(100000);
		GPIOE->ODR &= ~GPIO_ODR_OD1;
		GPIOE->ODR |= GPIO_ODR_OD2;
		dummy_delay(100000);
		GPIOE->ODR &= ~GPIO_ODR_OD2;
		GPIOE->ODR |= GPIO_ODR_OD3;
		dummy_delay(100000);
		GPIOE->ODR &= ~GPIO_ODR_OD3;
		GPIOE->ODR |= GPIO_ODR_OD2;
		dummy_delay(100000);
		GPIOE->ODR &= ~GPIO_ODR_OD2;
		GPIOE->ODR |= GPIO_ODR_OD1;
		dummy_delay(100000);
		GPIOE->ODR &= ~GPIO_ODR_OD1;
		GPIOE->ODR |= GPIO_ODR_OD0;
		dummy_delay(100000);
		GPIOE->ODR &= ~GPIO_ODR_OD0;
	}
}

void try() {
	if ((GPIOB->IDR & GPIO_IDR_ID12) == 0 && pressed1 == 0) {
		GPIOE->BSRR = GPIO_BSRR_BS0;
		key[enter_nums] = 'a';
		key[enter_nums + 1] = '\0';
		enter_nums+=1;
		pressed1 = 1;
	}
	if ((GPIOB->IDR & GPIO_IDR_ID13) == 0 && pressed2 == 0) {
		GPIOE->BSRR = GPIO_BSRR_BS1;
		key[enter_nums] = 'b';
		key[enter_nums + 1] = '\0';
		enter_nums+=1;
		pressed2 = 1;
	}
	if ((GPIOB->IDR & GPIO_IDR_ID14) == 0 && pressed3 == 0) {
		GPIOE->BSRR = GPIO_BSRR_BS2;
		key[enter_nums] = 'c';
		key[enter_nums + 1] = '\0';
		enter_nums+=1;
		pressed3 = 1;
	}
	if ((GPIOB->IDR & GPIO_IDR_ID15) == 0 && pressed4 == 0) {
		GPIOE->BSRR = GPIO_BSRR_BS3;
		key[enter_nums] = 'd';
		key[enter_nums + 1] = '\0';
		enter_nums+=1;
		pressed4 = 1;
	}
}

