/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __User_function_H
#define __User_function_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "main.h"

/***************** Dinh nghia *************************************/
#define LED_Clock						RCC_APB2Periph_GPIOB

#define LED_PORT 						GPIOB
#define LED_Pin							GPIO_Pin_0

#define LED_Clock_Relay			RCC_APB2Periph_GPIOA

#define LED_PORT_RELAY			GPIOA
#define LED_Pin_1						GPIO_Pin_4
#define LED_Pin_2						GPIO_Pin_5

// Ham cau hinh cho chan LED o PB0
// Gia tri tra ve: khong tra ve gia tri, ham void
// Tham so truyen vao: Khong can truyen tham so

void Initial_GPIO(void);

#endif /* __User_function_H */
