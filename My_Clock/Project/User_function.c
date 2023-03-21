#include "User_function.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"
void Initial_GPIO(void)
{
	GPIO_InitTypeDef LED_Structure;
	GPIO_InitTypeDef LED_Structure_Relay;
	
	RCC_APB2PeriphClockCmd(LED_Clock, ENABLE); //Bat Clock cho PortB
	RCC_APB2PeriphClockCmd(LED_Clock_Relay, ENABLE); //Bat Clock cho PortA
	
	LED_Structure.GPIO_Pin		= 		LED_Pin;
	LED_Structure.GPIO_Speed	= 		GPIO_Speed_50MHz;
	LED_Structure.GPIO_Mode		= 		GPIO_Mode_Out_PP; // Che do Output Pushpull
	
	GPIO_Init(LED_PORT, &LED_Structure); 
	
	LED_Structure_Relay.GPIO_Pin	= 		LED_Pin_1|LED_Pin_2;
	LED_Structure_Relay.GPIO_Speed= 		GPIO_Speed_50MHz;
	LED_Structure_Relay.GPIO_Mode	= 		GPIO_Mode_Out_PP;
	
	GPIO_Init(LED_PORT_RELAY, &LED_Structure_Relay); 
	//Set gia tri chan so 0 o Port B =1, PB0=1 de tat LED
	GPIO_SetBits(LED_PORT, LED_Pin);	
	
	GPIO_SetBits(LED_PORT_RELAY, LED_Pin_1|LED_Pin_2);	
}
void InitButton1(void){
GPIO_InitTypeDef GPIO_Structure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
GPIO_Structure.GPIO_Pin=GPIO_Pin_6;
GPIO_Structure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Structure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
GPIO_Init(GPIOA,&GPIO_Structure);
}
void InitLedA(void){
GPIO_InitTypeDef GPIO_Structure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
GPIO_Structure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_4;
GPIO_Structure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Structure.GPIO_Mode=GPIO_Mode_Out_PP;
GPIO_Init(GPIOA,&GPIO_Structure);
}
void InitLedB(void){
GPIO_InitTypeDef GPIO_Structure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
GPIO_Structure.GPIO_Pin=GPIO_Pin_0;
GPIO_Structure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Structure.GPIO_Mode=GPIO_Mode_Out_PP;
GPIO_Init(GPIOB,&GPIO_Structure);
}
void InitButton2(void){
NVIC_InitTypeDef NVIC_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
GPIO_InitTypeDef GPIO_Structure;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
GPIO_Structure.GPIO_Pin=GPIO_Pin_7;
GPIO_Structure.GPIO_Mode=GPIO_Mode_IPU;
GPIO_Init(GPIOA,&GPIO_Structure);
GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);

EXTI_InitStructure.EXTI_Line=EXTI_Line7;
EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
EXTI_InitStructure.EXTI_LineCmd=ENABLE;
EXTI_Init(&EXTI_InitStructure);
	
NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 15;
NVIC_InitStructure.NVIC_IRQChannelSubPriority= 15;
NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
NVIC_Init(&NVIC_InitStructure);
}
void EXTI9_5_IRQHandler(void){
 static int t=10000000;
	if(EXTI_GetITStatus(EXTI_Line7)==1)
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	while(t--);
EXTI_ClearITPendingBit(EXTI_Line7);
}
void Init_Timer_2(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM2_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM2_TimeBaseStructure.TIM_Prescaler = 35; // frequency = 1000000
	TIM2_TimeBaseStructure.TIM_Period = 1000 - 1;
	TIM2_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM2_TimeBaseStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);   
}
void InitButton3(void){
GPIO_InitTypeDef GPIO_Structure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
GPIO_Structure.GPIO_Pin=GPIO_Pin_8;
GPIO_Structure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Structure.GPIO_Mode=GPIO_Mode_IPU;
GPIO_Init(GPIOA,&GPIO_Structure);
	}
void TIM2_IRQHandler(void){
	static uint32_t time=1000;
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET){
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8))
			while(time--) GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

