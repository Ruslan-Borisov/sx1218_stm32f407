/**
  ******************************************************************************
  * @file    spi_slave.c
  * @brief   This file provides code for the configuration
  *          spi
  ******************************************************************************
	 * @attention
   * SPI configuration for STM32F407
  ******************************************************************************
 */


#include "spi_slave.h"

void spi_slave_init(void)
{
	
	gpio_spi_slave_init();
	
  /*1. Enable SPI2  clock*/
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;	
	
	/*2. Bit 9 SSM: Software slave management*/
  SPI2->CR1 |= (1<<9);  /*!<Software slave management enabled > */
	
	/*3.Bit 8 SSI: Internal slave select*/
  SPI2->CR1 &= ~(1<<8);  /*!<This bit has an effect only when the SSM bit is set. The value of this bit is forced onto the NSS pin and the IO value of the NSS pin is ignored > */
	
	/*4. Bit 2 MSTR: Master selection*/
  SPI2->CR1 &= ~(1<<2);  /*!<1: Slave configuration> */
	
	/*5. Bits 5:3 BR[2:0]: Baud rate control*/
	SPI2->CR1 |= (1<<3)|(1<<4)|(1<<5);  /*!<111: fPCLK/256> */
		
	/*7. Bit 0 RXDMAEN: Rx buffer DMA enable*/
	SPI2->CR2 |= (1<<0);  /*!<1: Rx buffer DMA enabled> */
  
  /*8. Bit 6 SPE: SPI enable*/
	SPI2->CR1 |= (1<<6);  /*!<1: Peripheral enabled> */
	
  DMA1_Stream3_SPI_RX_Init();
}

void gpio_spi_slave_init(void)
{
	 /*1. Enable GPIOD  clock*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	
		 /*1. Enable GPIOC  clock*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	
	  /* PB10   ------> SPI2_SCK*/	
	/*2. Bits 31:0 AFRHy: Alternate function selection for port B bit [11:8]*/	
	GPIOB->AFR[1] &=~ ((1<<8)|(1<<9)|(1<<10)|(1<<11)); /*!< reset>*/
	GPIOB->AFR[1] |= (1<<8)|(1<<10); /*!< 0101: AF5 - SPI2_SCK >*/
		
  /*3. Bits 2y:2y+1 MODERy[1:0]: Port B configuration bits [21;20] */	
  GPIOB->MODER &= ~((1<<20)|(1<<21)) ;	/*!<reset>*/		
	GPIOB->MODER |=  (1<<21) ;	/*!<Alternate function mode>*/
		
	/*4. Bits 2y:2y+1 OSPEEDRy[1:0]: Port B configuration bits [21:20]*/		
	GPIOB->OSPEEDR |=(1<<21)|(1<<20); /*!<11: Very high speed>*/
	
	  /* PC2  ------> SPI2_MISO*/	
	/*2. Bits 31:0 AFRHy: Alternate function selection for port C bit [11;8]*/	
	GPIOC->AFR[0] &= ~((1<<8)|(1<<9)|(1<<10)|(1<<11)); /*!< reset>*/
	GPIOC->AFR[0] |= (1<<8)|(1<<10); /*!< 0101: AF5 - SPI1_MISO >*/
		
  /*3. Bits 2y:2y+1 MODERy[1:0]: Port C configuration bits [5;4] */	
  GPIOC->MODER &= ~((1<<4)|(1<<5)) ;	/*!<reset>*/		
	GPIOC->MODER |=  (1<<3) ;	/*!<Alternate function mode>*/
		
	/*4. Bits 2y:2y+1 OSPEEDRy[1:0]: Port C configuration bits [5;4]*/		
	GPIOC->OSPEEDR |=(1<<4)|(1<<5); /*!<11: Very high speed>*/
	
 
  /* PC3   ------> SPI2_MOSI*/	
	/*2. Bits 31:0 AFRHy: Alternate function selection for port C bit [15;12]*/	
	GPIOC->AFR[0] &= ~((1<<12)|(1<<13)|(1<<14)|(1<<15)); /*!< reset>*/
	GPIOC->AFR[0] |= (1<<12)|(1<<14); /*!< 0101: AF5 - SPI1_MOSI >*/
		
  /*3. Bits 2y:2y+1 MODERy[1:0]: Port C configuration bits [7;6] */	
    GPIOC->MODER &= ~((1<<7)|(1<<6)) ;	/*!<reset>*/		
	GPIOC->MODER |=  (1<<7) ;	/*!<Alternate function mode>*/
		
	/*4. Bits 2y:2y+1 OSPEEDRy[1:0]: Port C configuration bits [7;6]*/		
	GPIOC->OSPEEDR |=(1<<7)|(1<<6); /*!<11: Very high speed>*/
	
}


/************************ (C) BORISOV RUSLAN *****END OF FILE****/

