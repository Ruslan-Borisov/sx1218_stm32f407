/**
  ******************************************************************************
  * @file    dma _spi_rx_slave.c
  * @brief   This file provides code for the configuration
  *          of all the requested memory to memory DMA transfers.
  ******************************************************************************
	 * @attention
   * DMA configuration for STM32F407
  ******************************************************************************
 */


#include "dma _spi_rx_slave.h"

void DMA1_Stream3_SPI_RX_Init(void)
{
	      /*1. Enable DMA2 clock*/
        RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	
	      /*1. Bits 27:25 CHSEL[2:0]: Channel selection  */
        DMA1_Stream3->CR &=~ ((1<<25)|(1<<26)|(1<<27));  /*!<000: channel 0 selected - SPI2_RX > */
	     
      	/*2. Bits 31:0 PAR[31:0]: Peripheral address */
        DMA1_Stream3->PAR = (uint32_t)&SPI2->DR;    /*!< > */
	
	      /*3. Bits 31:0 M0A[31:0]: Memory 0 address */
        DMA1_Stream3->M0AR = (uint32_t)&SPI2_buff;  /*!< > */
	
	      /*3. Bits 31:0 M1A[31:0]: Memory 1 address (used in case of Double buffer mode)*/
        //DMA1_Stream2->M1AR = (uint32_t)DMA_ADC_Buff_2;  /*!< > */
	
	      /*4. Bits 15:0 NDT[15:0]: Number of data items to transfer */
        DMA1_Stream3->NDTR = SIZE_BUFF_SPI2_RX;  /*!< > */ 
	
	      /*3. Bit 18 DBM: Double buffer mode*/
         DMA1_Stream3->CR &= ~(1<<18);  /*!<RESET> */
		      
	      /*5. Bit 10 MINC: Memory increment mode */
        DMA1_Stream3->CR|= (1<<10); /*!<Memory address pointer is incremented after each data transfer> */ 

	      /*6. Bit 9 PINC: Peripheral increment mode */
	      DMA1_Stream3->CR &=~ (1<<9); /*!<Peripheral address pointer is fixed> */ 
      
  			/*7. Bits 14:13 MSIZE[1:0]: Memory data size */
        DMA1_Stream3->CR &= ~((1<<13)|(1<<14));  /*!<00: byte (8-bit)> */ 
				
				/*8. Bits 12:11 PSIZE[1:0]: Peripheral data size */
        DMA1_Stream3->CR &= ~((1<<11)|(1<<12));  /*!<00: Byte (8-bit)> */ 
				
				
				
				/*9. Bit 8 CIRC: Circular mode */
        DMA1_Stream3->CR|= (1<<8); /*!<Circular mode enabled> */ 
				
				/*10. Bits 7:6 DIR[1:0]: Data transfer direction */
        DMA1_Stream3->CR &=~ (1<<6)|(1<<7); /*!<Peripheral-to-memory> */ 
				
				/*11. Bits 17:16 PL[1:0]: Priority level*/
        DMA1_Stream3->CR|= (1<<17); /*!<High> */ 
				
				/*12. Bit 4 TCIE: Transfer complete interrupt enable*/
        DMA1_Stream3->CR|= (1<<4); /*!<TC interrupt enabled> */ 
				
				/*12. 	Bit 0 EN: Stream enable / flag stream ready when read low*/
        DMA1_Stream3->CR|= (1<<0); /*!<Stream enabled> */ 
				
				NVIC_EnableIRQ(DMA1_Stream3_IRQn);
        NVIC_SetPriority(DMA1_Stream3_IRQn,1);
}

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
