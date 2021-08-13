/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */

#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MISO_HIGH()      (GPIOC->IDR & GPIO_IDR_IDR_2)

#include "main.h"

void spi_master_init(void);
void gpio_spi_master_init(void);


#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
