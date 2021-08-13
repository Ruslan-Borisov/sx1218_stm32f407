/**
  ******************************************************************************
  * @file    dma.h
  * @brief   This file contains all the function prototypes for
  *          the dma.c file
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */

#ifndef __DMA_H__
#define __DMA_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"


extern uint8_t USART1_buff_RX[SIZE_BUFF_USART1_RX];
extern uint8_t USART1_buff_TX[SIZE_BUFF_USART1_TX];


/**
  * @brief  Initializes the DMA2 Stream 0
	* @details Working together with ADC1,
	* DMA operates in double buffer mode
  * @param  None
  * @retval None
  */
void DMA2_Stream2_USART_RX_Init(void);
	
void DMA2_Stream2_USART_TX_Init(void);
	
void dmaSendUSART1(char *buff, int len);


#ifdef __cplusplus
}
#endif

#endif /* __DMA_H__ */

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
