/**
  ******************************************************************************
  * @file    rcc.c
  * @brief   This file provides code for the configuration
  *          of the RCC instances.
  ******************************************************************************
	 * @attention
   * RCC configuration for STM32F407
  ******************************************************************************
 */

/************************************************************
*************************************************************/

#include "rcc.h"

/************************************************************
*************************************************************/

void RCC_Init(void)
{  
					/**
					 ****************************
					* Clock Configuration
					* SYSCLK = 168 MHz
					* AHB = 168 MHz
					* APB1 (periph) = 42  MHz
					* APB1 (timer) = 84  MHz
					* APB2 (periph) = 84  MHz
					* APB2 (timer) = 168  MHz
					*********************************
					*/

	/*1. Bit 16 HSEON: HSE clock enable */ 
	RCC->CR |=((uint32_t)RCC_CR_HSEON); /*!< HSE oscillator ON > */	

	/*2.Bit 17 HSERDY: HSE clock ready flag*/ 
	while(!(RCC->CR & (1<<7)));  /*!< Wait HSE clock ready flag > */	                

	/*3. Enable PWR clock*/
	RCC->APB1ENR |= RCC_APB1ENR_PWREN; /*!< > */	

	/*4. Bit 14 VOSRDY: Regulator voltage scaling output selection ready bit*/
	PWR->CR |= (1<<14);	/*!<Ready> */														

	/*5. Bits 7:4 HPRE: AHB prescaler*/
	RCC->CFGR &= ~ ((1<<4)|(1<<5)|(1<<6)|(1<<7));	/*!<system clock not divided> */	

	/*6. Bits 15:13 PPRE2: APB high-speed prescaler (APB2)*/
	RCC->CFGR |= (1<<15);	/*!<AHB clock divided by 2> */	

	/*7. Bits 12:10 PPRE1: APB Low speed prescaler (APB1)*/
	RCC->CFGR |= (1<<10)|(1<<12);		/*!<AHB clock divided by 4> */	

	/*8. Bits 5:0 PLLM: Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock*/
	RCC->PLLCFGR &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)); /*!<reset> */	
	RCC->PLLCFGR |= (1<<2);   /*!<PLLM = 4> */	

	/*9. Bits 14:6 PLLN: Main PLL (PLL) multiplication factor for VCO*/
	RCC->PLLCFGR &= ~(0x1FF<<6);	 /*!<reset> */	
	RCC->PLLCFGR |= (0xA8<<6); /*!<PLLN = = 168> */

	/*10. Bits 17:16 PLLP: Main PLL (PLL) division factor for main system clock*/
	RCC->PLLCFGR &= ~((1<<16)|(1<<17)); /*!<reset> */
	RCC->PLLCFGR |= (1<<16); /*!<PLLP = 2> */

	/*11.  Bit 22 PLLSRC: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source*/
	RCC->PLLCFGR |= (1<<22); /*!<HSE oscillator clock selected as PLL and PLLI2S clock entry> */

	/*12.  Bit 24 PLLON: Main PLL (PLL) enable*/
	RCC->CR |= RCC_CR_PLLON; /*!<PLL ON> */   

	/*13.  Bit 25 PLLRDY: Main PLL (PLL) clock ready flag*/
	while((RCC->CR & RCC_CR_PLLRDY) == 0){} /*!< Wait PLL ready flag > */ 

	/*14.  Bit 8 PRFTEN: Prefetch enable*/
	FLASH->ACR |= (1<<8);  /*!< Prefetch is enabled > */ 

	/*15.Bit 9 ICEN: Instruction cache enable*/
	FLASH->ACR |= (1<<9);  /*!< Instruction cache is enabled > */ 

	/*16.Bit 10 DCEN: Data cache enable*/
	FLASH->ACR |= (1<<10);  /*!< Data cache is enabled > */ 
	 
	/*17. Bits 2:0 LATENCY[2:0]: Latency*/
	FLASH->ACR &= ~((1<<0)|(1<<1)|(1<<2));  /*!< reset> */ 
	FLASH->ACR |= (1<<0)|(1<<2);  /*!< Five wait states> */ 

	/*18. Bits 1:0 SW: System clock switch*/			
	RCC->CFGR &= ~((1<<0)|(1<<1));  /*!< reset> */                   		    
	RCC->CFGR |= (1<<1); /*!< PLL selected as system clock> */  

	/*19. Bits 3:2 SWS: System clock switch status*/		
	while((RCC->CFGR & RCC_CFGR_SWS) != (1<<3)) {} /*!< PLL used as the system clock> */  
}

/************************************************************
*************************************************************/
	

/************************ (C) BORISOV RUSLAN *****END OF FILE****/

