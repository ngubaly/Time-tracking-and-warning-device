#include "main.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "User_function.h"
#include "stm32f10x_exti.h"
int main()
{
	InitButton1();
	InitButton2();
	InitLedA();
	InitLedB();
	EXTI9_5_IRQHandler();
	Init_Timer_2();
	InitButton3();
	TIM2_IRQHandler();
	while(1){
		
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)){
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	} 
	else{
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	} 
	}
	}
	
