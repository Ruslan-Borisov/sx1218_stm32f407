/**
  ******************************************************************************
  * @file    stm32f4xx_it.h
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
 ******************************************************************************
  */

#ifndef __STM32F4xx_IT_H
#define __STM32F4xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif
#include "main.h"

/**/
extern volatile uint8_t status_DIO_0;
/**/
extern volatile uint8_t irqFlagUSART1_TX;
extern volatile uint8_t irqFlagUSART1_RX;
/**/	 
extern volatile uint8_t irqFlagEXTI_DIO0;	 
/**/
extern volatile uint8_t irqFlagEXTI_DIO1;
/**/
extern volatile uint8_t irqFlagSPI_RX;		 
/**/
void DMA2_Stream0_IRQHandler(void);
/**/	 
void DMA2_Stream2_IRQHandler(void);
/**/
void DMA2_Stream7_IRQHandler(void);
/**/
void EXTI15_10_IRQHandler(void);
/**/



#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_IT_H */

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
