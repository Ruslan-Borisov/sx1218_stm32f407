
/**
  ******************************************************************************
  * @file           : while_slave.h
  * @brief          : Header for while_slave.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */


#ifndef __WHILE_SLAVE_H
#define __WHILE_SLAVE_H

#ifdef __cplusplus
extern "C" {
#endif

	
#include "main.h"

extern uint8_t rxBuffSize;

extern uint16_t RSSI_Vale;
extern uint16_t SNR_Vale;	
	
void whileSlave();
	
extern char buffRX[16];

extern volatile uint8_t status_DIO_0;
	

extern int test1;
extern int test2;

#ifdef __cplusplus
}
#endif

#endif /* __WHILE_SLAVE_H */

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
