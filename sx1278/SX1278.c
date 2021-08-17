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

void SX1278_config(LoRaSettings *MyLoRaSettings)
{
   SX1278_sleep(MyLoRaSettings); 
   SX1278_timDelayMs(15); 
   SX1278_entryLoRa();          
  //SX1278_SPIWrite(module, 0x5904); //?? Change digital regulator form 1.6V to 1.47V: see errata note
	
	 uint64_t freq = ((uint64_t) MyLoRaSettings->frequency << 19) / 32000000;
   uint8_t freq_reg[3];
	
   freq_reg[0] = (uint8_t) (freq >> 16);
   freq_reg[1] = (uint8_t) (freq >> 8);
   freq_reg[2] = (uint8_t) (freq >> 0);
   SX1278_WriteBurst(LR_RegFrMsb,freq_reg, 3);  
	
   SX1278_WriteSingle(RegSyncWord, MyLoRaSettings->LoRa_SyncWord_39); 
	
   SX1278_WriteSingle(LR_RegPaConfig, MyLoRaSettings->power); 
	
   SX1278_WriteSingle(LR_RegOcp, SX1278_LR_RegOcp(MyLoRaSettings));		
	
   SX1278_WriteSingle(LR_RegLna, SX1278_RegLna(MyLoRaSettings));		
	 
	 SX1278_WriteSingle(LR_RegModemConfig1,SX1278_LR_RegModemConfig1(MyLoRaSettings));
	 
	 SX1278_WriteSingle(LR_RegModemConfig2,SX1278_LR_RegModemConfig2(MyLoRaSettings)); 
   
	if (MyLoRaSettings->LoRa_SF_1E== 6) //SFactor=6
		{	
			uint8_t tmp;
         tmp = SX1278_ReadSingle(0x31);
         tmp &= 0xF8;
         tmp |= 0x05;
         SX1278_WriteSingle(0x31, tmp);
         SX1278_WriteSingle(0x37, 0x0C);
		} 
		
	SX1278_WriteSingle(LR_RegModemConfig3, SX1278_LR_RegModemConfig3(MyLoRaSettings));
		
	SX1278_WriteSingle(LR_RegPreambleMsb, MyLoRaSettings->PreambleMsb_20); //RegPreambleMsb
		
  SX1278_WriteSingle(LR_RegPreambleLsb, MyLoRaSettings->PreamblelSB_21); //RegPreambleLsb 8+4=12byte Preamble
 	
	SX1278_WriteSingle(REG_LR_DIOMAPPING2, SX1278_LR_DIOMAPPING2(MyLoRaSettings)); //RegDioMapping2 DIO5=00, DIO4=01
  
	MyLoRaSettings->readBytes = 0;
  
	SX1278_standby(MyLoRaSettings);
}

/************************************************************
*************************************************************/

void SX1278_sleep(LoRaSettings *MyLoRaSettings) 
{
	SX1278_WriteSingle(LR_RegOpMode, 0x08);
	MyLoRaSettings->status = SLEEP;
}

/************************************************************
*************************************************************/

