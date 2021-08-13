/**
  ******************************************************************************
  * @file           : while_slave.c
  * @brief          : Main program body
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */

#include "while_slave.h"
#include "SX1278.h"
#include "SX1278_hw.h"	
#include "SX1278.h"



void whileSlave()
{
	test2++;
 WriteSingle(REG_LR_DIOMAPPING1,	RFLR_DIOMAPPING1_DIO0_00);
 WriteSingle(REG_LR_SYNCWORD,0x12);	
 WriteSingle(REG_LR_OPMODE,RFLR_OPMODE_STANDBY|0x80);
 WriteSingle(REG_LR_FIFOADDRPTR,0x00);
 WriteSingle(REG_LR_OPMODE,RFLR_OPMODE_RECEIVER|0x80);
	
 while (1)
  {
	if(status_DIO_0==1){
	rxBuffSize = SPI_ReadSignal(REG_LR_NBRXBYTES);
	RSSI_Vale= SPI_ReadSignal(REG_LR_PKTRSSIVALUE);
	SNR_Vale = SPI_ReadSignal(REG_LR_PKTSNRVALUE);
	ReadBurst( REG_LR_FIFO, buffRX, rxBuffSize);
	WriteSingle(REG_LR_OPMODE,RFLR_OPMODE_SLEEP|0x80);
	WriteSingle(REG_LR_FIFOADDRPTR,0x00);
	WriteSingle(REG_LR_OPMODE,RFLR_OPMODE_RECEIVER|0x80);	
	status_DIO_0=0;
	}
  }

}

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
