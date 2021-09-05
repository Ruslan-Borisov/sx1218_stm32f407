
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

#define T191_Addr 0x78

/************************************************************
*************************************************************/

void i2c_oled_init()
{
	
	i2c_gpio_init();
	
	/*1. Enable I2C1 clock*/
	RCC->AHB1ENR |=RCC_APB1ENR_I2C1EN;
	
	/*2. Bits 5:0 FREQ[5:0]: Peripheral clock frequency*/
	I2C1->CR2 &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)); /*!<reset> */
  I2C1->CR2 |= (0x2A<<0); /*!<42 MHz> */
	
	/*3. Bits 11:0 CCR[11:0]: Clock control register in Fm/Sm mode (Master mode)*/
	I2C1->CCR  &= ~(0xFFF<<0);/*!<reset> */
	I2C1->CCR  = 0x00D2; /*!< 210 ns> */
	
	/*4. Bits 5:0 TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)*/
	I2C1->TRISE &= ~(0x3F<<0);/*!<reset> */
	I2C1->TRISE  = 0x2B; /*!< 43 ns> */
	
	
	/* Bit 0 PE: Peripheral enable*/
  I2C1->CR1 |= (1<<0); /*!<1: Peripheral enable> */

}
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
	GPIOB->OSPEEDR |=(1<<13); /*!<High speed>*/
	
	
	
		/* PB7  ------> I2C_SDA*/	
	
		/*2. Bits 31:0 AFRHy: Alternate function selection for port B bit [31;28]*/	
	GPIOB->AFR[0] &=~ ((1<<28)|(1<<29)|(1<<30)|(1<<31)); /*!< reset>*/
	GPIOB->AFR[0] |= (1<<30); /*!< 0100: AF4 - I2C1_SDA >*/

	/*3. Bits 2y:2y+1 MODERy[1:0]: Port B configuration bits [15;14] */	
	GPIOB->MODER &= ~((1<<14)|(1<<15)) ;	/*!<reset>*/		
	GPIOB->MODER |=  (1<<15) ;	/*!<Alternate function mode>*/

	/*4. Bits 2y:2y+1 OSPEEDRy[1:0]: Port x configuration bits [15;14]*/		
	GPIOB->OSPEEDR &= ~((1<<14)|(1<<15)) ;	/*!<reset>*/
	GPIOB->OSPEEDR |=(1<<15); /*!<High speed>*/
}

void I2C_Write(uint8_t reg_addr, uint8_t data)
{
        //стартуем
   I2C1->CR1 |= I2C_CR1_START;		
	 while(!(I2C1->SR1 & I2C_SR1_SB)){};
	 (void) I2C1->SR1;
		
        //передаем адрес устройства
	 I2C2->DR = I2C_ADDRESS(ADDR,I2C_MODE_WRITE);
	 while(!(I2C1->SR1 & I2C_SR1_ADDR)){};
	(void) I2C1->SR1;
	(void) I2C1->SR2;
		
        //передаем адрес регистра
	I2C2->DR = reg_addr;	
	while(!(I2C1->SR1 & I2C_SR1_TXE)){};	
			
        //пишем данные	
	I2C2->DR = data;	
	while(!(I2C1->SR1 & I2C_SR1_BTF)){};	
	I2C2->CR1 |= I2C_CR1_STOP;		
}






/************************ (C) BORISOV RUSLAN *****END OF FILE****/

