
/**
  ******************************************************************************
  * @file           : while_master.h
  * @brief          : Header for while_master.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */


#ifndef __WHILE_MASTER_H
#define __WHILE_MASTER_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "main.h"
#include "SX1278_hw.h"

void whileMaster();

extern char buffTX[16];	

extern int test1;
extern int test2;	
	
#ifdef __cplusplus
}
#endif

#endif /*  __WHILE_MASTER_H*/

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
