/**
  ******************************************************************************
  * @file    SX1278_hw.c
  * @brief   
  ******************************************************************************
	 * @attention
  ******************************************************************************
 */

/************************************************************
*************************************************************/

#include "tim.h"
#include "SX1278_hw.h"
#include "spi.h"

#include "gpio.h"


/************************************************************
*************************************************************/

void SX1278_hw_init() 
{
	SX1278_hw_SetNSS(1);
	RST_SET();
}
/************************************************************
*************************************************************/

void SX1278_hw_SetNSS(int value)
{
	NSS_GPIO_BSRR  |= ((value == 1) ? NSS_SET: NSS_RESET);
}

/************************************************************
*************************************************************/

void SX1278_hw_Reset() 
{
	SX1278_hw_SetNSS(1);
	RST_RESET();
	timDelayMs(1);
	RST_SET();
	timDelayMs(100);
}

/************************************************************
*************************************************************/

int SX1278_hw_GetDIO0()
{
	return (DIO0_GPIO_ODR & DIO0_GPIO_STATUS)==SET ? 1:0;
}

/************************************************************
*************************************************************/

void SX1278_timDelayMs(uint32_t msec)
{
	timDelayMs(msec);
}

/************************************************************
*************************************************************/

uint8_t SX1278_WriteSingle(uint8_t command, uint8_t value) 													
{
	uint8_t temp;
	SX1278_hw_SetNSS(0);
	//while (GPIOA->IDR & MISO){};							
	while (!(SPI1->SR & SPI_SR_TXE)){};  
	SPI1_DR_8bit = (WRITE_SINGLE | command);
	while (SPI1->SR & SPI_SR_BSY){};
	while (!(SPI1->SR & SPI_SR_RXNE)){}; 
	temp=SPI1_DR_8bit;
	while (!(SPI1->SR & SPI_SR_TXE)){};	 
	SPI1_DR_8bit = value;
	while (SPI1->SR & SPI_SR_BSY){};
	while (!(SPI1->SR & SPI_SR_RXNE)){}; 
	temp=SPI1_DR_8bit;	
	SX1278_hw_SetNSS(1);
	return temp;	
}

/************************************************************
*************************************************************/

uint8_t SX1278_ReadSingle(uint8_t command)
{
	uint8_t temp;
	SX1278_hw_SetNSS(0);
	//while (GPIOA->IDR & MISO){};							
	while (!(SPI1->SR & SPI_SR_TXE)){}; 
	SPI1_DR_8bit = (command | READ_SINGLE);
	while (SPI1->SR & SPI_SR_BSY){};
	while (!(SPI1->SR & SPI_SR_RXNE)){}; 
	command = SPI1_DR_8bit;
	while (!(SPI1->SR & SPI_SR_TXE)){};	 
	SPI1_DR_8bit = 0x00;
	while (SPI1->SR & SPI_SR_BSY){};
	while (!(SPI1->SR & SPI_SR_RXNE)){};
	temp = SPI1_DR_8bit;
	SX1278_hw_SetNSS(1);
	return temp;	
}

/************************************************************
*************************************************************/

void SX1278_WriteBurst( uint8_t addr,char *buff, uint8_t size)
{
  uint8_t j_;
	SX1278_hw_SetNSS(0);
	//while (GPIOA->IDR & MISO){};							
	while (!(SPI1->SR & SPI_SR_TXE)){};	
	SPI1_DR_8bit = (addr | WRITE_SINGLE);
	while (SPI1->SR & SPI_SR_BSY){};		
	while (!(SPI1->SR & SPI_SR_RXNE)){}; 
	SPI1_DR_8bit;	
	for(j_ = 0; j_ < size; j_ ++ )
		{
			while (!(SPI1->SR & SPI_SR_TXE)){};	
			SPI1_DR_8bit = buff[j_]; 
			while (SPI1->SR & SPI_SR_BSY){};
			while (!(SPI1->SR & SPI_SR_RXNE)){};
			SPI1_DR_8bit;	
		}
	SX1278_hw_SetNSS(1);
}

/************************************************************
*************************************************************/
//void SX1278_WriteBurst( uint8_t addr,char *buff, uint8_t size)
//{  
//	uint8_t temp;
//	for(int i=0; i<size; i++){
//	SX1278_hw_SetNSS(0);
//	//while (GPIOA->IDR & MISO){};							
//	while (!(SPI1->SR & SPI_SR_TXE)){};  
//	SPI1_DR_8bit = (WRITE_SINGLE | (addr+i));
//	while (SPI1->SR & SPI_SR_BSY){};
//	while (!(SPI1->SR & SPI_SR_RXNE)){}; 
//	temp=SPI1_DR_8bit;
//	while (!(SPI1->SR & SPI_SR_TXE)){};	 
//	SPI1_DR_8bit = buff[i];
//	while (SPI1->SR & SPI_SR_BSY){};
//	while (!(SPI1->SR & SPI_SR_RXNE)){}; 
//	temp=SPI1_DR_8bit;	
//	SX1278_hw_SetNSS(1);
//	timDelayMs(1);
//	}
//}

/************************************************************
*************************************************************/
void SX1278_ReadBurst( uint8_t cmd, char *buff, uint8_t size)
{
	uint8_t j_;
	SX1278_hw_SetNSS(0);
	//while (GPIOA->IDR & MISO){};							
	while (!(SPI1->SR & SPI_SR_TXE)){};	SPI1_DR_8bit = (cmd | READ_SINGLE);
	while (SPI1->SR & SPI_SR_BSY){};
	while (!(SPI1->SR & SPI_SR_RXNE)){}; SPI1_DR_8bit;	
	for( j_ = 0; j_ < size; j_ ++ )
		{
			while (!(SPI1->SR & SPI_SR_TXE)){};	SPI1_DR_8bit = 0x00; 
			while (SPI1->SR & SPI_SR_BSY){};
			while (!(SPI1->SR & SPI_SR_RXNE)){}; buff[j_] = SPI1_DR_8bit;		
		}
	SX1278_hw_SetNSS(1);
}

/************************************************************
*************************************************************/
void SX1278_Correct( uint8_t cmd, uint8_t signal)
{
   uint8_t currentSignal = 0;
	uint8_t correctedSignal = 0;
	currentSignal = SX1278_ReadSingle(cmd);
	correctedSignal = currentSignal|signal;
}

/************************************************************
*************************************************************/


/************************ (C) BORISOV RUSLAN *****END OF FILE****/