int SX1278_LoRaEntryRx(LoRaSettings *MyLoRaSettings, uint8_t length, uint32_t timeout)
{
	uint8_t addr;
	MyLoRaSettings->LoRa_packetLength = length;
	SX1278_config(MyLoRaSettings);		//Setting base parameter
	SX1278_WriteSingle(REG_LR_PADAC, 0x84);	//Normal and RX
	SX1278_WriteSingle(LR_RegHopPeriod, 0xFF);	//No FHSS
	SX1278_WriteSingle(REG_LR_DIOMAPPING1, SX1278_LR_DIOMAPPING1(MyLoRaSettings));//DIO=00,DIO1=00,DIO2=00, DIO3=01
	SX1278_WriteSingle(LR_RegIrqFlagsMask, SX1278_LR_RegIrqFlagsMask(MyLoRaSettings));//Open RxDone interrupt & Timeout
	SX1278_clearLoRaIrq();  // очистить флаги прерывания
	SX1278_WriteSingle(LR_RegPayloadLength, length);//Payload Length 21byte(this register must difine when the data long of one byte in SF is 6)
	addr = SX1278_ReadSingle(LR_RegFifoRxBaseAddr); //Read RxBaseAddr
	SX1278_WriteSingle(LR_RegFifoAddrPtr, addr); //RxBaseAddr->FiFoAddrPtr
	SX1278_WriteSingle(LR_RegOpMode, 0x8d);	//Mode//Low Frequency Mode
	//SX1278_WriteSingle(LR_RegOpMode,0x05);	//Continuous Rx Mode //High Frequency Mode
	MyLoRaSettings->readBytes = 0;
	while (1) 
		{
			if((SX1278_ReadSingle(LR_RegModemStat) & 0x04) == 0x04) 
				{	//Rx-on going RegModemStat
					MyLoRaSettings->status = RX;
					return 1;
		      }
			if(--timeout == 0) 
				{
					SX1278_hw_Reset();
					SX1278_config(MyLoRaSettings);
					return 0;
				}
			SX1278_timDelayMs(1);
		}
}

/************************************************************
*************************************************************/

uint8_t SX1278_LoRaRxPacket(LoRaSettings *MyLoRaSettings){
	uint8_t addr;
	uint8_t packet_size;
	if(SX1278_hw_GetDIO0())
		{
			for(int i=0; i<SX1278_MAX_PACKET; i++)
				{
					MyLoRaSettings->txBuffer[i] = 0x00;
				}
			addr = SX1278_ReadSingle(LR_RegFifoRxCurrentaddr); //last packet addr
			SX1278_WriteSingle(LR_RegFifoAddrPtr, addr); //RxBaseAddr -> FiFoAddrPtr
			if (MyLoRaSettings->LoRa_SF_1E == SX1278_LORA_SF_6) //When SpreadFactor is six,will used Implicit Header mode(Excluding internal packet length)
				{ 
					packet_size = MyLoRaSettings->LoRa_packetLength;
				} 
			else 
				{
					packet_size = SX1278_ReadSingle(LR_RegRxNbBytes); //Number for received bytes
				}
			SX1278_ReadBurst(0x00, MyLoRaSettings->rxBuffer, packet_size);
			MyLoRaSettings->readBytes = packet_size;
			SX1278_clearLoRaIrq();
	  }
	return MyLoRaSettings->readBytes;
}

/************************************************************
*************************************************************/

int SX1278_LoRaEntryTx(LoRaSettings *MyLoRaSettings, uint8_t length, uint32_t timeout) 
{
	uint8_t addr;
	uint8_t temp;
	MyLoRaSettings->LoRa_packetLength = length;
	SX1278_config(MyLoRaSettings); //setting base parameter
	SX1278_WriteSingle(REG_LR_PADAC, 0x87);	//Tx for 20dBm
	SX1278_WriteSingle(LR_RegHopPeriod, 0x00); //RegHopPeriod NO FHSS
	SX1278_WriteSingle(REG_LR_DIOMAPPING1, 0x41); //DIO0=01, DIO1=00,DIO2=00, DIO3=01
	SX1278_clearLoRaIrq();
	SX1278_WriteSingle(LR_RegIrqFlagsMask, 0xF7); //Open TxDone interrupt
	SX1278_WriteSingle(LR_RegPayloadLength, length); //RegPayloadLength 21byte
	addr = SX1278_ReadSingle(LR_RegFifoTxBaseAddr); //RegFiFoTxBaseAddr
	SX1278_WriteSingle(LR_RegFifoAddrPtr, addr); //RegFifoAddrPtr

	while(1) 
		{
		temp = SX1278_ReadSingle(LR_RegPayloadLength);
		if(temp == length) 
			{
				MyLoRaSettings->status = TX;
				return 1;
		   }

		if(--timeout == 0) 
			{
				SX1278_hw_Reset();
				SX1278_config(MyLoRaSettings);
				return 0;
		  }
	  }
}

