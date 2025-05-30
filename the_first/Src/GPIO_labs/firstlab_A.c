#include "stm32g474xx.h"

uint32_t pressed = 1;
void dummy_delay(uint32_t duration);

int main(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOEEN;

    GPIOE->MODER &= ~(GPIO_MODER_MODE3_Msk | GPIO_MODER_MODE4_Msk | GPIO_MODER_MODE5_Msk | GPIO_MODER_MODE6_Msk );
    GPIOE->MODER |= 1 << GPIO_MODER_MODE3_Pos | 1 << GPIO_MODER_MODE4_Pos | 1 << GPIO_MODER_MODE5_Pos | 1 << GPIO_MODER_MODE6_Pos;

    GPIOB->MODER &= ~(GPIO_MODER_MODE12_Msk);

    while(1)
    {
    	if((GPIOB->IDR & GPIO_IDR_ID12) == 0)
    	{
    		if(pressed == 0)
    		            {
    		            	pressed = 1;
    		    		}
    		    		else
    		    		{
    		    		pressed = 0;
    		    		}
    	}
    	else if(pressed == 1)
    	{
    		GPIOE->BSRR = GPIO_BSRR_BR3 | GPIO_BSRR_BR4 | GPIO_BSRR_BR5 | GPIO_BSRR_BR6;
    		GPIOE->BSRR = GPIO_BSRR_BS3;
    		dummy_delay(100000);
    		GPIOE->BSRR = GPIO_BSRR_BR3;
    		GPIOE->BSRR = GPIO_BSRR_BS4;
    	    dummy_delay(100000);
    	    GPIOE->BSRR = GPIO_BSRR_BR4;
    	    GPIOE->BSRR = GPIO_BSRR_BS5;
      		dummy_delay(100000);
      		GPIOE->BSRR = GPIO_BSRR_BR5;
            GPIOE->BSRR = GPIO_BSRR_BS6;
    	    dummy_delay(100000);
    	    GPIOE->BSRR = GPIO_BSRR_BR6;
            GPIOE->BSRR = GPIO_BSRR_BS5;
            dummy_delay(100000);
            GPIOE->BSRR = GPIO_BSRR_BR5;
            GPIOE->BSRR = GPIO_BSRR_BS4;
            dummy_delay(100000);
            GPIOE->BSRR = GPIO_BSRR_BR4;
    	}
    	else if(pressed == 0)
    	{
    		GPIOE->BSRR = GPIO_BSRR_BR3 | GPIO_BSRR_BR4 | GPIO_BSRR_BR5 | GPIO_BSRR_BR6;
    		GPIOE->BSRR = GPIO_BSRR_BS3 | GPIO_BSRR_BS6;
    		    		     dummy_delay(200000);
    		    		     GPIOE->BSRR = GPIO_BSRR_BR3 | GPIO_BSRR_BR6;
    		    		   	 dummy_delay(200000);
    		    		   	GPIOE->BSRR = GPIO_BSRR_BS4 | GPIO_BSRR_BS5;
    		    		     dummy_delay(200000);
    		    		     GPIOE->BSRR = GPIO_BSRR_BR4 | GPIO_BSRR_BR5;
    	}
    }
}

void dummy_delay(uint32_t duration)
{
        for(uint32_t i = 0; i < duration; i+=1);
}








