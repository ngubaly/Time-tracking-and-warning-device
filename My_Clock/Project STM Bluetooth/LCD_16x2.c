#include "stm32f10x.h"
#include "User_Function.h"
#include "User_Delay.h"
void LCD_Config(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_8;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;

GPIO_Init(GPIOB,&GPIO_InitStructure);

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13|GPIO_Pin_12;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
GPIO_Init(GPIOB,&GPIO_InitStructure);

}

void LCD_Enable(void)
{
GPIO_SetBits(GPIOB,EN_PIN);
delay_us(3);
GPIO_ResetBits(GPIOB,EN_PIN);
delay_us(50);	
}

void LCD_Send4bit(uint8_t Data){
GPIO_WriteBit(GPIOB,D4_PIN,(Data>>0)&0x01);
GPIO_WriteBit(GPIOB,D5_PIN,(Data>>1)&0x01);
GPIO_WriteBit(GPIOB,D6_PIN,(Data>>2)&0x01);
GPIO_WriteBit(GPIOB,D7_PIN,(Data>>3)&0x01);
}

void LCD_SendCommand(uint8_t Command)
{
LCD_Send4bit(Command>>4);
LCD_Enable();
LCD_Send4bit(Command);
LCD_Enable();
}
void LCD_Clear(void){
	LCD_SendCommand(0x01);
	delay_ms(5);

}
void LCD_Init(void){
LCD_Send4bit(0x00);
delay_ms(20);
GPIO_ResetBits(GPIOB,RS_PIN);
LCD_Send4bit(0x03);
LCD_Enable();
delay_ms(5);
LCD_Enable();
delay_us(100);
LCD_Enable();
LCD_Send4bit(0x02);
LCD_Enable();
LCD_SendCommand(0x28);
LCD_SendCommand(0x0C);
LCD_SendCommand(0x06);
LCD_Clear();
}

void LCD_Gotoxy(uint8_t x, uint8_t y){
uint8_t address;
if(!y) address = (0x80+x);
else address=(0xC0+x);
delay_ms(1);
LCD_SendCommand(address);
delay_ms(5);
}

void LCD_PutChar(uint8_t Data)
{
GPIO_SetBits(GPIOB,RS_PIN);
LCD_SendCommand(Data);
GPIO_ResetBits(GPIOB,RS_PIN);
}
void LCD_Puts(uint8_t *s)
{while(*s){
LCD_PutChar(*s);
	s++;
}
}
