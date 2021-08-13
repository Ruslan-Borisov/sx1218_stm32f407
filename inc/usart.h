/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
 
  ******************************************************************************
  */

#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/**
  * @brief  Initializes the USART1 and GPIO RX(PA10), TX(PA9).
  * @param  None
  * @retval None
  */
void UART1_Init(void);
extern void DMA2_Stream2_USART_RX_Init(void);
	
#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) BORISOV RUSLAN  *****END OF FILE****/
