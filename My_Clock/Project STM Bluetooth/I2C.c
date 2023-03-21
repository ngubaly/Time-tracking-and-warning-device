#include <I2C.H>
#include "User_Function.h"



	 /*-----------------------Giao tiep I2C------------------------------*/
void I2C_Start(){
	
	GPIO_SetBits(GPIOB,SCL);
	GPIO_SetBits(GPIOB,SDA);
	GPIO_ResetBits(GPIOB,SDA);								
	GPIO_ResetBits(GPIOB,SCL);		
}
void I2C_Stop(){
	GPIO_SetBits(GPIOB,SCL);
	GPIO_ResetBits(GPIOB,SDA);
	GPIO_SetBits(GPIOB,SCL);
	GPIO_SetBits(GPIOB,SDA);
}
unsigned char I2C_Write(unsigned char Data){
	unsigned char i;
	for(i=0;i<8;i++){
		if((Data&0x80)==1) GPIO_SetBits(GPIOB,SDA);
		else 	GPIO_ResetBits(GPIOB,SDA);
		GPIO_SetBits(GPIOB,SCL);
		GPIO_ResetBits(GPIOB,SCL);	
		Data<<=1;
	}
	GPIO_SetBits(GPIOB,SCL);
	GPIO_ResetBits(GPIOB,SCL);	
	return Data;
}
unsigned char I2C_Read(void){
	char Read_Bit;
	unsigned char i,Data;
	Data=0x00;
	for(i=0;i<8;i++){
	GPIO_SetBits(GPIOB,SCL);
	Read_Bit=SDA;
	Data=Data<<1;
	Data=Data|Read_Bit;
	GPIO_ResetBits(GPIOB,SCL);	
	}
	return Data;
}