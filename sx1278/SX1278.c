/**
  ******************************************************************************
  * @file    SX1278.c
  * @brief   
  ******************************************************************************
	 * @attention
  ******************************************************************************
 */

/************************************************************
*************************************************************/

#include "SX1278.h"
#include "SX1278_hw.h"	


/************************************************************
*************************************************************/
LoRaSettings MyLoRaSettings;
/************************************************************
*************************************************************/
void SX1278_config(LoRaSettings *MyLoRaSettings){
   SX1278_sleep(MyLoRaSettings); //установить режим SLEEP
   SX1278_timDelayMs(15); // задержка 15 мс
   SX1278_entryLoRa();  // включаем регистры lora          
  //SX1278_SPIWrite(module, 0x5904); //?? Change digital regulator form 1.6V to 1.47V: see errata note
	// расчет частоты
	uint64_t freq = ((uint64_t) MyLoRaSettings->frequency << 19) / 32000000;
   uint8_t freq_reg[3];
   freq_reg[0] = (uint8_t) (freq >> 16);
   freq_reg[1] = (uint8_t) (freq >> 8);
   freq_reg[2] = (uint8_t) (freq >> 0);
   SX1278_WriteBurst(LR_RegFrMsb,freq_reg, 3); // настройка частоты 
   SX1278_WriteSingle(RegSyncWord, 0x34); // слово инхронизации
	//настройка базовых параметров
   SX1278_WriteSingle(LR_RegPaConfig, SX1278_Power[MyLoRaSettings->power]); //Setting output power parameter
   SX1278_WriteSingle(LR_RegOcp, 0x0B);		//RegOcp,Close Ocp
   SX1278_WriteSingle(LR_RegLna, 0x23);		//RegLNA,High & LNA Enable
   
	if (SX1278_SpreadFactor[MyLoRaSettings->LoRa_SF] == 6) //SFactor=6
		{	
			uint8_t tmp;
         SX1278_WriteSingle(LR_RegModemConfig1,((SX1278_LoRaBandwidth[MyLoRaSettings->LoRa_BW] << 4)
                            + (SX1278_CodingRate[MyLoRaSettings->LoRa_CR] << 1) + 0x01)); //Implicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
         SX1278_WriteSingle(LR_RegModemConfig2,((SX1278_SpreadFactor[MyLoRaSettings->LoRa_SF] << 4)
                            + (SX1278_CRC_Sum[MyLoRaSettings->LoRa_CRC_sum] << 2) + 0x03));
         tmp = SX1278_ReadSingle(0x31);
         tmp &= 0xF8;
         tmp |= 0x05;
         SX1278_WriteSingle(0x31, tmp);
         SX1278_WriteSingle(0x37, 0x0C);
		} 
		else
		{
			SX1278_WriteSingle(LR_RegModemConfig1,  ((SX1278_LoRaBandwidth[MyLoRaSettings->LoRa_BW] << 4)
 						           + (SX1278_CodingRate[MyLoRaSettings->LoRa_CR] << 1) + 0x00)); //Explicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
       	SX1278_WriteSingle(LR_RegModemConfig2,((SX1278_SpreadFactor[MyLoRaSettings->LoRa_SF] << 4)
									  + (SX1278_CRC_Sum[MyLoRaSettings->LoRa_CRC_sum] << 2) + 0x00)); //SFactor &  LNA gain set by the internal AGC loop
		}
	ё(LR_RegModemConfig3, 0x04);
   SX1278_SPIWrite(MyLoRaSettings, LR_RegSymbTimeoutLsb, 0x08); //RegSymbTimeoutLsb Timeout = 0x3FF(Max)
//	SX1278_SPIWrite(MyLoRaSettings, LR_RegPreambleMsb, 0x00); //RegPreambleMsb
//	SX1278_SPIWrite(MyLoRaSettings, LR_RegPreambleLsb, 8); //RegPreambleLsb 8+4=12byte Preamble
//	SX1278_SPIWrite(MyLoRaSettings, REG_LR_DIOMAPPING2, 0x01); //RegDioMapping2 DIO5=00, DIO4=01
//	MyLoRaSettings->readBytes = 0;
//	//SX1278_standby(MyLoRaSettings); //Entry standby mode
}

void SX1278_sleep(LoRaSettings *MyLoRaSettings) 
{
	SX1278_WriteSingle(LR_RegOpMode, 0x08);
	MyLoRaSettings->status = SLEEP;
}
/************************************************************
*************************************************************/
void SX1278_entryLoRa()
{
	SX1278_WriteSingle(LR_RegOpMode, 0x88);
}

/************************ (C) BORISOV RUSLAN *****END OF FILE****/

