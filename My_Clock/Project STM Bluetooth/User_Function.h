#ifndef USER_FUNCTION
#define USER_FUNCTION
#include "stm32f10x.h"

#define EN_PIN GPIO_Pin_8
#define RS_PIN GPIO_Pin_9

#define D4_PIN GPIO_Pin_15
#define D5_PIN GPIO_Pin_14
#define D6_PIN GPIO_Pin_13
#define D7_PIN GPIO_Pin_12
#define LED_CLOCK_A RCC_APB2Periph_GPIOA
#define LED_CLOCK_B RCC_APB2Periph_GPIOB
#define BUZZ_CLOCK	RCC_APB2Periph_GPIOA

#define BT_CLOCK_A	RCC_APB2Periph_GPIOA
#define BT_CLOCK_B	RCC_APB2Periph_GPIOB

// PORT
#define LED_PORT_A	GPIOA					
#define LED_PORT_B	GPIOB
#define BUZZ_PORT		GPIOA

#define BT_PORT_A		GPIOA
#define BT_PORT_B		GPIOB

// Pin
#define LED_1				GPIO_Pin_5			// PB5
#define LED_2				GPIO_Pin_12			// PA11
#define LED_3				GPIO_Pin_11			// PA12
#define LED_4				GPIO_Pin_8			// PB8
#define BUZZ				GPIO_Pin_4			// PA4

#define BT_UP				GPIO_Pin_3			// PA6
#define BT_CENTER		GPIO_Pin_7			// PA7
#define BT_DOWN			GPIO_Pin_8			// PA8
#define BT_RIGHT		GPIO_Pin_2			// PB2			
#define BT_LEFT			GPIO_Pin_3			// PB3			
#define BT_MODE			GPIO_Pin_4			// PB4	

// Mode
#define OUTPUT			GPIO_Mode_Out_PP
#define INPUT				GPIO_Mode_IN_FLOATING
void InitGPIO(GPIO_TypeDef *GPIOx,uint32_t RCC_APB2Periph_x,uint16_t GPIO_Pin_x,uint8_t GPIO_Mode);
void Init_GPIO(uint32_t RCC_APB2Periph, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode );
void Init_I2C();
void i2c_start();
void i2c_stop();
void i2c_address_direction(uint8_t address, uint8_t direction);
void i2c_transmit(uint8_t byte);
uint8_t i2c_receive_ack();
uint8_t i2c_receive_nack();
void i2c_write_no_reg(uint8_t address, uint8_t data);
void i2c_write_with_reg(uint8_t address, uint8_t reg, uint8_t data);
void i2c_write_multi_no_reg(uint8_t address, uint8_t* data, uint8_t len);
void i2c_write_multi_with_reg(uint8_t address, uint8_t reg, uint8_t* data, uint8_t len);
void i2c_read_no_reg(uint8_t address, uint8_t* data);
void i2c_read_with_reg(uint8_t address, uint8_t reg, uint8_t* data);
void i2c_read_multi_no_reg(uint8_t address, uint8_t len, uint8_t* data);
void i2c_read_multi_with_reg(uint8_t address, uint8_t reg, uint8_t len, uint8_t* data);

#endif