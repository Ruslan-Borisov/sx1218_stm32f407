/**
  ******************************************************************************
  * @file    SX1278_hw.h
  * @brief          : Header for SX1278_hw.c file.
  *                   This file contains the common defines of the application.  
  ******************************************************************************
  * @attention
 
  ******************************************************************************
  */

#ifndef __SX1278_HW_H_
#define __SX1278_HW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define SPI_STATE_READY             (1<<15)

#define SPI1_DR_8bit 			      *((__IO uint8_t *)&SPI1->DR)


#define 	WRITE_SINGLE     				0x80
#define 	READ_SINGLE     				0x00

/**
 * \brief Initialize hardware layer
 *
 * Clears NSS and resets LoRa module.
 *
 * \param[in]  
 */
void SX1278_hw_init();

/**
 * \brief Control NSS
 *
 * Clears and sets NSS according to passed value.
 *
 * \param[in]   value   1 sets NSS high, other value sets NSS low.
 */
void SX1278_hw_SetNSS(int value);

/**
 * \brief Resets LoRa module
 *
 * Resets LoRa module.
 *
 * \param[in]  
 */
void SX1278_hw_Reset();



/**
 * \brief Reads DIO0 state
 *
 * Reads LoRa DIO0 state using GPIO.
 *
 * \param[in]   hw 		Pointer to hardware structure
 *
 * \return				0 if DIO0 low, 1 if DIO high
 */
int SX1278_hw_GetDIO0();


int SPI_GetState();

uint8_t SX1278_WriteSingle(uint8_t command, uint8_t value);

uint8_t SX1278_ReadSingle(uint8_t command);

void SX1278_WriteBurst( uint8_t addr,char *buff, uint8_t size);

void SX1278_ReadBurst( uint8_t cmd, char *buff, uint8_t size);

void SX1278_timDelayMs(uint32_t msec);

#ifdef __cplusplus
}
#endif

#endif /* __SX1278_HW_H_*/

