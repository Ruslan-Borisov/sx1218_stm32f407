/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
   * @attention
	 * GPIO configuration for STM32F407
  ******************************************************************************
 */

/************************************************************
*************************************************************/

#include "gpio.h"


/************************************************************
*************************************************************/

void GPIO_Init(void)
{
	/* Enable  GPIOD clock*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	/*XS1278 GPIO Configuration*/  
	/*PD10   ------> RESET_PIN (OUTPUT)*/ 
	/*1. Bits 2y:2y+1 MODERy[1:0]: Port D configuration bit [20;21] */	
	GPIOD->MODER &= ~((1<<21)|(1<<20)) ; /*!<reset>*/
	GPIOD->MODER |=  (1<<20);	 /*!<01: General purpose output mode>*/

	/*2. Bits 15:0 OTy: Port D configuration bit[10] */	
	GPIOD->OTYPER &= ~(1<<10);/*!<0: Output push-pull (reset state)>*/	

	/*3. Bits 2y:2y+1 OSPEEDRy[1:0]: Port D configuration bit [21;20]) */	
	GPIOD->OSPEEDR &= ~((1<<21)|(1<<20)) ; /*!<00: Low speed>*/

	/*4. Bits 2y:2y+1 PUPDRy[1:0]: Port x configuration bit [21;20]) */	
	GPIOD->PUPDR &= ~((1<<21)|(1<<20));/*!<00: No pull-up, pull-down>*/
	

	/*PD12   ------> NSS_PIN (OUTPUT)*/ 
	/*1. Bits 2y:2y+1 MODERy[1:0]: Port D configuration bit [24;25] */	
	GPIOD->MODER &= ~((1<<24)|(1<<25)) ; /*!<reset>*/
	GPIOD->MODER |=  (1<<24);	 /*!<01: General purpose output mode>*/

	/*2. Bits 15:0 OTy: Port D configuration bit[12] */	
	GPIOD->OTYPER &= ~(1<<12);/*!<0: Output push-pull (reset state)>*/	

	/*3. Bits 2y:2y+1 OSPEEDRy[1:0]: Port D configuration bit [24;25]) */	
	GPIOD->OSPEEDR &= ~((1<<24)|(1<<25)) ; /*!<00: Low speed>*/

	/*4. Bits 2y:2y+1 PUPDRy[1:0]: Port D configuration bit [24;25]) */	
	GPIOD->PUPDR &= ~((1<<21)|(1<<20));/*!<00: No pull-up, pull-down>*/
 
		/*PD3   ------> LORA_SET_PIN (OUTPUT)*/ 
	/*1. Bits 2y:2y+1 MODERy[1:0]: Port D configuration bit [6;7] */	
	GPIOD->MODER &= ~((1<<6)|(1<<7)) ; /*!<reset>*/
	GPIOD->MODER |=  (1<<6);	 /*!<01: General purpose output mode>*/

	/*2. Bits 15:0 OTy: Port D configuration bit[3] */	
	GPIOD->OTYPER &= ~(1<<3);/*!<0: Output push-pull (reset state)>*/	

	/*3. Bits 2y:2y+1 OSPEEDRy[1:0]: Port D configuration bit [6;7]) */	
	GPIOD->OSPEEDR &= ~((1<<6)|(1<<7)) ; /*!<00: Low speed>*/

	/*4. Bits 2y:2y+1 PUPDRy[1:0]: Port D configuration bit [6;7]) */	
	GPIOD->PUPDR &= ~((1<<6)|(1<<7));/*!<00: No pull-up, pull-down>*/
	GPIOD->PUPDR |=(1<<7);/*!<10: Pull-down>*/
	GPIOD->BSRR |=  GPIO_BSRR_BR3;
	
	
	/* Enable  GPIOD clock*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	/*SET_OLED GPIO Configuration*/  

	/*PC11   ------> SET_OLED_PIN (INPUT)*/ 
	/*1. Bits 2y:2y+1 MODERy[1:0]: Port C configuration bit [22;23] */	
	GPIOC->MODER &= ~((1<<22)|(1<<23)) ; /*!<00: Input (reset state)>*/

	/*2. Bits 15:0 OTy: Port C configuration bit[11] */	
	GPIOC->OTYPER |= (1<<11);/*!<1: Output open-drain>*/	
  
	/*3. Bits 2y:2y+1 OSPEEDRy[1:0]: Port C configuration bit [22;23]) */	
	GPIOC->OSPEEDR &= ~((1<<22)|(1<<23)) ; /*!<00: Low speed>*/

	/*4. Bits 2y:2y+1 PUPDRy[1:0]: Port C configuration bit [22;23]) */	
	GPIOC->PUPDR &= ~((1<<22)|(1<<23));/*!<00: No pull-up, pull-down>*/
  GPIOC->PUPDR |= (1<<23);/*!<10: pull-down>*/
	 

}
/************************************************************
*************************************************************/





/************************ (C) BORISOV RUSLAN *****END OF FILE****/
