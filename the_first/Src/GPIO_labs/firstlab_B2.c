#include "stm32g474xx.h"

char key[9] = "";
int points = 8;
char key_word[8] = "abcddcba";
int number = 0;

uint32_t exception = 0;

void victory();
void defeat();
void dummy_delay();
void try();

int main() {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN | RCC_AHB2ENR_GPIOBEN;

	GPIOE->MODER &= ~(GPIO_MODER_MODE0_Msk | GPIO_MODER_MODE1_Msk
			| GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);
	GPIOE->MODER |= 1 << GPIO_MODER_MODE0_Pos | 1 << GPIO_MODER_MODE1_Pos
			| 1 << GPIO_MODER_MODE2_Pos | 1 << GPIO_MODER_MODE3_Pos;

	GPIOB->MODER &= ~(GPIO_MODER_MODE12_Msk | GPIO_MODER_MODE13_Msk
			| GPIO_MODER_MODE14_Msk | GPIO_MODER_MODE15_Msk);

	while (1) {
		if (exception < 3) {
			try();
		} else {
			defeat();
		}
		if (number>=points) {
			if (strncmp(key, key_word, 8) == 0) {
				GPIOE->BSRR = GPIO_BSRR_BR0 | GPIO_BSRR_BR1 | GPIO_BSRR_BR2 | GPIO_BSRR_BR3;
				victory();
			} else {
			     GPIOE->BSRR = GPIO_BSRR_BR0 | GPIO_BSRR_BR1 | GPIO_BSRR_BR2 | GPIO_BSRR_BR3;
				defeat();
				exception+=1;
				number = 0;
			}
		}
	}

}

void dummy_delay(uint32_t duration) {
	for (uint32_t i = 0; i < duration; i+=1);
}

void victory() {
	GPIOE->BSRR = GPIO_BSRR_BS0 | GPIO_BSRR_BS3;
	dummy_delay(200000);
	GPIOE->BSRR = GPIO_BSRR_BR0 | GPIO_BSRR_BR3;
	dummy_delay(200000);
	GPIOE->BSRR = GPIO_BSRR_BS1 | GPIO_BSRR_BS2;
	dummy_delay(200000);
	GPIOE->BSRR = GPIO_BSRR_BR1 | GPIO_BSRR_BR2;
}
void defeat() {
	for (int i = 0; i <= 4; i+=1) {
		GPIOE->BSRR = GPIO_BSRR_BS0;
		dummy_delay(100000);
		GPIOE->BSRR = GPIO_BSRR_BR0;
		    GPIOE->BSRR = GPIO_BSRR_BS1;
		dummy_delay(100000);
		GPIOE->BSRR = GPIO_BSRR_BR1;
			GPIOE->BSRR = GPIO_BSRR_BS2;
		dummy_delay(100000);
		GPIOE->BSRR = GPIO_BSRR_BR2;
			GPIOE->BSRR = GPIO_BSRR_BS3;
		dummy_delay(100000);
		GPIOE->BSRR = GPIO_BSRR_BR3;
			GPIOE->BSRR = GPIO_BSRR_BS2;
		dummy_delay(100000);
		GPIOE->BSRR = GPIO_BSRR_BR2;
			GPIOE->BSRR = GPIO_BSRR_BS1;
		dummy_delay(100000);
		GPIOE->BSRR = GPIO_BSRR_BR1;
	}
}

void try() {
	while(number<points)
	{
	if ((GPIOB->IDR & GPIO_IDR_ID12) == 0) {
		while((GPIOB->IDR & GPIO_IDR_ID12) == 0)
		{
		GPIOE->BSRR = GPIO_BSRR_BS0;
		}
		GPIOE->BSRR = GPIO_BSRR_BR0;
		key[number] = 'a';
		number+=1;
	}
	if ((GPIOB->IDR & GPIO_IDR_ID13) == 0) {
		while((GPIOB->IDR & GPIO_IDR_ID13) == 0)
				{
				GPIOE->BSRR = GPIO_BSRR_BS1;
				}
				GPIOE->BSRR = GPIO_BSRR_BR1;
		key[number] = 'b';
		number+=1;
	}
	if ((GPIOB->IDR & GPIO_IDR_ID14) == 0) {
		while((GPIOB->IDR & GPIO_IDR_ID14) == 0)
				{
				GPIOE->BSRR = GPIO_BSRR_BS2;
				}
				GPIOE->BSRR = GPIO_BSRR_BR2;
		key[number] = 'c';
		number+=1;
	}
	if ((GPIOB->IDR & GPIO_IDR_ID15) == 0) {
		while((GPIOB->IDR & GPIO_IDR_ID15) == 0)
				{
				GPIOE->BSRR = GPIO_BSRR_BS3;
				}
				GPIOE->BSRR = GPIO_BSRR_BR3;
		key[number] = 'd';
		number+=1;
	}
	}
}





