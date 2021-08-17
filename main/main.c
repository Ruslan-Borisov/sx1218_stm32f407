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

void init_struct_MyLoRaSettings(LoRaSettings *MyLoRaSettings)
{
	MyLoRaSettings->frequency = 434000000; // частота в MГц
	MyLoRaSettings->power = 0xFF;                  //20dbm
	MyLoRaSettings->LoRa_SF  = 0x07;               // Коэффициент pаспространения 128 chips / symbol
	MyLoRaSettings->LoRa_BW = 0x07;                // полоса пропускания 0111 125 kHz
	MyLoRaSettings->LoRa_CodingRate = 0x1; // скорость кодирования 001 4/5
	MyLoRaSettings->LoRa_RxPayloadCrcOn = 0x00;   // Включите генерацию CRC и проверьте полезную нагрузку:
	MyLoRaSettings->header_mode = 0x1;             // Неявный режим заголовка
	MyLoRaSettings->ocp_Imax = 100;                // мА, максимольное значение  тока при которой начинается осечка
	MyLoRaSettings->ocp_SET = 100;                 // Включает защиту от перегрузки по току (OCP) для PA:
	//MyLoRaSettings->packetLength;
	uint8_t rxBuffer[SX1278_MAX_PACKET];
	uint8_t txBuffer[SX1278_MAX_PACKET];
	
	uint8_t Irq_DIO_0;
	uint8_t Irq_DIO_1;
	uint8_t Irq_DIO_2;
	uint8_t Irq_DIO_3;
	uint8_t Irq_DIO_4;
	uint8_t Irq_DIO_5;
	
	uint8_t RxTimeoutMask;
	uint8_t RxDoneMask;
	uint8_t PayloadCrcErrorMask;
	uint8_t ValidHeaderMask;
	uint8_t TxDoneMask;
	uint8_t CadDoneMask;
	uint8_t FhssChangeChannelMask;
	uint8_t CadDetectedMask;
	
	uint8_t preambleDetect;
	uint8_t readBytes;

}


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


}
 
}




/************************ (C) BORISOV RUSLAN *****END OF FILE****/
