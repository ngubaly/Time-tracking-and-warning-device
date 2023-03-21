/**
  ******************************************************************************
  * @file    Timer device
  * @author  Group 11 - Microprocessing
  * @version KeilC_v5
  * @date    March - 2023
  * @brief   This file contains all the main activity 
  *         
  ******************************************************************************
  ******************************************************************************
  */


#include "main.h"
#include "User_Function.h"   // Cau hinh PIN
#include "stm32f10x_tim.h"
#include "User_Delay.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "nokia_5110.h"
#include "DS1307.h"
// #include "DHT11.h"   
void time(void);
uint8_t date, day, month, year, hour, minute, second;
char Str1[20];
int gio,phut=0;
char TEXT[40]= "";
int count = 5;
int minute_now, hour_now, minute_specific, hour_specific;
	// Ham lay thoi gian tu module RTC va hien thi len LCD
void time(void){
	
    ds1307_get_calendar_date(&date, &day, &month, &year);
		ds1307_get_time_24(&hour, &minute, &second);
	
	// Hang dau tien se hien thi theo thu tu: thu:ngay:thang:nam
	 	sprintf(Str1,"T %u:",date);
		gotoXY(0,1);
		LCDString(Str1);
	
		sprintf(Str1,"%2u:",day);
		LCDString(Str1);
	
		sprintf(Str1,"%2u:",month);
		LCDString(Str1);
	
		sprintf(Str1,"%2u",year);
		LCDString(Str1);
	// Hang thu hai se hien thi theo thu tu: gio:phut:giay
		sprintf(Str1,"  %2u:",hour);
		gotoXY(0,2);
		LCDString(Str1);
		
		sprintf(Str1,"%2u:",minute);
		LCDString(Str1);
		
		sprintf(Str1,"%2u",second);
		LCDString(Str1);
}
// ham bat coi neu trung gio va phut
void BUZZZZ(){
	if(hour == hour_specific && minute == minute_specific){
		// Coi bao trong 5 lan
		while(count--){
			GPIO_ResetBits(BUZZ_PORT,BUZZ); // Bat Buzzer
			delay_ms(1000);
			GPIO_SetBits(BUZZ_PORT,BUZZ);  // Tat Buzzer
			delay_ms(1000);
		}
		// Cap nhat 
		minute_now = minute;
		hour_now = hour;
		count = 5;
	}
}
int main(void)
{	
	// Config dau vao button (PA_6 va PA_8)
	Init_GPIO(BT_CLOCK_A, GPIOA,GPIO_Pin_6|GPIO_Pin_8, INPUT);
	// Config dau ra la buzz (PA_4)
	Init_GPIO(BUZZ_CLOCK, GPIOA, BUZZ, OUTPUT);
	SystemInit();
	delay_init(72);
	LCD_GPIO_Init();	
	LCDInit(0x55,1,0 );
	LCDClear();
	ds1307_config();
	ds1307_set_time_24(21, 00, 00); // cai dat gio phut giay
	ds1307_set_calendar_date(1,19,03,23); // cai dat thu ngay thang nam, quy uoc: CN: 1
	
	
  gotoXY(0,0);
  LCDString(" ~My Clock~");
  gotoXY(0,3);
	LCDString("Timer: OFF");  // che do binh thuong
		while(1)
	{	
		 	time();
		
			gotoXY(0,4);
			sprintf(TEXT, "Phut= %d(m)", phut);
			LCDString(TEXT);
		
			gotoXY(0,5);
			sprintf(TEXT, "Gio= %d(h)", gio);
			LCDString(TEXT);
			// hen gio 
			if((GPIO_ReadInputDataBit(BT_PORT_A, BT_UP)==0))    // PA_6
			{ 		
			phut++;
			minute_now= minute;
			hour_now=hour;
			}
			
			if(phut >= 60){
					phut = phut - 60;
					gio++;
					if(gio == 24){
						gio =23;
					}
				}
			if(GPIO_ReadInputDataBit(BT_PORT_A,BT_DOWN)==0){	// PA_7
		  phut--;
			minute_now = minute;
			hour_now=hour;
			}
			if(phut <0){
					phut = 59;
					gio--;
				if(gio <0){
						gio = 0;
					}
				}
			delay_ms(250);
			
			if(phut!=0||gio!=0){
				gotoXY(0,3);
				LCDString("Timer: ON ");
			}
			minute_specific= minute_now + phut;
			hour_specific= hour_now + gio;
			if(minute_specific>=60){
				minute_specific=minute_specific - 60;
				hour_specific++;
			}
			if(hour_specific>=24){
				minute_specific=minute_specific - 24;
			}
			BUZZZZ();
			
			
}
}


