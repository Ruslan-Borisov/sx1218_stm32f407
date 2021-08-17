
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */


#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"
/* */
#define SIZE_BUFF_SPI1_RX     3
extern char SPI1_buff_RX[SIZE_BUFF_SPI1_RX];
/* */	
#define SIZE_BUFF_USART1_RX   3
#define SIZE_BUFF_USART1_TX   3
/* */	
extern uint8_t USART1_buff_RX[SIZE_BUFF_USART1_RX];
extern char USART1_buff_TX[SIZE_BUFF_USART1_TX];
/* */
extern volatile uint8_t irqFlagUSART1_TX;
extern volatile uint8_t irqFlagUSART1_RX;
/**/
extern volatile uint8_t irqFlagEXTI_DIO0;
/**/
extern volatile uint8_t irqFlagSPI_RX;
/**/
extern uint8_t sizeLen;	
/**/
/**/
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
