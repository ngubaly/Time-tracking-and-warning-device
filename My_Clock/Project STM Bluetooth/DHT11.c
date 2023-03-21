/**
  *****************************************************************************
	*
  * @file    dht11.c
  * @version V1.0.0
  *
  ******************************************************************************
**/

#include "DHT11.h"
#include "main.h"
#include "stm32f10x_gpio.h"
#include "user_delay.h"
 /*******************************************************************************
Noi Dung    :   MCU gui yeu cau chuyen doi den DHT11.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
void GPIO_SetState(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,GPIOMode_TypeDef GPIO_Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;	         		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

uint8_t DHT_GetTemHumi(uint8_t *tem,uint8_t *humi)
{
	uint8_t buffer[5]={0,0,0,0,0};
	uint8_t i,j,checksum;
//	DHT_DDR_DATA = DDROUT;   // set la cong ra
	GPIO_SetState(DHT_GPIO,DHT_DATA,GPIO_Mode_Out_OD);//Thiet lap dau ra

	GPIO_SetBits(DHT_GPIO,DHT_DATA);	//DHT_DATA_OUT = 1;
  delay_us(60);
	//Delay(1);
	
	GPIO_ResetBits(DHT_GPIO,DHT_DATA);	//DHT_DATA_OUT = 0;
  delay_ms(25); // it nhat 18ms
	//Delay(25);
	
	GPIO_SetBits(DHT_GPIO,DHT_DATA);	//DHT_DATA_OUT=1;
  //delay_us(40); // doi DHT dap ung trong vong 20us-40us
	
//	DHT_DDR_DATA = DDRIN;	//set la cong vao
	GPIO_SetState(DHT_GPIO,DHT_DATA,GPIO_Mode_IN_FLOATING);//Thiet lap dau vao
	delay_us(60);
	//Delay(1);
	
//  if (DHT_DATA_IN) return DHT_ER;
//	else while(!(DHT_DATA_IN));	//Doi DaTa len 1
	
	if (GPIO_ReadInputDataBit(DHT_GPIO,DHT_DATA)) return DHT_ER;
	else while(!GPIO_ReadInputDataBit(DHT_GPIO,DHT_DATA));
  delay_us(60);
	//Delay(1);
	
//  if (!DHT_DATA_IN) return DHT_ER;
//	else while((DHT_DATA_IN));	 //Doi Data ve 0
	
	if (!GPIO_ReadInputDataBit(DHT_GPIO,DHT_DATA)) return DHT_ER;
	else while(GPIO_ReadInputDataBit(DHT_GPIO,DHT_DATA));
	
	//Bat dau doc du lieu
	for(i=0;i<5;i++)
	{
		for(j=0;j<8;j++)
		{
			//while((!DHT_DATA_IN));//Doi Data len 1
			while(!GPIO_ReadInputDataBit(DHT_GPIO,DHT_DATA));
			delay_us(50);
			//Delay(1);
			//if(DHT_DATA_IN)
			if (GPIO_ReadInputDataBit(DHT_GPIO,DHT_DATA))
			{
				buffer[i]|=(1<<(7-j));
				//while((DHT_DATA_IN));//Doi Data xuong 0
				while(GPIO_ReadInputDataBit(DHT_GPIO,DHT_DATA));
			}
		}
	}
	
  checksum = buffer[0] + buffer[1] + buffer[2] + buffer[3];
  //DHT_DDR_DATA=DDROUT;
  //DHT_DATA_OUT=1;
  if((checksum)!=buffer[4])return DHT_ER;
  *tem  =   buffer[2];
	*humi =   buffer[0];
	return DHT_OK;
}
/******************************KET THUC FILE******************************
______________________________THINH NGUYEN______________________________*/
