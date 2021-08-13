/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */

#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/**
  * @brief  Initializes the ADC1
	* @details Operation of the ADC on 
	* the trigger from the timer TIM2 
	* by storing values using DMA2
  * @param  None
  * @retval None
  */
void ADC1_Init(void);



#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
