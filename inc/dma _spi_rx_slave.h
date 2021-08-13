/**
  ******************************************************************************
  * @file    dma _spi_rx_slave.h
  * @brief   This file contains all the function prototypes for
  *          the dma.c file
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */

#ifndef __DMA_SPI_SLAVE_H__
#define __DMA_SPI_SLAVE_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"


extern char SPI2_buff[SIZE_BUFF_SPI2_RX];


/**
  * @brief  Initializes the DMA2 Stream 3
	* @details Working together with SPI2
  * @param  None
  * @retval None
  */
extern void DMA1_Stream3_SPI_RX_Init(void);


#ifdef __cplusplus
}
#endif

#endif /* __DMA_SPI_SLAVE_H__ */

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
