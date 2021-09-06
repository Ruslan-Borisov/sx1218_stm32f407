/**
  ******************************************************************************
  * @file    ic1306.h
  * @brief   
  ******************************************************************************
  * @attention

  *
  ******************************************************************************
  */

#ifndef __IC1306__H
#define __IC1306__H

#ifdef __cplusplus
extern "C" {
#endif


#define COMAND 0x00
#define DATA   0x40

#define OLED_adress 0x78
#define OLED_SETCONTRAST 0x81
#define OLED_DISPLAYALLON_RESUME 0xA4
#define OLED_DISPLAYALLON 0xA5
#define OLED_NORMALDISPLAY 0xA6
#define OLED_INVERTDISPLAY 0xA7
#define OLED_DISPLAYOFF 0xAE
#define OLED_DISPLAYON 0xAF
#define OLED_SETDISPLAYOFFSET 0xD3
#define OLED_SETCOMPINS 0xDA
#define OLED_SETVCOMDETECT 0xDB
#define OLED_SETDISPLAYCLOCKDIV 0xD5
#define OLED_SETPRECHARGE 0xD9
#define OLED_SETMULTIPLEX 0xA8
#define OLED_SETLOWCOLUMN 0x00
#define OLED_SETHIGHCOLUMN 0x10
#define OLED_SETSTARTLINE 0x40
#define OLED_MEMORYMODE 0x20
#define OLED_COLUMNADDR 0x21
#define OLED_PAGEADDR   0x22
#define OLED_COMSCANINC 0xC0
#define OLED_COMSCANDEC 0xC8
#define OLED_SEGREMAP 0xA0
#define OLED_CHARGEPUMP 0x8D
#define OLED_SWITCHCAPVCC 0x2
#define OLED_NOP 0xE3

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_BUFFERSIZE (OLED_WIDTH*OLED_HEIGHT)/8
#define OLED_DEFAULT_SPACE 5

#include "main.h"

void ssd1306_init(void);

void ssd1306_sendCommand(unsigned char command);

void 	ssd1306_sendData(uint8_t data);

void ssd1306_Send(uint8_t *data, uint8_t count);

void LCD_Goto(unsigned char x, unsigned char y);

void LCD_Char(unsigned int c);

void LCD_Clear(void);

void OLED_string(char *string);

void OLED_num_to_str(unsigned int value, unsigned char nDigit);




#ifdef __cplusplus
}
#endif

#endif /* __IC1306__H */

/************************ (C) BORISOV RUSLAN *****END OF FILE****/
