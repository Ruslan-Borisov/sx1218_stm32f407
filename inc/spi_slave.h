/**
  ******************************************************************************
  * @file    spi_slave.h
  * @brief   This file contains all the function prototypes for
  *          the spi_slave.c file
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */

#ifndef __SPI_SLAVE_H__
#define __SPI_SLAVE_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"

void spi_slave_init(void);
void gpio_spi_slave_init(void);
extern void DMA1_Stream3_SPI_RX_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __SPI_SLAVE_H__ */

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
