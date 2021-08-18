/**
  ******************************************************************************
  * @file    exti.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
   * @attention
	 * GPIO configuration for STM32F407
  ******************************************************************************
 */

/************************************************************
*************************************************************/

#include "exti.h"


/************************************************************
*************************************************************/

void GPIO_EXTI_Init(void)
{
	/* Enable  GPIOD clock*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	/*EXTI GPIO Configuration*/  

	/*PD11   ------> DIO1_PIN (INPUT)*/ 
	/*1. Bits 2y:2y+1 MODERy[1:0]: Port D configuration bit [22;23] */	
	GPIOD->MODER &= ~((1<<22)|(1<<23)) ; /*!<00: Input (reset state)>*/

	/*2. Bits 15:0 OTy: Port D configuration bit[11] */	
	GPIOD->OTYPER |= (1<<11);/*!<1: Output open-drain>*/	
  
	/*3. Bits 2y:2y+1 OSPEEDRy[1:0]: Port D configuration bit [22;23]) */	
	GPIOD->OSPEEDR &= ~((1<<22)|(1<<23)) ; /*!<00: Low speed>*/

	/*4. Bits 2y:2y+1 PUPDRy[1:0]: Port D configuration bit [22;23]) */	
	GPIOD->PUPDR &= ~((1<<22)|(1<<23));/*!<00: No pull-up, pull-down>*/
   GPIOD->PUPDR |= (1<<23);/*!<10: pull-down>*/
	 
   /*PD0   ------> DIO1_PIN (INPUT)*/ 
	/*1. Bits 2y:2y+1 MODERy[1:0]: Port D configuration bit [0;1] */	
	GPIOA->MODER &= ~((1<<0)|(1<<1)) ; /*!<00: Input (reset state)>*/

	/*2. Bits 15:0 OTy: Port D configuration bit[0] */	
	GPIOA->OTYPER |= (1<<0);/*!<1: Output open-drain>*/	
  
	/*3. Bits 2y:2y+1 OSPEEDRy[1:0]: Port D configuration bit [0;1]) */	
	GPIOA->OSPEEDR &= ~((1<<0)|(1<<1)) ; /*!<00: Low speed>*/

	/*4. Bits 2y:2y+1 PUPDRy[1:0]: Port D configuration bit [0;1]) */	
	GPIOA->PUPDR &= ~((1<<0)|(1<<1));/*!<00: No pull-up, pull-down>*/
   GPIOA->PUPDR |= (1<<1);/*!<10: pull-down>*/
	
}
/************************************************************
*************************************************************/

void EXTI_Init(void)
{
	GPIO_EXTI_Init();
	
	/*1. Enable  SYSCFG clock*/
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	/*PD11   ------> EXTI_PIN (INPUT)*/ 
	/*1.Bits 22:0 MRx: Interrupt mask on line 11 bit[11] */	
	EXTI->IMR |= (1<<11) ; /*!<1: Interrupt request from line x is not masked>*/
	
	/*2. Bits 22:0 MRx: Event mask on line 11 bit [11] */	
	EXTI->EMR &= ~(1<<11) ; /*!<0: Event request from line x is masked>*/
	
	/*3.Bits 22:0 TRx: Rising trigger event configuration bit of line 11 bit [11] */	
	EXTI->RTSR |= (1<<11) ; /*!<1: Rising trigger enabled (for Event and Interrupt) for input line>*/
	
	/*4. Bits 22:0 TRx: Falling trigger event configuration bit of line 11 bit [11] */	
	EXTI->FTSR &= ~(1<<11) ; /*!<0: Falling trigger disabled (for Event and Interrupt) for input line>*/
	
	/*5. Bits 15:0 EXTIx[3:0]: EXTI x configuration (x = 8 to 11) bit [15:12] */	
	SYSCFG->EXTICR[2] &= ~((1<<12)|(1<<13)|(1<<14)|(1<<15)) ; /*!<reset>*/
	SYSCFG->EXTICR[2] |= (1<<12)|(1<<13) ; /*!<0011: PD[x] pin>*/
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_SetPriority(EXTI15_10_IRQn,1);
	
	
   // *PD0   ------> EXTI_PIN (INPUT)*/ 
	/*1.Bits 22:0 MRx: Interrupt mask on line 0 bit[0] */	
	EXTI->IMR |= (1<<0) ; /*!<1: Interrupt request from line x is not masked>*/
	
	/*2. Bits 22:0 MRx: Event mask on line 0 bit [0] */	
	EXTI->EMR &= ~(1<<0) ; /*!<0: Event request from line x is masked>*/
	
	/*3.Bits 22:0 TRx: Rising trigger event configuration bit of line 0 bit [0] */	
	EXTI->RTSR |= (1<<0) ; /*!<1: Rising trigger enabled (for Event and Interrupt) for input line>*/
	
	/*4. Bits 22:0 TRx: Falling trigger event configuration bit of line 0 bit [0] */	
	EXTI->FTSR &= ~(1<<0) ; /*!<0: Falling trigger disabled (for Event and Interrupt) for input line>*/
	
	/*5. Bits 15:0 EXTIx[3:0]: EXTI x configuration (x = 8 to 11) bit [0:3] */	
	SYSCFG->EXTICR[0] &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3)) ; /*!<reset>*/
	SYSCFG->EXTICR[0] |= (1<<0)|(1<<1) ; /*!<0011: PD[x] pin>*/
	
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn ,1);

}

/************************************************************
*************************************************************/




/************************ (C) BORISOV RUSLAN *****END OF FILE****/
