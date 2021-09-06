
/**
  ******************************************************************************
  * @file    i2c_oled.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
   * @attention
	 * GPIO configuration for STM32F407
  ******************************************************************************
 */

/************************************************************
*************************************************************/

#include "i2c_oled.h"

/************************************************************
*************************************************************/

void i2c_oled_init()
{
	
	i2c_gpio_init();
	
	/*1. Enable I2C1 clock*/
	RCC->APB1ENR |=RCC_APB1ENR_I2C1EN;
	
	/*2. Bits 5:0 FREQ[5:0]: Peripheral clock frequency*/
	I2C1->CR2 &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)); /*!<reset> */
  I2C1->CR2 |= (0x2A<<0); /*!<42 MHz> */
	
	/*3. Bits 11:0 CCR[11:0]: Clock control register in Fm/Sm mode (Master mode)*/
	I2C1->CCR  &= ~(0xFFF<<0);/*!<reset> */
	I2C1->CCR  = 0x0023; /*!< 210 ns> */
	
	/*3.Bit 15  F/S: I2C master mode selection*/
	I2C1->CCR  |= (1<<15); /*!< 1: Fm mode I2C> */
	
	/*4. Bits 5:0 TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)*/
	I2C1->TRISE &= ~(0x3F<<0);/*!<reset> */
	I2C1->TRISE  = 0x0D; /*!< 43 ns> */
	
	
	/* Bit 0 PE: Peripheral enable*/
  I2C1->CR1 |= (1<<0); /*!<1: Peripheral enable> */

}
/************************************************************
*************************************************************/
void i2c_gpio_init()
{
  	/*1. Enable GPIOB clock*/
	  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	
		/* PB6   ------> I2C_SCL*/	
	
	/*2. Bits 31:0 AFRHy: Alternate function selection for port B bit [27;24]*/	
	GPIOB->AFR[0] &=~ ((1<<24)|(1<<25)|(1<<26)|(1<<27)); /*!< reset>*/
	GPIOB->AFR[0] |= (1<<26); /*!< 0100: AF4 - I2C1_SCL >*/

	/*3. Bits 2y:2y+1 MODERy[1:0]: Port B configuration bits [13;12] */	
	GPIOB->MODER &= ~((1<<13)|(1<<12)) ;	/*!<reset>*/		
	GPIOB->MODER |=  (1<<13) ;	/*!<Alternate function mode>*/

	/*4. Bits 2y:2y+1 OSPEEDRy[1:0]: Port x configuration bits [13;12]*/		
	GPIOB->OSPEEDR &= ~((1<<13)|(1<<12)) ;	/*!<reset>*/
	GPIOB->OSPEEDR |=(1<<13)|(1<<12); /*!<11: Very high speed>*/
	
	/*5. PUPDRy[1:0]: Port x configuration bits (y = 0..15) [13;12] */	
	GPIOB->PUPDR &= ~((1<<13)|(1<<12)) ;	/*!<reset>*/		
  GPIOB->PUPDR |=  (1<<12) ;	/*!<01: Pull-up>*/
	
	/*6.OTy: Port x configuration bits (y = 0..15) [6] */		
  GPIOB->OTYPER |=  (1<<6) ;	/*!<1: Output open-drain>*/
	
	
		/* PB7  ------> I2C_SDA*/	
	
		/*2. Bits 31:0 AFRHy: Alternate function selection for port B bit [31;28]*/	
	GPIOB->AFR[0] &=~ ((1<<28)|(1<<29)|(1<<30)|(1<<31)); /*!< reset>*/
	GPIOB->AFR[0] |= (1<<30); /*!< 0100: AF4 - I2C1_SDA >*/

	/*3. Bits 2y:2y+1 MODERy[1:0]: Port B configuration bits [15;14] */	
	GPIOB->MODER &= ~((1<<14)|(1<<15)) ;	/*!<reset>*/		
	GPIOB->MODER |=  (1<<15) ;	/*!<Alternate function mode>*/

	/*4. Bits 2y:2y+1 OSPEEDRy[1:0]: Port x configuration bits [15;14]*/		
	GPIOB->OSPEEDR &= ~((1<<14)|(1<<15)) ;	/*!<reset>*/
	GPIOB->OSPEEDR |=(1<<14)|(1<<15); /*!<11: Very high speed>*/
	
	/*5. PUPDRy[1:0]: Port x configuration bits (y = 0..15) [15;14] */	
	GPIOB->PUPDR &= ~((1<<14)|(1<<15)) ;	/*!<reset>*/		
	GPIOB->PUPDR |=  (1<<14) ;	/*!<01: Pull-up>*/
	 
	 /*6.OTy: Port x configuration bits (y = 0..15) [7] */		
  GPIOB->OTYPER |=  (1<<7) ;	/*!<1: Output open-drain>*/
}
/************************************************************
*************************************************************/






/************************ (C) BORISOV RUSLAN *****END OF FILE****/

