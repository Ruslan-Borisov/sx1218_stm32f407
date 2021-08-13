/**
  ******************************************************************************
  * @file    SX1278_hw.c
  * @brief   
  ******************************************************************************
	 * @attention
  ******************************************************************************
 */

#include "tim.h"
#include "SX1278_hw.h"
#include <string.h>
#include "spi_master.h"
#include "main.h"
#include "gpio.h"

#define SPI_STATE_READY  (1<<15)

 void SX1278_hw_init() {
	SX1278_hw_SetNSS(1);
	RST_SET();
}

 void SX1278_hw_SetNSS(int value) {
	NSS_GPIO_BSRR  |= ((value == 1) ? NSS_SET: NSS_RESET);
}

 void SX1278_hw_Reset() {
	SX1278_hw_SetNSS(1);
	RST_RESET();
	timDelayMs(1);
	RST_SET();
	timDelayMs(100);
}



int SX1278_hw_GetDIO0() {
	return (DIO0_GPIO_ODR & DIO0_GPIO_STATUS)==SET ? 1:0;
}

void ReadBurst( uint8_t cmd, char *buff, uint8_t size ){
	uint8_t i;
	SX1278_hw_SetNSS(0);
	while (MISO_HIGH()){};
	while (!(SPI2->SR & SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = (cmd | 0x80);
	while (SPI2->SR & SPI_SR_BSY){};
	while (!(SPI2->SR & SPI_SR_RXNE)){}; 
   *((__IO uint8_t *)&SPI2->DR);		
	for(i = 0; i < size;i ++){
	   while (!(SPI2->SR & SPI_SR_TXE)){};	
	     *((__IO uint8_t *)&SPI2->DR);		
			while (SPI2->SR & SPI_SR_BSY){};
			while (!(SPI2->SR & SPI_SR_RXNE)){};
			buff[i] = *((__IO uint8_t *)&SPI2->DR);		
		}
	SX1278_hw_SetNSS(1);
}



void WriteBurst( uint8_t addr, char *buff, uint8_t size ){
	uint8_t i;
	SX1278_hw_SetNSS(0);
	while (!(SPI2->SR & SPI_SR_TXE)){};	
	*((__IO uint8_t *)&SPI2->DR) = (addr | 0x80);
	while (SPI2->SR & SPI_SR_BSY){};		
	while (!(SPI2->SR & SPI_SR_RXNE)){}; 
	*((__IO uint8_t *)&SPI2->DR);	
	for(i = 0;i < size;i ++){
			while (!(SPI2->SR & SPI_SR_TXE)){};	
			*((__IO uint8_t *)&SPI2->DR) = buff[i]; 
			while (SPI2->SR & SPI_SR_BSY){};
			while (!(SPI2->SR & SPI_SR_RXNE)){};
			*((__IO uint8_t *)&SPI2->DR);	;	
		}
	SX1278_hw_SetNSS(1);
}

uint8_t WriteSingle(uint8_t cmd, uint8_t signal){
	SX1278_hw_SetNSS(0);
	uint8_t temp;
	while (!(SPI2->SR & SPI_SR_TXE)){};  
	*((__IO uint8_t *)&SPI2->DR) = (cmd | 0x80);
	while (SPI2->SR & SPI_SR_BSY){};
	while (!(SPI2->SR & SPI_SR_RXNE)){}; 
	temp=*((__IO uint8_t *)&SPI2->DR);
	while (!(SPI2->SR & SPI_SR_TXE)){};	 
	*((__IO uint8_t *)&SPI2->DR) = signal;
	while (SPI2->SR & SPI_SR_BSY){};
	while (!(SPI2->SR & SPI_SR_RXNE)){}; 
	temp=*((__IO uint8_t *)&SPI2->DR);	
   SX1278_hw_SetNSS(1);
   return temp;			
 }


uint8_t SPI_ReadSignal(uint8_t cmd){
	SX1278_hw_SetNSS(0);
	uint8_t temp;
	while (GPIOA->IDR & MISO_HIGH()){};							
	while (!(SPI2->SR & SPI_SR_TXE)){}; 
	*((__IO uint8_t *)&SPI2->DR) = (cmd | 0x80);
	while (SPI2->SR & SPI_SR_BSY){};
	while (!(SPI2->SR & SPI_SR_RXNE)){}; 
	cmd = *((__IO uint8_t *)&SPI2->DR);
	while (!(SPI2->SR & SPI_SR_TXE)){};	 
	*((__IO uint8_t *)&SPI2->DR) = 0x00;
	while (SPI2->SR & SPI_SR_BSY){};
	while (!(SPI2->SR & SPI_SR_RXNE)){};
	temp = *((__IO uint8_t *)&SPI2->DR);
	SX1278_hw_SetNSS(1);
	return temp;	
}

/************************ (C) BORISOV RUSLAN *****END OF FILE****/


