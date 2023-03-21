#ifndef LCD_16x2
#define LCD_16x2
#include "stm32f10x.h"
void LCD_Config(void);
void LCD_Enable(void);
void LCD_Send4bit(uint8_t Data);
void LCD_SendCommand(uint8_t Command);
void LCD_Init(void);
void LCD_Gotoxy(uint8_t x, uint8_t y);
void LCD_Clear(void);
void LCD_PutChar(uint8_t Data);
void LCD_Puts(uint8_t *s);
#endif