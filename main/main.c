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





 char tx[] = {"msg_tx"};
 char rx[] = {"msg_rx"};






void Lora_transmit(char *buff, uint8_t len);

void Lora_receive(char *buff, uint8_t len);
/**/
void init_LoRaSettings(LoRaSettings *settings);

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
LoRaSettings settings;
/**/
char text_RX[] = "DATA_INPUT";
/**/
char bufTX[5] = {"ST"};
char bufRX[5];

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
	
	 
	 init_LoRaSettings(&settings);
	 SX1278_config(&settings);
    SX1278_clearLoRaIrq();
    irqFlagEXTI_DIO0=0;
//	
////----------------ПРИЕМНИК-------------------
////#ifdef RX    
//	 SX1278_LoRaEntryRx(&settings, 3, 3000);  // ПРИЕМНИК 
////#endif	 
////----------------ПРИЕМНИК-------------------	 

 //++++++++++++++++ ПЕРЕДАТЧИК+++++++++++++++++	  
//#ifdef TX 
    SX1278_transmit(&settings,bufTX, 5, 1000); // ПЕРЕДАТЧИК
//#endif
//++++++++++++++++ ПЕРЕДАТЧИК+++++++++++++++++		


	 while (1)
 {
    
////----------------ПРИЕМНИК-------------------
////#ifdef RX 
//	 if(irqFlagEXTI_DIO0 == 1){
//		
//		 SX1278_standby(&settings);
//		 irqFlagEXTI_DIO0=2;
//		 SX1278_LoRaRxPacket(&settings);  
//       SX1278_LoRaEntryRx(&settings, 3, 3000);
//	 }
////#endif
////----------------ПРИЕМНИК-------------------
	 
	 
//++++++++++++++++ ПЕРЕДАТЧИК+++++++++++++++++	
//#ifdef TX 	 
         timDelayMs(4000);
	     
	      if(irqFlagEXTI_DIO0 == 1){
		   bufTX[4] = (char)testcounter;
			SX1278_clearLoRaIrq();
			irqFlagEXTI_DIO0=0;
         SX1278_transmit(&settings,bufTX, 5, 1000);
		}
//#endif
//+++++++++++++++++ПЕРЕДАТЧИК++++++++++++++++++
	 
 
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
					
				
					 Lora_transmit(bufTX, 3);
					 
				}
			if(rw_test==3)
				{
					Lora_receive(bufRX, 12);
					 
				}
		  irqFlagUSART1_RX = 0;	
		}


  }
}

void Lora_transmit(char *buff, uint8_t len)
{
  SX1278_WriteBurst(LR_RegFifo, buff, len);

}

void Lora_receive(char *buff, uint8_t len)
{
  //SX1278_WriteSingle(0x0D, 0); 
  SX1278_ReadBurst(LR_RegFifo, buff, len);

}




