/**
  ******************************************************************************
  * @file    spi_master.c
  * @brief   This file provides code for the configuration
  *          spi
  ******************************************************************************
	 * @attention
   * SPI configuration for STM32F407
  ******************************************************************************
 */
/************************************************************
*************************************************************/

#include "spi.h"
#include "dma _spi.h"

/************************************************************
*************************************************************/

void spi_master_init(void)
{
	gpio_spi_master_init();
	
	/*1. Enable SPI1  clock*/
	
	 volatile uint32_t tmp;
   RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
   tmp = RCC->APB2ENR;
   (void)tmp;
		
	/*2. Bit 9 SSM: Software slave management*/
	SPI1->CR1 |= (1<<9);  /*!<Software slave management enabled > */
	
	/*3.Bit 8 SSI: Internal slave select*/
	SPI1->CR1 |= (1<<8);  /*!<This bit has an effect only when the SSM bit is set. 
	The value of this bit is forced onto the NSS pin and the IO value of the NSS pin is ignored > */
	
	/*4. Bit 2 MSTR: Master selection*/
	SPI1->CR1 |= (1<<2);  /*!<1: Master configuration> */
	
	/*5. Bits 5:3 BR[2:0]: Baud rate control*/
	SPI1->CR1  &= ~ (1<<3)|(1<<4)|(1<<5);   /*!<111: fPCLK/256> */
	SPI1->CR1  |= (1<<4);  /*!<010: fPCLK/8> */
	
	/*7. Bit 0 RXDMAEN: Rx buffer DMA enable*/
	SPI1->CR2 &= ~ (1<<0);  /*!<1: Rx buffer DMA enabled> */
  
	
#ifdef _SLEVE
    	
	/*3.Bit 8 SSI: Internal slave select*/
	SPI1->CR1 &= ~ (1<<8);  /*!<This bit has an effect only when the SSM bit is set. 
	The value of this bit is forced onto the NSS pin and the IO value of the NSS pin is ignored > */
	
	/*4. Bit 2 MSTR: Master selection*/
	SPI1->CR1 &= ~ (1<<2);  /*!<1: Master configuration> */
  
#endif
	 
	
	/*8. Bit 6 SPE: SPI enable*/
	SPI1->CR1 |= (1<<6);  /*!<1: Peripheral enabled> */
	
	//DMA2_Stream0_SPI_RX_Init();

}
/************************************************************
*************************************************************/
void gpio_spi_master_init(void)
{
	/*Enable GPIOA  clock*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	/* PA5   ------> SPI1_SCK*/	
	/*2. Bits 31:0 AFRуHy: Alternate function selection for port B bit [23:20]*/	
	GPIOA->AFR[0] &=~ ((1<<20)|(1<<21)|(1<<22)|(1<<23)); /*!< reset>*/
	GPIOA->AFR[0] |= (1<<20)|(1<<22); /*!< 0101: AF5 - SPI1_SCK >*/

	/*3. Bits 2y:2y+1 MODERy[1:0]: Port B configuration bits [10:11]] */	
	GPIOA->MODER &= ~((1<<10)|(1<<11)) ;	/*!<reset>*/		
	GPIOA->MODER |=  (1<<11) ;	/*!<Alternate function mode>*/

	/*4. Bits 2y:2y+1 OSPEEDRy[1:0]: Port B configuration bits [10:11]]*/		
	GPIOA->OSPEEDR |=(1<<10)|(1<<11); /*!<11: Very high speed>*/

	/* PA6  ------> SPI1_MISO*/	
	/*2. Bits 31:0 AFRHy: Alternate function selection for port C bit [24;27]*/	
	GPIOA->AFR[0] &= ~((1<<24)|(1<<25)|(1<<26)|(1<<27)); /*!< reset>*/
	GPIOA->AFR[0] |= (1<<24)|(1<<26); /*!< 0101: AF5 - SPI1_MISO >*/

	/*3. Bits 2y:2y+1 MODERy[1:0]: Port C configuration bits [12;13] */	
	GPIOA->MODER &= ~((1<<12)|(1<<13)) ;	/*!<reset>*/		
	GPIOA->MODER |=  (1<<13) ;	/*!<10 Alternate function mode>*/

	/*4. Bits 2y:2y+1 OSPEEDRy[1:0]: Port C configuration bits [12;13]*/		
	GPIOA->OSPEEDR |=(1<<12)|(1<<13); /*!<11: Very high speed>*/

	/* PA7   ------> SPI1_MOSI*/	
	/*2. Bits 31:0 AFRHy: Alternate function selection for port C bit [31;27]*/	
	//GPIOA->AFR[0] &= ~((1<<12)|(1<<13)|(1<<14)|(1<<15)); /*!< reset>*/
	GPIOA->AFR[0] |= (1<<27)|(1<<29); /*!< 0101: AF5 - SPI1_MOSI >*/

	/*3. Bits 2y:2y+1 MODERy[1:0]: Port C configuration bits [14;15] */	
	GPIOA->MODER &= ~((1<<14)|(1<<15)) ;	/*!<reset>*/		
	GPIOA->MODER |=  (1<<15) ;	/*!<Alternate function mode>*/

	/*4. Bits 2y:2y+1 OSPEEDRy[1:0]: Port C configuration bits [14;15]*/		
	GPIOA->OSPEEDR |=(1<<14)|(1<<15); /*!<11: Very high speed>*/

}

/************************************************************
*************************************************************/


/************************ (C) BORISOV RUSLAN *****END OF FILE****/

