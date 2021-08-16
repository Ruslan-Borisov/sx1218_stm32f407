/**
  ******************************************************************************
  * @file    dma_uart.c
  * @brief   This file provides code for the configuration
  *          of all the requested memory to memory DMA transfers.
  ******************************************************************************
	 * @attention
   * DMA configuration for STM32F407
  ******************************************************************************
 */
/************************************************************
*************************************************************/

#include "dma_uart.h"


/************************************************************
*************************************************************/
void DMA2_Stream2_USART_RX_Init(void)
{
	/*1. Enable DMA2 clock*/
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

	/*1. Bits 27:25 CHSEL[2:0]: Channel selection */
	DMA2_Stream2->CR &=~ ((1<<25)|(1<<26)|(1<<27));  /*!< reset > */
	DMA2_Stream2->CR |=(1<<27);  /*!<100: channel 4 selected USART1_RX > */

	/*2. Bits 31:0 PAR[31:0]: Peripheral address */
	DMA2_Stream2->PAR = (uint32_t)&USART1->DR;    /*!< > */

	/*3. Bits 31:0 M0A[31:0]: Memory 0 address */
	DMA2_Stream2->M0AR = (uint32_t)&USART1_buff_RX;  /*!< > */

	/*4. Bits 31:0 M1A[31:0]: Memory 1 address (used in case of Double buffer mode)*/
	//DMA2_Stream2->M1AR = (uint32_t)DMA_ADC_Buff_2;  /*!< > */

	/*5. Bits 15:0 NDT[15:0]: Number of data items to transfer */
	DMA2_Stream2->NDTR = SIZE_BUFF_USART1_RX;  /*!< > */ 

	/*6. Bit 18 DBM: Double buffer mode*/
	DMA2_Stream2->CR &= ~(1<<18);  /*!<RESET> */

	/*7. Bit 10 MINC: Memory increment mode */
	DMA2_Stream2->CR |= (1<<10); /*!<Memory address pointer is incremented after each data transfer> */ 

	/*8. Bit 9 PINC: Peripheral increment mode */
	DMA2_Stream2->CR &=~ (1<<9); /*!<Peripheral address pointer is fixed> */ 

	/*9. Bits 14:13 MSIZE[1:0]: Memory data size */
	DMA2_Stream2->CR &= ~((1<<13)|(1<<14));  /*!<00: byte (8-bit)> */ 

	/*10. Bits 12:11 PSIZE[1:0]: Peripheral data size */
	DMA2_Stream2->CR &= ~((1<<11)|(1<<12));  /*!<00: byte (8-bit)> */ 

	/*11. Bit 8 CIRC: Circular mode */
	DMA2_Stream2->CR|= (1<<8); /*!<Circular mode enabled> */ 

	/*12. Bits 7:6 DIR[1:0]: Data transfer direction */
	DMA2_Stream2->CR &= ~((1<<6)|(1<<7)); /*!<Peripheral-to-memory(reset)> */ 

	/*13. Bits 17:16 PL[1:0]: Priority level*/
	DMA2_Stream2->CR|= (1<<17); /*!<High> */ 

	/*14. Bit 4 TCIE: Transfer complete interrupt enable*/
	DMA2_Stream2->CR|= (1<<4); /*!<TC interrupt enabled> */ 

	/*15. 	Bit 0 EN: Stream enable / flag stream ready when read low*/
	DMA2_Stream2->CR|= (1<<0); /*!<Stream enabled> */ 

	NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	NVIC_SetPriority(DMA2_Stream2_IRQn,1);
}
/************************************************************
*************************************************************/
void DMA2_Stream7_USART_TX_Init(void)
{
	/* Enable DMA2 clock*/
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

	/*1. Bits 27:25 CHSEL[2:0]: Channel selection */
	DMA2_Stream7->CR &=~ ((1<<25)|(1<<26)|(1<<27));  /*!< reset > */
	DMA2_Stream7->CR |=(1<<27);  /*!<100: channel 4 selected USART1_TX > */

	/*2. Bits 31:0 PAR[31:0]: Peripheral address */
	DMA2_Stream7->PAR = (uint32_t)&USART1->DR;    /*!< > */

	/*3. Bits 31:0 M0A[31:0]: Memory 0 address */
	DMA2_Stream7->M0AR = (uint32_t)&USART1_buff_TX;  /*!< > */

	/*4. Bits 31:0 M1A[31:0]: Memory 1 address (used in case of Double buffer mode)*/
	//DMA2_Stream2->M1AR = (uint32_t)DMA_ADC_Buff_2;  /*!< > */

	/*5. Bits 15:0 NDT[15:0]: Number of data items to transfer */
	DMA2_Stream7->NDTR = SIZE_BUFF_USART1_TX;  /*!< > */ 

	/*6. Bit 18 DBM: Double buffer mode*/
	DMA2_Stream7->CR &= ~(1<<18);  /*!<RESET> */

	/*7. Bit 10 MINC: Memory increment mode */
	DMA2_Stream7->CR |= (1<<10); /*!<Memory address pointer is incremented after each data transfer> */ 

	/*8. Bit 9 PINC: Peripheral increment mode */
	DMA2_Stream7->CR &=~ (1<<9); /*!<Peripheral address pointer is fixed> */ 

	/*9. Bits 14:13 MSIZE[1:0]: Memory data size */
	DMA2_Stream7->CR &= ~((1<<13)|(1<<14));  /*!<00: byte (8-bit)> */ 

	/*10. Bits 12:11 PSIZE[1:0]: Peripheral data size */
	DMA2_Stream7->CR &= ~((1<<11)|(1<<12));  /*!<00: byte (8-bit)> */ 

	/*11. Bit 8 CIRC: Circular mode */
	DMA2_Stream7->CR &= ~(1<<8); /*!<Circular mode disabled> */ 

	/*12. Bits 7:6 DIR[1:0]: Data transfer direction */
	DMA2_Stream7->CR &=~ ((1<<6)|(1<<7)); /*!<reset> */ 
	DMA2_Stream7->CR |= (1<<6); /*!<01: Memory-to-peripheral> */ 

	/*13. Bits 17:16 PL[1:0]: Priority level*/
	DMA2_Stream7->CR|= (1<<17); /*!<High> */ 

	/*14. Bit 4 TCIE: Transfer complete interrupt enable*/
	DMA2_Stream7->CR|= (1<<4); /*!<TC interrupt enabled> */ 

	/*15. 	Bit 0 EN: Stream enable / flag stream ready when read low*/
	DMA2_Stream7->CR &=~ (1<<0); /*!<Stream disabled> */ 

	NVIC_EnableIRQ(DMA2_Stream7_IRQn);
	NVIC_SetPriority(DMA2_Stream7_IRQn,1);
}
/************************************************************
*************************************************************/
void dmaSendUSART1(char text[], uint8_t data)
{
	static uint8_t len;
	len = sizeof(&text);
	static char buff[256];
	for(int i=0; i<len; i++)
   {
	   buff[i] = text[i]; 
	}
	
   buff[len] = ' ';	
	buff[len+1] = '=';
	buff[len+2] = ' ';	
	buff[len+3] = (char)data;
	//buff[len+4] = {"\n"};
	
	//DMA2_Stream7->CR &=~ (1<<0); /*!<Stream disabled> */
   DMA2_Stream7->M0AR = (uint32_t)&buff; /*!< > */
	DMA2_Stream7->NDTR = len+4; 
	DMA2_Stream7->CR |=  (1<<0); /*!<enabled> */
}
/************************************************************
*************************************************************/

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
