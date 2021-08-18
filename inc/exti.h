/**
  ******************************************************************************
  * @file    exti.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */

#ifndef __EXTI_H__
#define __EXTI_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"
	
	
void EXTI_Init(void);
	
void GPIO_EXTI_Init(void);



#ifdef __cplusplus
}
#endif
#endif /*__ EXTI_H__ */

/************************ (C) BORISOV RUSLAN  *****END OF FILE****/