/************************************************************
*************************************************************/

int SX1278_LoRaTxPacket(LoRaSettings *MyLoRaSettings, uint8_t *txBuffer, uint8_t length, uint32_t timeout) {
	  SX1278_WriteBurst(0x00, txBuffer, length);
	  SX1278_WriteSingle(LR_RegOpMode, 0x8b);	//Tx Mode
	  while (1) 
		  {
			if(SX1278_hw_GetDIO0()) //if(Get_NIRQ()) //Packet send over
				{ 
					SX1278_ReadSingle(LR_RegIrqFlags);
					SX1278_clearLoRaIrq(); //Clear irq
					SX1278_standby(MyLoRaSettings); //Entry Standby mode
					return 1;
			   }

			if(--timeout == 0)
				{
					SX1278_hw_Reset();
					SX1278_config(MyLoRaSettings);
					return 0;
			   }
			SX1278_timDelayMs(1);
	   }
}

/************************************************************
*************************************************************/

void SX1278_entryLoRa()
{
	SX1278_WriteSingle(LR_RegOpMode, 0x88);
}

/************************************************************
*************************************************************/

void SX1278_standby(LoRaSettings *MyLoRaSettings) 
{
	SX1278_WriteSingle(LR_RegOpMode, 0x09);
	MyLoRaSettings->status = STANDBY;
}

/************************************************************
*************************************************************/

void SX1278_clearLoRaIrq() 
{
	SX1278_WriteSingle(LR_RegIrqFlags, 0xFF);
}

/************************************************************
*************************************************************/

uint8_t SX1278_RSSI_LoRa()
{
	uint32_t temp = 10;
	temp = SX1278_ReadSingle(LR_RegRssiValue); //Read RegRssiValue, Rssi value
	temp = temp + 127 - 137; //127:Max RSSI, 137:RSSI offset
	return (uint8_t) temp;
}

/************************************************************
*************************************************************/

uint8_t SX1278_RSSI()
{
	uint8_t temp = 0xff;
	temp = SX1278_ReadSingle(RegRssiValue);
	temp = 127 - (temp >> 1);	//127:Max RSSI
	return temp;
}

/************************************************************
*************************************************************/

void SX1278_init()
{

}

/************************************************************
*************************************************************/

int SX1278_transmit(LoRaSettings *MyLoRaSettings, uint8_t *txBuf, uint8_t length, uint32_t timeout)
{
	if (SX1278_LoRaEntryTx(MyLoRaSettings, length, timeout))
		{
			return SX1278_LoRaTxPacket(MyLoRaSettings, txBuf, length, timeout);
	   }
	return 0;
}

/************************************************************
*************************************************************/

int SX1278_receive(LoRaSettings *MyLoRaSettings, uint8_t length, uint32_t timeout)
{
	return SX1278_LoRaEntryRx(MyLoRaSettings, length, timeout);
}

/************************************************************
*************************************************************/

uint8_t SX1278_available(LoRaSettings *MyLoRaSettings) 
{
	return SX1278_LoRaRxPacket(MyLoRaSettings);
}

/************************************************************
*************************************************************/

uint8_t SX1278_read(LoRaSettings *MyLoRaSettings, uint8_t *rxBuf, uint8_t length) 
{
	
}

/************************************************************
*************************************************************/

uint8_t SX1278_LR_RegOcp(LoRaSettings *MyLoRaSettings) 
{  
	uint8_t temp;
	temp = MyLoRaSettings->LoRa_ocp_Imax_0B;
	if(temp>0xF0)
		{
		temp = 0xF0;
		}
	return (temp<=0xf) ? ((temp+45)/5):((temp+30)/10);
  
}

/************************************************************
*************************************************************/

/************************************************************
*************************************************************/

