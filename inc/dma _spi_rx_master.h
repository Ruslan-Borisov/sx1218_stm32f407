/**
  ******************************************************************************
  * @file    dma _spi_rx_slave.h
  * @brief   This file contains all the function prototypes for
  *          the dma.c file
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */

#ifndef __DMA_SPI_MASTER_H__
#define __DMA_SPI_MASTER_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"


extern char SPI1_buff_RX[SIZE_BUFF_SPI1_RX];


/**
  * @brief  Initializes the DMA2 Stream 0
	* @details Working together with ADC1,
	* DMA operates in double buffer mode
  * @param  None
  * @retval None
  */
void DMA2_Stream0_SPI_RX_Init(void);


#ifdef __cplusplus
}
#endif

#endif /* __DMA_SPI_MASTER_H__ */

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
