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
#include "usart.h"
#include "dma_uart.h"
#include "stm32f4xx_it.h"
#include "rcc.h"
#include "spi.h"
#include "gpio.h"
#include "tim.h"
#include "SX1278_hw.h"
#include "SX1278.h"
#include "dma _spi.h"
#include "exti.h"
#include "i2c_oled.h"
#include "ic1306.h"


//#define _SLAVE	

#define _MASTER

 char tx[] = {"msg_tx"};
 char rx[] = {"msg_rx"};

SX1278_t SX1278;

/**/


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
volatile uint8_t irqFlagEXTI_DIO1;
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
uint8_t test_loraset;
/**/
uint8_t testcounter;	
/**/

/**/
char text_RX[] = "DATA_INPUT";
/**/
uint8_t bufTX[3] = {0x1, 0x2, 0x3};
uint8_t bufRX[3];

uint16_t gg;

int main(void)
{
 
		RCC_Init();
		UART1_Init();
		
		GPIO_Init();
		EXTI_Init();
		TIM6_Init();
	   
	   i2c_oled_init();
	   ssd1306_init();
		LCD_Clear();
		LCD_Goto(0,0);
   
		LORA_ADD_SET();
		timDelayMs(100);
		SX1278_hw_init();
		spi_master_init();	
		timDelayMs(1000);
	
      SX1278_init(&SX1278, 433000000, 100, SX1278_LORA_SF_7, SX1278_LORA_BW_125KHZ,
						SX1278_LORA_CR_4_6, SX1278_LORA_CRC_DIS, 3);
	
		 
	
	
#ifdef _SLAVE
	 OLED_string("SLAVE");
	 SX1278_receive(&SX1278, 3, 10000);
#endif

#ifdef _MASTER
	  OLED_string("MASTER");
	  SX1278_transmit(&SX1278, bufTX, 3,  2000);	
#endif

	 while (1)
 {
	 
#ifdef _SLAVE   
/*******************************************************/ 	 
	    if(irqFlagEXTI_DIO0 == 1){
		 test_loraset++;
		 LCD_Goto(0,1);
		 OLED_string("Lora RECEIVE = ");
		 OLED_num_to_str(test_loraset, 5);
		 LCD_Goto(0,2);
	    irqFlagEXTI_DIO0=0;
		 bufRX[0] = SX1278.rxBuffer[0];
		 OLED_string(" ");
		 OLED_num_to_str( bufRX[0] , 5);
		 bufRX[1] = SX1278.rxBuffer[1];
		 OLED_string(" ");
		 OLED_num_to_str( bufRX[1] , 5);
		 bufRX[2] = SX1278.rxBuffer[2];
		 OLED_string(" ");
		 OLED_num_to_str( bufRX[2] , 5);
		 
		 LCD_Goto(0,3);
	    OLED_string("RSSI_LoRa= "); 
		 OLED_num_to_str(SX1278_RSSI_LoRa(), 5);
			
       LCD_Goto(0,4);
	    OLED_string("RSSI= "); 
		 OLED_num_to_str(SX1278_RSSI(), 5);			 
			 
		 irqFlagEXTI_DIO0=0;
		 SX1278_receive(&SX1278, 3, 10000);
	 }

	  
/*******************************************************/	 
#endif
	 
/*******************************************************/
	 
#ifdef _MASTER   
/*******************************************************/ 	 
	 if(irqFlagEXTI_DIO0 == 1){
		 test_loraset++;
		 LCD_Goto(0,1);
		 OLED_string("Lora RECEIVE = ");
		 OLED_num_to_str(test_loraset, 5);
		
		 
	
		 timDelayMs(1000);
		 
		  irqFlagEXTI_DIO0=0;
		 SX1278_transmit(&SX1278, bufTX, 3,  2000);	

	 }
	    testcounter++;
	    LCD_Goto(0,3);
		 OLED_num_to_str(testcounter, 5);
/*******************************************************/	 
#endif
	 
/*******************************************************/
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
			if(rw_test==2)
				{
					
				
				SX1278_WriteBurst( cmd_test,bufRX, 3);
					 
				}
			if(rw_test==3)
				{
					SX1278_ReadBurst(cmd_test,bufRX, 3);
					 
				}
		  irqFlagUSART1_RX = 0;	
		}
/*******************************************************/

  }
}







/************************ (C) BORISOV RUSLAN *****END OF FILE****/
