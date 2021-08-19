/**
  ******************************************************************************
  * @file    dma_uart.h
  * @brief   This file contains all the function prototypes for
  *          the dma_uart.c file
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */

#ifndef __DMA_UART_H__
#define __DMA_UART_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"


extern uint8_t USART1_buff_RX[SIZE_BUFF_USART1_RX];
extern char USART1_buff_TX[SIZE_BUFF_USART1_TX];


/**
  * @brief  Initializes the DMA2 Stream 0
	* @details Working together with ADC1,
	* DMA operates in double buffer mode
  * @param  None
  * @retval None
  */
void DMA2_Stream2_USART_RX_Init(void);
	
void DMA2_Stream2_USART_TX_Init(void);
	
void dmaSendUSART1(char *data);

extern uint8_t sizeLen;	

#ifdef __cplusplus
}
#endif

#endif /* __DMA_UART_H__ */

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
