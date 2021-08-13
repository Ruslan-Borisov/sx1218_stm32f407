/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
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

#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define ARR_FOR_1ms       ((uint16_t)0xA40F)  //41999
#define PCS_FOR_1ms       ((uint16_t)0x0)      // 0
	
#define ARR_FOR_100ms     ((uint16_t)0xEA5F)   //55999
#define PCS_FOR_100ms     ((uint16_t)0x8B)     //139
	
	
	
/**
  * @brief  Initializes the TIM6.
	* @details 
  * @param  None
  * @retval None
  */
void TIM6_Init(void);

void timDelayMs(uint32_t msec); 


#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
