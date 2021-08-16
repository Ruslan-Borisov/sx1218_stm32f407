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
#include "main.h"
#include "gpio.h"

#define SPI_STATE_READY  (1<<15)

/************************************************************
*************************************************************/
 void SX1278_hw_init() {
	SX1278_hw_SetNSS(1);
	RST_SET();
}
/************************************************************
*************************************************************/
 void SX1278_hw_SetNSS(int value) {
	NSS_GPIO_BSRR  |= ((value == 1) ? NSS_SET: NSS_RESET);
}
/************************************************************
*************************************************************/
 void SX1278_hw_Reset() {
	SX1278_hw_SetNSS(1);
	RST_RESET();
	timDelayMs(1);
	RST_SET();
	timDelayMs(100);
}
/************************************************************
*************************************************************/
int SX1278_hw_GetDIO0() {
	return (DIO0_GPIO_ODR & DIO0_GPIO_STATUS)==SET ? 1:0;
}
/************************************************************
*************************************************************/
void SX1278_hw_ReadBurst_SPI( uint8_t cmd, char *buff, uint8_t size ){
	
	
	uint8_t i;
	SX1278_hw_SetNSS(0);
	//while (MISO_HIGH()){};
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
/************************************************************
*************************************************************/
void SX1278_hw_WriteBurst_SPI( uint8_t addr, char *buff, uint8_t size ){
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
/************************************************************
*************************************************************/
uint8_t SX1278_hw_WriteSingle_SPI(uint8_t cmd, uint8_t signal){
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
/************************************************************
*************************************************************/
uint8_t SPI_ReadSignal_SPI(uint8_t cmd){
	uint8_t temp;
	   SX1278_hw_SetNSS(0);
	   while(!(SPI1->SR & SPI_SR_TXE)){}
      *((__IO uint8_t *)&SPI1->DR) = cmd;
      while (!(SPI1->SR & SPI_SR_RXNE)){}
      while ( SPI1->SR & SPI_SR_BSY )
      {
            (void)SPI1->DR;
      }
     while(!(SPI1->SR & SPI_SR_TXE)){}
     *((__IO uint8_t *)&SPI1->DR) = 0xFF;
     while (!(SPI1->SR & SPI_SR_RXNE)){}
     temp = (uint8_t)SPI1->DR;
 
     SX1278_hw_SetNSS(1);		
}


void SX1278_hw_comand_SPI(uint8_t rw, uint8_t adr, uint8_t cmd)
{
	SX1278_hw_SetNSS(0);
	
	   cmd = (rw==0)? cmd: (cmd|0x80);
	   while(!(SPI1->SR & SPI_SR_TXE)){}
      *((__IO uint8_t *)&SPI1->DR) = adr;
     // while (!(SPI1->SR & SPI_SR_RXNE)){}
      while ( SPI1->SR & SPI_SR_BSY )
      {
            (void)SPI1->DR;
      }
     while(!(SPI1->SR & SPI_SR_TXE)){}
     *((__IO uint8_t *)&SPI1->DR) = cmd;
	
	   while ( SPI1->SR & SPI_SR_BSY )
      {
            (void)SPI1->DR;
      }
     SX1278_hw_SetNSS(1);	
 






}
/************************************************************
*************************************************************/






/************************ (C) BORISOV RUSLAN *****END OF FILE****/


