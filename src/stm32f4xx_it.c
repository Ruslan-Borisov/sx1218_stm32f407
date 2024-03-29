/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
	 * @attention
   * Configuration for STM32F407
  ******************************************************************************
 */

/************************************************************
*************************************************************/
 
#include "stm32f4xx_it.h"

/************************************************************
*************************************************************/

/* DMA interrupt handler DMA2_Stream2 (USRT1_RX) */
void DMA2_Stream2_IRQHandler(void) 
{
	if(DMA2->LISR & (1<<21))
	{	
		DMA2->LIFCR |= (1<<21);	
    	irqFlagUSART1_RX = 1;	
	}
}

/************************************************************
*************************************************************/

/* DMA interrupt handler DMA2_Stream7 (USRT1_TX) */
void DMA2_Stream7_IRQHandler(void) 
{
	if(DMA2->HISR & (1<<5) )
	{	
		DMA2->HIFCR |= (1<<5);	
      irqFlagUSART1_TX = 1;		
	}
}

/************************************************************
*************************************************************/

/* DMA interrupt handler DMA2_Stream0 (SPI1_RX) */	
void DMA2_Stream0_IRQHandler(void) 
{
	if(DMA2->LISR & (1<<5) )
	{	
		DMA2->LIFCR |= (1<<5);
      irqFlagSPI_RX = 1;		
	}
}

/************************************************************
*************************************************************/	

/*USART1 interrupt handler RX*/	
void USART1_IRQHandler(void)
{
	USART1->SR &=~(1<<7);	
}

/************************************************************
*************************************************************/

/*External Interrupt Handler (PD11)*/
void EXTI15_10_IRQHandler(void)
{
	EXTI->PR = (1<<11);
	irqFlagEXTI_DIO0 = 1;
}

/************************************************************
*************************************************************/
	


/************************ (C) BORISOV RUSLAN *****END OF FILE****/
