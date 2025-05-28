#include "stm32g474xx.h"

void setup_clock();

int main (void)
{
    setup_clock();

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;


    GPIOD->MODER &= ~( GPIO_MODER_MODE8_Msk);
    GPIOD->MODER |= 1 <<  GPIO_MODER_MODE8_Pos;

   //переполнение каждые 0.5 с
    TIM3->PSC = 31999;
    TIM3->ARR = 499;
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1 |= TIM_CR1_CEN;
    NVIC_EnableIRQ (TIM3_IRQn);


    while ( 1 )
    {
    }
}

void TIM3_IRQHandler (void)
{
    GPIOD->ODR ^= GPIO_ODR_OD8;
    TIM3->SR &= ~ TIM_SR_UIF;
}


//устанавливаю частоту процессора 32МГц
void setup_clock()
{
  FLASH->ACR &= ~FLASH_ACR_LATENCY_Msk;
  FLASH->ACR |= FLASH_ACR_LATENCY_1WS;

  RCC->CR |= RCC_CR_HSEON;
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
