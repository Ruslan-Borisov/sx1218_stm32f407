/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"
	
#define READ_PIN_SLAVE()   (GPIOD->IDR & GPIO_IDR_IDR_3)	


#define RST_SET()         (GPIOD->BSRR |=  GPIO_BSRR_BS10)
#define RST_RESET()       (GPIOD->BSRR |=  GPIO_BSRR_BR10)
#define NSS_SET           GPIO_BSRR_BS12
#define NSS_RESET         GPIO_BSRR_BR12  
#define NSS_GPIO_BSRR     GPIOD->BSRR 
#define DIO0_GPIO_ODR     GPIOD->IDR 
#define DIO0_GPIO_STATUS  GPIO_ODR_OD11

void GPIO_Init(void);
void EXTI_Init(void);



#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

/************************ (C) BORISOV RUSLAN  *****END OF FILE****/