void init_LoRaSettings(LoRaSettings *settings){
	
	/*RegFrMsb(0x06), RegFrMid(0x07), RegFrLsb(0x08)*/
	settings->frequency = 434;           /*Частота задается в МГц*/
	
   /*RegPaConfig(0x09)*/
	settings->PaSelect_09    = 0x00;         /*Выбирает выходной вывод PA - Пин-код RFO. Выходная мощность ограничена +14 дБм.
                                               1 - PIN-код PA_BOOST. Выходная мощность ограничена +20 дБм*/
	
	settings->MaxPower_09    = 0x04;     /*Выберите максимальную выходную мощность: 
	                                            Pmax=10,8+0,6*Максимальная мощность [дБм]*/
	
	settings->OutputPower_09 = 0x0f;     /*Мощность на выходе*/
	
	/* RegModemConfig2(0x1E)*/
	settings->LoRa_SF_1E = 0x07;        /*Коэффициент распространения(помехозащищенность линии
														   чем выше значение тем более защищена линия но скорость ниже)*/
	
	settings->TxContinuousMode_1E = 0 ; /*0 - нормальный режим, отправляется один пакет
                                              1 - непрерывный режим, отправка нескольких пакетов через FIFO
                                             (используется для спектрального анализа)*/
	
	settings->LoRa_RxPayloadCrcOn_1E = 0 ; /*Включение генерации CRC и проверка полезной нагрузки:
                                                 0 - Отключение CRC, 1 - Включить CRC
                                                 Если требуется CRC, следует установить RxPayloadCrcOn:
                                                - в режиме неявного заголовка: на стороне Tx и Rx
                                                - в явном режиме заголовка: только на стороне Tx (восстановлено из
                                                 заголовка на стороне Rx)*/
	
	/*RegModemConfig1(0x1D)*/
	settings->LoRa_BW_1D = 0x07;             /*Полоса пропускания сигнала*/
	
	settings->LoRa_CodingRate_1D = 0x01;      /*Скорость кодирования ошибок в полосе пропускания сигнала*/
	
	settings->ImplicitHeaderModeOn_1D = 0x00;             // 1 - не явный ти заголовка 0 - явный заголовок
	
	/*RegOcp (0x0B)*/
	settings->LoRa_ocp_Imax_0B = 100;          /*мА, максимальное значение тока перегрузки*/
	settings->LoRa_ocp_SET_0B = 1;           /*Включает защиту от перегрузки по току (OCP) для PA:
                                                   0 - OCP отключен 1 - OCP включен*/
	/*RegSyncWord(0x39)*/
	settings->LoRa_SyncWord_39 = 0x20;          /*Слово синхронизации Значение 0x34 зарезервировано для сетей LoRaWAN*/
	
	/*RegLna(0x0C)*/
	settings->LoRa_Lna_Gain_0C = 0x01;           /*Настройка усиления LNA*/
	settings->LoRa_Lna_BoostLf_0C=0;             /*Регулировка тока LNA низкой частоты (RFI_LF) 00 - Ток LNA по умолчанию*/
	settings->LoRa_Lna_BoostHf_0C =0;           /*Высокочастотная (RFI_HF) регулировка тока LNA 00 - Ток LNA по умолчанию
                                                      11 - Увеличение, ток 150% LNA*/
	
	/*RegModemConfig3(0x26)*/
	settings->LoRa_LDRateOptimize_26 = 1;      /*Оптимизация ризкой скорости передачи данных 0 -Отключено
                                                     1 - Включено; требуется, если длина символа превышает 16 м*/
	settings->LoRa_AgcAutoOn_26 = 0;           /*0 - Коэффициент усиления LNA, установленный регистром LnaGain
                                                      1 - Коэффициент усиления LNA, установленный внутренним контуром AGC*/
																		
	/*RegPreambleMsb(0x20)*/
	settings->PreambleMsb_20 = 0;              /*Длина преамбулы MSB*/
	/*RegPreambleLsb(0x21)*/
	settings->PreamblelSB_21 = 0x08;             /*Длина преамбулы LSB */
	
	/*RegDioMapping2(0x41)*/
	settings->PreambleDetect_41 = 0;          /*Позволяет сопоставлять Rssi или предварительный набор с выводами DIO
,                                                   как показано в таблице 29 и таблице 30
                                                     0 - Прерывание Rssi
                                                    1 - Прерывание предварительного обнаружения*/
																	 
	settings->Dio_4_0Map_41 = 0;               /*00 - CadDetected, 01 - PllLock, 10 - PllLock */
	settings->Dio_5_0Map_41 = 0;               /*00 - ModeReady, 01 - ClkOut, 10 - ClkOut */
	
	/*RegDioMapping1(0x40)*/
	settings->Dio_0_0Map_40 = 0;                /*00 - RxDone, 01 - TxDone, 10 - CadDone */
	settings-> Dio_1_0Map_40 = 0;               /*00 - RxTimeout, 01 - FhssChangeChannel, 10 - CadDetected */
	settings-> Dio_2_0Map_40 = 0;
	settings-> Dio_3_0Map_40 = 0;               /*00 - FhssChangeChannel, 01 - FhssChangeChannel, 10 - FhssChangeChannel */


////----------------ПРИЕМНИК-------------------	
////#ifdef RX 	
//	settings->RxTimeoutMask_11 = 1;
//   settings->RxDoneMask_11 = 0;
//   settings->PayloadCrcErrorMask_11 = 1;
//   settings->ValidHeaderMask_11 = 1;
//   settings-> TxDoneMask_11 = 1;
//   settings->CadDoneMask_11=1;
//   settings->FhssChangeChannelMask_11 = 1;
//   settings->CadDetectedMask_11 = 1;
//#endif	
//----------------ПРИЕМНИК-------------------
	
//++++++++++++++++ ПЕРЕДАТЧИК+++++++++++++++++		 
//#ifdef TX  
	settings->RxTimeoutMask_11 = 1;
   settings->RxDoneMask_11 = 1;
   settings->PayloadCrcErrorMask_11 = 1;
   settings->ValidHeaderMask_11 = 1;
   settings-> TxDoneMask_11 = 0;
   settings->CadDoneMask_11=1;
   settings->FhssChangeChannelMask_11 = 1;
   settings->CadDetectedMask_11 = 1;
//#endif	
//+++++++++++++++++ПЕРЕДАТЧИК++++++++++++++++++

	/*RegIrqFlagsMask (0x11)*/	
  
	settings->LoRa_header_mode = 0;
	
	settings->LoRa_packetLength = 5;  //длина пакета
	
	settings->preambleDetect_1F = 0;
	
	settings->readBytes = 0;

} 
	



/************************ (C) BORISOV RUSLAN *****END OF FILE****/
