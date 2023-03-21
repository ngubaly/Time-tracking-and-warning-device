/**
  ******************************************************************************
  * @file       nokia_5110.h
  * @author     linhkien69.vn
  * @version    V1.0.0
  * @date       28/02/2013
  ******************************************************************************
*/

#ifndef __NOKIA_5110_H
#define __NOKIA_5110_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x.h"

/************************************PIN****************************************/
	 
#define LCD_PIN_RST                    GPIO_Pin_0
#define LCD_PORT_RST                    GPIOB

#define LCD_PIN_CE                     GPIO_Pin_1
#define LCD_PORT_CE                     GPIOB

#define LCD_PIN_DC                     GPIO_Pin_13
#define LCD_PORT_DC                     GPIOC

#define LCD_PIN_DIN                    GPIO_Pin_14
#define LCD_PORT_DIN                    GPIOC
	 
#define LCD_PIN_CLK                    GPIO_Pin_15
#define LCD_PORT_CLK                    GPIOC

#define RCC_NOKIA_5110                 RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC

/******************************************************************************/

#define LCD_CMD   0
#define LCD_DATA  1

/**
You may find a different size screen, but this one is 84 by 48 pixels
**/
#define LCD_X     84
#define LCD_Y     48

 /*******************************************************************************
Chuc nang    :   Ham tao thoi gian tre
Tham so      :   nTime
********************************************************************************/
void nDelay(volatile long nTime);                                                   

 /*******************************************************************************
Chuc nang    :   Ham khoi tao cac PIN GPIO chuc nang
Tham so      :   khong
********************************************************************************/
void LCD_GPIO_Init(void);                                                        

 /*******************************************************************************
Chuc nang    :   Ham khoi tao LCD NOKIA 5110.
Tham so      :   + contrast.
								 + coefficent.
								 + bias.
********************************************************************************/
void LCDInit(unsigned char contrast,unsigned char coefficent,unsigned char bias);  

 /*******************************************************************************
Chuc nang    :   Ham xoa noi dung hien thi tren man hinh LCD Nokia 5110.
Tham so      :   khong
********************************************************************************/
void LCDClear(void);                                                                     

 /*******************************************************************************
Chuc nang    :   Ham viet 1 ki tu len LCD Nokia 5110.
Tham so      :   characters 
********************************************************************************/
void LCDCharacter(char character);                                                  

 /*******************************************************************************
Chuc nang    :   Ham viet 1 chuoi ki tu len LCD Nokia 5110.
Tham so      :   characters 
********************************************************************************/
void LCDString(char *characters);      

 /*******************************************************************************
Chuc nang    :   Ham hien thi 1 hinh anh len LCD Nokia 5110.
Tham so      :   my_array[] la hinh anh can hien thi.
********************************************************************************/
void LCDBitmap(char my_array[]);

 /*******************************************************************************
Chuc nang  :   Thiet lap vi tri con tro LCD NOKIA 5110.
Tham so    :   + x: vi tri cot cua con tro, x gia tri tu 0 -> 83.
               + y: vi tri hang cua con tro, y gia tri tu 0 -> 5.
********************************************************************************/
void gotoXY(int x, int y);                                                          

 /*******************************************************************************
Chuc nang  :   Gui 1 Byte du lieu den Nokia5110
Tham so    :   + data_or_command   
               + data                :   Byte du lieu.
********************************************************************************/
void LCDWrite(char data_or_command, unsigned char data);                            

 /*******************************************************************************
Chuc nang  :   Dich du lieu txdata ra PIN DIN
Tham so    :   txdata   
********************************************************************************/
void shiftOut(unsigned char txdata);                                               


#ifdef __cplusplus
}
#endif


#endif /* __NOKIA_5110_H */

/************************* linhkien69.vn ************************END OF FILE****/
