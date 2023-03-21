#ifndef User_Delay
#define User_Delay
#include "stm32f10x.h"
static uint8_t fac_us=0;
static uint16_t fac_ms=0;
void delay_init(uint8_t SYSCLK);
void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);
#endif