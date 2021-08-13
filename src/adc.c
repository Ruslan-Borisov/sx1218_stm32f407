/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
  ******************************************************************************
	 * @attention
   * ADC configuration for STM32F407
  ******************************************************************************
*/

#include "adc.h"


void ADC1_Init(void)
{
   /*1. Enable ADC and GPIOA clock*/
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	
	/* 2. ADC Clock Prescaler*/ 
	ADC->CCR |= ADC_CCR_ADCPRE_0; /*!< Prescaler 4 > */	
	
	/* 3. Bit 8 SCAN: Scan mode*/
	ADC1->CR1 |= (1<<8); 	/*!< enabled > */
	
	/* 4. Bits 25:24 RES: Resolution */
	ADC1->CR1 &= ~(0x2 << 24);	/*!< 12-bit (15 ADCCLK cycles)> */
	
	/* 5.  Bits 15:13 DISCNUM[2:0]: Discontinuous mode channel count*/
	ADC1->CR1 |= (1<<13)|(1<<14); /*!< channel count 3*/
	
	/* 6. Bit 1 CONT: Continuous conversion*/
	ADC1->CR2 &= ~ (1 << 1);	/*!< Single conversion mode >*/
	
	/* 7. Bit 10 EOCS: End of conversion selection*/   
	ADC1->CR2 &= ~ (1 << 10);	/*!< disabled >*/
		
	/* 8. Bit 11 ALIGN: Data alignment*/ 
	ADC1->CR2 &= ~ (1 << 11);		/*!< Right alignment >*/
	
	/* 8. Bits 27:24 EXTSEL[3:0]: External event select for regular group*/ 
	ADC1->CR2 |= (1 << 25)|(1 << 26);		/*!< Timer 2 TRGO event >*/
	
	/* 9.Bit 8 DMA: Direct DMA (for single ADC mode)*/
  ADC1->CR2 |= (1<<8); /*!< enabled >*/
	
	/* 10.Bit 9 DDS: DMA disable selection (for single ADC mode)*/ 
	ADC1->CR2 |= (1<<9); /*!< DMA requests are issued as long as data are converted and DMA=1 >*/

  /*Bits 29:28 EXTEN: External trigger enable for regular channels*/
	ADC1->CR2 |= (1<<28); /*!< Trigger detection on the rising edge >*/
	
	/*Bits 23:20 L[3:0]: Regular channel sequence length)*/
	ADC1->SQR1 |= (1<<21); /*!< 3 conversions>*/
	
	/*Bits 29:0 SMPx[2:0]: Channel x sampling time selection*/
	ADC1->SMPR2 |= (1<<16); /*!< channel 5  cycles 28>*/
	ADC1->SMPR2 |= (1<<19); /*!< channel 6  cycles 28 >*/
	ADC1->SMPR2 |= (1<<22); /*!< channel 7  cycles 28 >*/
	
	/*ADC regular sequence register 3 (ADC_SQR3)*/
	ADC1->SQR3 |= (0x5<<0); /*!< channel number 5 >*/
	ADC1->SQR3 |= (0x6<<5); /*!< channel number 6 >*/
	ADC1->SQR3 |= (0x7<<10); /*!< channel number 7 >*/
	
	/* 11. Bits 26:0 SMP: Sampling time selection*/ 
	ADC1->SMPR1 |=  (1 << 0);	 /*!< 15 cycles >*/	
	
	/* 12. Bits 2y:2y+1 MODERy[1:0]: Port configuration */
	GPIOA->MODER |= (3 << 10);	/*!< analog mode for PA 5>*/
	GPIOA->MODER |= (3 << 13);	/*!< analog mode for PA 6>*/
	GPIOA->MODER |= (3 << 15);	/*!< analog mode for PA 7>*/
	
	
	/*13. Bit 0 ADON: A/D Converter ON / OFF */
	 ADC1->CR2 |=(1<<0); /*!<Enable ADC>*/
	 
	// ADC1->CR2 |=(1<<30); /*!<Enable ADC>*/
}



/************************ (C) BORISOV RUSLAN *****END OF FILE****/
