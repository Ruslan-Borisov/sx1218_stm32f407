/**
  ******************************************************************************
  * @file    SX1278.h
  * @brief          : Header for SX1278.c file.
  *                   This file contains the common defines of the application.  
  ******************************************************************************
  * @attention
 
  ******************************************************************************
  */

#ifndef __SX1278_H__
#define __SX1278_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "SX1278_hw.h"	

/*!
 * SX1276 LoRa General parameters definition
 */

typedef struct sLoRaSettings
{
    uint32_t RFFrequency;
    int8_t Power;
    uint8_t SignalBw;                   // LORA [0: 7.8 kHz, 1: 10.4 kHz, 2: 15.6 kHz, 3: 20.8 kHz, 4: 31.2 kHz,
                                        // 5: 41.6 kHz, 6: 62.5 kHz, 7: 125 kHz, 8: 250 kHz, 9: 500 kHz, other: Reserved]  
    uint8_t SpreadingFactor;            // LORA [6: 64, 7: 128, 8: 256, 9: 512, 10: 1024, 11: 2048, 12: 4096  chips]
    uint8_t ErrorCoding;                // LORA [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
    uint8_t CrcOn;                         // [0: OFF, 1: ON]
    uint8_t ImplicitHeaderOn;              // [0: OFF, 1: ON]
    uint8_t RxSingleOn;                    // [0: Continuous, 1 Single]
    uint8_t FreqHopOn;                     // [0: OFF, 1: ON]
    uint8_t HopPeriod;                  // Hops every frequency hopping period symbols
    uint32_t TxPacketTimeout;
    uint32_t RxPacketTimeout;
    uint8_t PayloadLength;
}tLoRaSettings;




void SX1278_Init(void);



#ifdef __cplusplus
}
#endif

#endif /* __SX1278_H__ */

/************************ (C) BORISOV RUSLAN  *****END OF FILE****/
