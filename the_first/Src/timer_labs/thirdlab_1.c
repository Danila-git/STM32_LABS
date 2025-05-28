#include "stm32g474xx.h"

void setup_clock();

int main (void)
{
	void setup_clock();
    while ( 1 )
    {
    }
}

//устанавливаю частоту процессора 32МГц
void setup_clock()
{
  FLASH->ACR &= ~FLASH_ACR_LATENCY_Msk;
  FLASH->ACR |= FLASH_ACR_LATENCY_1WS;

  RCC->CR |= RCC_CR_HSEON;//в нашем случае частота 8MГц
  while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY) {}

  RCC->PLLCFGR&=~(RCC_PLLCFGR_PLLR_Msk | RCC_PLLCFGR_PLLM_Msk | RCC_PLLCFGR_PLLN_Msk);


  RCC->PLLCFGR |= 1 << RCC_PLLCFGR_PLLR_Pos // Установка делителя R=4
                  | RCC_PLLCFGR_PLLREN    // Включение R делителя PLL
                  | 32 << RCC_PLLCFGR_PLLN_Pos // Установка умножителя N=32
                  | 1 << RCC_PLLCFGR_PLLM_Pos // Установка делителя M=2
                  | RCC_PLLCFGR_PLLSRC_HSE; // HSE - источник сигнала для PLL

  RCC->CR |= RCC_CR_PLLON;


  while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY){}

  RCC->CFGR |= RCC_CFGR_SW_Msk;
  RCC->CFGR &= ~(RCC_CFGR_SW_Msk ^ RCC_CFGR_SW_PLL);

  while ((RCC->CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL){}
  }
