/**
  ******************************************************************************
  * @file           : while_master.c
  * @brief          : 
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */

#include "while_master.h"
#include "SX1278_hw.h"	
#include "SX1278.h"



void whileMaster()
{
	test1++;
	int i;
  while (1)
  {
		i++;
		buffTX[13]=i;	
		WriteSingle(REG_LR_DIOMAPPING1,RFLR_DIOMAPPING1_DIO0_01);
		WriteSingle(REG_LR_SYNCWORD,0x12);	
		WriteSingle(REG_LR_OPMODE,RFLR_OPMODE_STANDBY|0x80);
		WriteSingle(REG_LR_FIFOADDRPTR,0x80);
		WriteBurst( REG_LR_FIFO, buffTX, 16);
		WriteSingle(REG_LR_OPMODE,RFLR_OPMODE_TRANSMITTER|0x80); 

		while (status_DIO_0==1) {};	
		WriteSingle(REG_LR_OPMODE,RFLR_OPMODE_SLEEP|0x80);	
		status_DIO_0 = 0;
		SX1278_hw_DelayMs(3000);
      test1++;
	}

}

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
