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
#include "exti.h"

//#define _SLEVE


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
uint8_t rw_test;
uint8_t cmd_test;
uint8_t vale_test;
/**/
uint8_t set_test[256];
/**/
int signal_lora_test;
/**/
uint8_t sizeLen;	
/**/
/**/
uint8_t testcounter;	
/**/

int main(void)
{
 
	RCC_Init();
   UART1_Init();
	GPIO_Init();
	EXTI_Init();
   TIM6_Init();
	
   LORA_ADD_SET();
	timDelayMs(100);
	
	SX1278_hw_init();
	
   spi_master_init();	
   timDelayMs(1000);
	
	
	 while (1)
{

	if(irqFlagUSART1_RX==1)
  {
	  
	  rw_test = USART1_buff_RX[0];
	  cmd_test = USART1_buff_RX[1];
	  vale_test = USART1_buff_RX[2];
	  if(rw_test==0)
     {
		//  signal_lora_test = SX1278_LoRaTxPacket(MyLoRaSettings, USART1_buff_RX, 3, 90000000000);
	    signal_lora_test = SX1278_ReadSingle(cmd_test); 
	  }
		 if(rw_test==1)
     {
	      SX1278_WriteSingle(cmd_test, vale_test); 
	  }
	 irqFlagUSART1_RX = 0;
	}

}
 
}
	



/************************ (C) BORISOV RUSLAN *****END OF FILE****/
