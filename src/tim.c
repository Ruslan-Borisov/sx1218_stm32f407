/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
  ******************************************************************************
  * @attention
  * TIM configuration for STM32F407
  ******************************************************************************
  */
/************************************************************
*************************************************************/

#include "tim.h"

/************************************************************
*************************************************************/

void TIM6_Init(void)
{
	/*1. Enable TIM2 clock*/
	 RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; 
	
   /*2. TIMx prescaler*/
	 TIM6->PSC = 0;  /*!< >*/
	
	/*3. TIMx auto-reload register*/
    TIM6->ARR =  47999;	/*!< >*/
	
	/*5. Bits 6:4 MMS[2:0]: Master mode selection*/
	 TIM6->CR2 =  (1<<5); /*!<Update>*/
	
   /*6.Bit 3 OPM: One-pulse moden*/
	 TIM6->CR1 =  (1<<3); /*!<1: Counter stops counting at the next update event (clearing the CEN bit).>*/
	
	/*6. Bit 0 CEN: Counter enable*/
	 //TIM6->CR1 |= (1<<0); /*!<Counter enabled>*/
	
}
/************************************************************
*************************************************************/

void timDelayMs(uint32_t msec) 
{
	for(int i=0; i<msec; i++)
	{
		TIM6->ARR =  ARR_FOR_1ms;
		TIM6->PSC  = PCS_FOR_1ms;
		TIM6->CR1 |= (1<<0);
		while (TIM6->CR1&(1<<0)){}
	}	
}
/************************************************************
*************************************************************/



/************************ (C) BORISOV RUSLAN *****END OF FILE****/