uint8_t SX1278_LR_DIOMAPPING1(LoRaSettings *MyLoRaSettings) 
{  
	uint8_t temp;
	temp |= (MyLoRaSettings->Dio_0_0Map_40<<6)|(MyLoRaSettings->Dio_1_0Map_40<<4)|
	        (MyLoRaSettings->Dio_2_0Map_40<<2)| (MyLoRaSettings->Dio_3_0Map_40<<0);
  return temp;
}

/************************************************************
*************************************************************/


uint8_t SX1278_RegLna(LoRaSettings *MyLoRaSettings) 
{  
	uint8_t temp;
	temp |= (MyLoRaSettings->LoRa_Lna_Gain_0C<<5)|(MyLoRaSettings-> LoRa_Lna_BoostLf_0C<<3)|
	        (MyLoRaSettings->LoRa_Lna_BoostHf_0C<<0);
  return temp;
}

/************************************************************
*************************************************************/

uint8_t SX1278_LR_RegModemConfig1(LoRaSettings *MyLoRaSettings) 
{  
	uint8_t temp;
	if (MyLoRaSettings->LoRa_SF_1E== 6) 
		{	
        temp|= (MyLoRaSettings->LoRa_BW_1D<< 4)|(MyLoRaSettings->LoRa_CodingRate_1D<< 1)|0x01; //Implicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
        return temp;
		} 
		else
		{
			 temp|= (MyLoRaSettings->LoRa_BW_1D << 4)|(MyLoRaSettings->LoRa_CodingRate_1D<< 1)|0x00; //Explicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
       return temp;
		}
}
/************************************************************
*************************************************************/

uint8_t SX1278_LR_RegModemConfig2(LoRaSettings *MyLoRaSettings) 
{  
	uint8_t temp;
	if (MyLoRaSettings->LoRa_SF_1E== 6) 
		{	
        temp|= (MyLoRaSettings->LoRa_SF_1E << 4)|(MyLoRaSettings->LoRa_RxPayloadCrcOn_1E<< 2)|0x03;
        return temp;
		} 
		else
		{
			 temp|= (MyLoRaSettings->LoRa_SF_1E << 4)|(MyLoRaSettings->LoRa_RxPayloadCrcOn_1E << 2)|0x00; //SFactor &  LNA gain set by the internal AGC loop
       return temp;
		}
}

/************************************************************
*************************************************************/

uint8_t SX1278_LR_RegModemConfig3(LoRaSettings *MyLoRaSettings) 
{  
	uint8_t temp;
	temp |= (MyLoRaSettings->LoRa_LDRateOptimize_26 << 3)|(MyLoRaSettings-> LoRa_AgcAutoOn_26 <<2);
  return temp;
}
/************************************************************
*************************************************************/

uint8_t SX1278_LR_DIOMAPPING2(LoRaSettings *MyLoRaSettings) 
{  
	uint8_t temp;
	temp |= (MyLoRaSettings->Dio_4_0Map_41 << 6)|(MyLoRaSettings->Dio_5_0Map_41 << 4)|
					(MyLoRaSettings->PreambleDetect_41 << 0);
  return temp;
}

/************************************************************
*************************************************************/

uint8_t SX1278_LR_RegIrqFlagsMask(LoRaSettings *MyLoRaSettings) 
{  
	uint8_t temp;
	temp |= (MyLoRaSettings->RxTimeoutMask_11 << 7)|(MyLoRaSettings->RxDoneMask_11 << 6)|
					(MyLoRaSettings->PayloadCrcErrorMask_11 << 5)|(MyLoRaSettings->ValidHeaderMask_11 << 4)|
					(MyLoRaSettings->TxDoneMask_11 << 3)|(MyLoRaSettings->CadDoneMask_11 << 2)|
					(MyLoRaSettings->FhssChangeChannelMask_11 << 1)|(MyLoRaSettings->CadDetectedMask_11 << 0);
  return temp;
}
/************************************************************
*************************************************************/

/************************ (C) BORISOV RUSLAN *****END OF FILE****/

