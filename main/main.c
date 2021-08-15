/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */

#include <stdint.h>
#include "main.h"
#include "dma_uart.h"
#include "usart.h"
#include "stm32f4xx_it.h"
#include "rcc.h"
#include "spi.h"
#include "gpio.h"
#include "tim.h"
#include "SX1278_hw.h"
#include "SX1278.h"
#include "dma _spi.h"


#define _SLEVE


/**/
uint8_t USART1_buff_RX[SIZE_BUFF_USART1_RX];
char USART1_buff_TX[SIZE_BUFF_USART1_TX];
/**/
char SPI1_buff_RX[SIZE_BUFF_SPI1_RX]; 
/**/
volatile uint8_t irqFlagUSART1_TX;
volatile uint8_t irqFlagUSART1_RX;
/**/
volatile uint8_t irqFlagSPI_RX;
/**/
volatile uint8_t irqFlagEXTI_DIO0;
/**/

int main(void)
{
 
	RCC_Init();
  UART1_Init();
	GPIO_Init();
	EXTI_Init();
  TIM6_Init();
  spi_master_init();	

	 while (1)
{
	if(irqFlagUSART1_RX ==1)
  {
	 irqFlagUSART1_RX = 0;
	}

   
	
}
 
}
	


/************************ (C) BORISOV RUSLAN *****END OF FILE****/
