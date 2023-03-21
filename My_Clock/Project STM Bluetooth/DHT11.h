/**
  ******************************************************************************
  *
  * @file    dht11.h
  * @author  Thinh Nguyen
  * @version V1.0.0
  * @date    04-09-2016
  *           
  *
  ******************************************************************************
**/
#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"

#define DHT_ER       0
#define DHT_OK       1
#define DDROUT         0
#define DDRIN          1
#define DHT_GPIO			 			GPIOB
#define DHT_GPIO_CLK  			RCC_APB2Periph_GPIOB
#define DHT_DATA  					GPIO_Pin_12 

void GPIO_SetState(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,GPIOMode_TypeDef GPIO_Mode);
 /*******************************************************************************
Noi Dung    :   MCU gui yeu cau chuyen doi den DHT11.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
uint8_t DHT_Start(void);
 /*******************************************************************************
Noi Dung    :   Kiem tra dap ung cua DHT11 sau yeu cau chuyen doi.
Tham Bien   :   Khong.
Tra Ve      :   DHT_ER: Dap ung cua DHT bi loi.
                DHT_OK: Dap ung cua DHT thanh cong.
********************************************************************************/  
//uint8_t   DHT_IsOk(void);
/*******************************************************************************
Noi Dung    :   Doc 1 byte du lieu tu DHT11.
Tham Bien   :   Khong.
Tra Ve      :   1 byte du lieu.
 *******************************************************************************/
uint8_t DHT_ReadByte(void);
/*******************************************************************************
Noi Dung    :   Doc 1 khung du lieu tu DHT11 gui ve.
Tham Bien   :   array: mang so nguyen 8 bit luu tru khung du lieu.
Tra Ve      :   - DHT_OK:   Neu DHT va MCU gui du lieu thanh cong.
                - DHT_ER:   Neu DHT va MCU gui du lieu that bai.
 *******************************************************************************/
uint8_t DHT_GetFrame(uint8_t *array);   
/*******************************************************************************
Noi Dung    :   Doc gia tri nhiet do, do am tu DHT.
Tham Bien   :   *tem:    con tro luu tru gia tri nhiet do.
                *humi:   con tro luu tru gia tri do am.   
Tra Ve      :   - DHT_OK:   Neu do nhiet do,do am thanh cong.
                - DHT_ER:   Neu do nhiet do, do am xay ra loi.
 *******************************************************************************/
uint8_t DHT_GetTemHumi (uint8_t *tem,uint8_t *humi);
#endif
/******************************KET THUC FILE******************************
______________________________THINH NGUYEN______________________________*/
