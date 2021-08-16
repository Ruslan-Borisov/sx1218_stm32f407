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
 * \brief ms delay
 *
 * Milisecond delay.
 *
 * \param[in]   msec 		Number of milliseconds to wait
 */
void SX1278_hw_DelayMs(uint32_t msec);

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

void WriteBurst( uint8_t addr, char *buff, uint8_t size);

void ReadBurst( uint8_t cmd, char *buff, uint8_t size);

uint8_t WriteSingle(uint8_t cmd, uint8_t signal);

uint8_t SPI_ReadSignal_SPI(uint8_t cmd);

#ifdef __cplusplus
}
#endif

#endif /* __SX1278_HW_H_*/

