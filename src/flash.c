/**
  ******************************************************************************
  * @file           : flash.c
  * @brief          : 
  ******************************************************************************
	 * @attention
 
  ******************************************************************************
 */

#include "flash.h"

void unlocking_Flash(void)
{
	FLASH->KEYR = 0x45670123;
	FLASH->KEYR = 0xCDEF89AB;
}

void Internal_Flash_Erase(unsigned int pageAddress) {
	while (FLASH->SR & FLASH_SR_BSY);
	if (FLASH->SR & FLASH_SR_EOP) {
		FLASH->SR = FLASH_SR_EOP;
	}

//	FLASH->CR |= FLASH_CR_PER;
//	FLASH->AR = pageAddress;
//	FLASH->CR |= FLASH_CR_STRT;
//	while (!(FLASH->SR & FLASH_SR_EOP));
//	FLASH->SR = FLASH_SR_EOP;
//	FLASH->CR &= ~FLASH_CR_PER;
}
	
//data - указатель на записываемые данные
//address - адрес во flash
//count - количество записываемых байт, должно быть кратно 2
void Internal_Flash_Write(unsigned char* data, unsigned int address, unsigned int count) {
	unsigned int i;

	while (FLASH->SR & FLASH_SR_BSY);
	if (FLASH->SR & FLASH_SR_EOP) {
		FLASH->SR = FLASH_SR_EOP;
	}

	FLASH->CR |= FLASH_CR_PG;

	for (i = 0; i < count; i += 2) {
		*(volatile unsigned short*)(address + i) = (((unsigned short)data[i + 1]) << 8) + data[i];
		while (!(FLASH->SR & FLASH_SR_EOP));
		FLASH->SR = FLASH_SR_EOP;
	}

	FLASH->CR &= ~(FLASH_CR_PG);
}

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
