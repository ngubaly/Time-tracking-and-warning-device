#include "User_Function.h"
#include "stm32f10x_i2c.h"

void Init_I2C()
{
	GPIO_InitTypeDef GPIO_Structure;
	I2C_InitTypeDef I2C_Structure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	I2C_Structure.I2C_ClockSpeed=100000;
	I2C_Structure.I2C_Mode=I2C_Mode_I2C;
	I2C_Structure.I2C_DutyCycle=I2C_DutyCycle_2;
	I2C_Structure.I2C_OwnAddress1=0x00;
	I2C_Structure.I2C_Ack=I2C_Ack_Disable;
	I2C_Structure.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1,&I2C_Structure);
	I2C_Cmd(I2C1,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	GPIO_Structure.GPIO_Pin= GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Structure.GPIO_Speed= GPIO_Speed_2MHz;
	GPIO_Structure.GPIO_Mode= GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB,&GPIO_Structure);
}

void i2c_start()
{
	// Wait until I2Cx is not busy anymore
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	// Generate start condition
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// Wait for I2C EV5. 
	// It means that the start condition has been correctly released 
	// on the I2C bus (the bus is free, no other devices is communicating))
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
}

// Dung che do I2C
void i2c_stop()
{
	// Generate I2C stop condition
	I2C_GenerateSTOP(I2C1, ENABLE);
}


void i2c_address_direction(uint8_t address, uint8_t direction)
{
	// Send slave address
	I2C_Send7bitAddress(I2C1, address, direction);
	
	// Wait for I2C EV6
	// It means that a slave acknowledges his address
	if (direction == I2C_Direction_Transmitter)
	{
		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	}
	else if (direction == I2C_Direction_Receiver)
	{	
		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}
}

// chuyen doi 1 byte sang bus I2C(byte can chuyen)
void i2c_transmit(uint8_t byte)
{
	// Send data byte
	I2C_SendData(I2C1, byte);
	// Wait for I2C EV8_2.
	// It means that the data has been physically shifted out and 
	// output on the bus)
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

// Nhan byte du lieu tu bus I2C-> gia tri ACK
uint8_t i2c_receive_ack()
{
	// Enable ACK of received data
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	// Wait for I2C EV7
	// It means that the data has been received in I2C data register
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	// Read and return data byte from I2C data register
	return I2C_ReceiveData(I2C1);
}

// nhan gia byte du lieu tu I2C bus-> gia tri NACK
uint8_t i2c_receive_nack()
{
	// Disable ACK of received data
	I2C_AcknowledgeConfig(I2C1, DISABLE);
	// Wait for I2C EV7
	// It means that the data has been received in I2C data register
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	// Read and return data byte from I2C data register
	return I2C_ReceiveData(I2C1);
}

void i2c_write_no_reg(uint8_t address, uint8_t data)
{
	i2c_start();
	i2c_address_direction(address << 1, I2C_Direction_Transmitter);
	i2c_transmit(data);
	i2c_stop();
}

// viet byte vao slave su dung dia chi thanh ghi
// Slave device address (7-bit right aligned)
// Register address
// Data byte
void i2c_write_with_reg(uint8_t address, uint8_t reg, uint8_t data)
{
	i2c_start();
	i2c_address_direction(address << 1, I2C_Direction_Transmitter);
	i2c_transmit(reg);
	i2c_transmit(data);
	i2c_stop();
}

// viet nhieu byte vao slave ma k su dung dia chi thanh ghi
// Slave device address (7-bit right aligned)
// Pointer to data byte array
// Number of bytes to write
void i2c_write_multi_no_reg(uint8_t address, uint8_t* data, uint8_t len)
{
	int i;
	
	i2c_start();
	i2c_address_direction(address << 1, I2C_Direction_Transmitter);
	for (i = 0; i < len; i++)
	{
		i2c_transmit(data[i]);
	}
	i2c_stop();
}

// viet nhieu byte vao slave su dung dia chi thanh ghi
// Slave device address (7-bit right aligned)
// Register address where to start write
// Pointer to data byte array
// Number of bytes to write
void i2c_write_multi_with_reg(uint8_t address, uint8_t reg, uint8_t* data, uint8_t len)
{
	int i;
	
	i2c_start();
	i2c_address_direction(address << 1, I2C_Direction_Transmitter);
	i2c_transmit(reg);
	for (i = 0; i < len; i++)
	{
		i2c_transmit(data[i]);
	}
	i2c_stop();
}

// doc byte tu slave khong su dung dia chi thanh ghi
// Slave device address (7-bit right aligned)
// Pointer to data byte to store data from slave
void i2c_read_no_reg(uint8_t address, uint8_t* data)
{
	i2c_start();
	i2c_address_direction(address << 1, I2C_Direction_Receiver);
	*data = i2c_receive_nack();
	i2c_stop();
}

// doc byte tu slave voi dia chi thanh ghi
// Slave device address (7-bit right aligned)
// Register address
// Pointer to data byte to store data from slave
void i2c_read_with_reg(uint8_t address, uint8_t reg, uint8_t* data)
{
	i2c_start();
	i2c_address_direction(address << 1, I2C_Direction_Transmitter);
	i2c_transmit(reg);
	i2c_stop();
	i2c_start();
	i2c_address_direction(address << 1, I2C_Direction_Receiver);
	*data = i2c_receive_nack();
	i2c_stop();
}

/// Doc nhieu byte ma khong can chi dinh dia chi thanh ghi
// Slave device address (7-bit right aligned)
// Number of data bytes to read from slave
// Pointer to data array byte to store data from slave    */
void i2c_read_multi_no_reg(uint8_t address, uint8_t len, uint8_t* data)
{
	int i;
	
	i2c_start();
	i2c_address_direction(address << 1, I2C_Direction_Receiver);
	for (i = 0; i < len; i++)
	{
		if (i == (len - 1))
		{
			data[i] = i2c_receive_nack();
		}
		else
		{
			data[i] = i2c_receive_ack();
		}
	}
	i2c_stop();
}

// Doc nhieu byte  du lieu tu dia chi thanh ghi()
//Slave device address (7-bit right aligned)
//Register address
//Number of data bytes to read from slave
// Pointer to data array byte to store data from slave
void i2c_read_multi_with_reg(uint8_t address, uint8_t reg, uint8_t len, uint8_t* data)
{
	int i;
	
	i2c_start();
	i2c_address_direction(address << 1, I2C_Direction_Transmitter);
	i2c_transmit(reg);
	i2c_stop();
	i2c_start();
	i2c_address_direction(address << 1, I2C_Direction_Receiver);
	for (i = 0; i < len; i++)
	{
		if (i == (len - 1))
		{
			data[i] = i2c_receive_nack();
		}
		else
		{
			data[i] = i2c_receive_ack();
		}
	}
	i2c_stop();
}


/**********************************************/
void InitGPIO(GPIO_TypeDef *GPIOx,uint32_t RCC_APB2Periph_x,uint16_t GPIO_Pin_x,uint8_t GPIO_Mode){
	GPIO_InitTypeDef GPIO_Structure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_x,ENABLE);
	GPIO_Structure.GPIO_Pin= GPIO_Pin_x;
	GPIO_Structure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Structure.GPIO_Mode= GPIO_Mode;
	GPIO_Init(GPIOx,&GPIO_Structure);
}
void Init_GPIO(uint32_t RCC_APB2Periph, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode )
{
	GPIO_InitTypeDef GPIO_Structure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph,ENABLE);		// Clock
	
	GPIO_Structure.GPIO_Pin 	= GPIO_Pin;							// Pin
	GPIO_Structure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Structure.GPIO_Mode	= GPIO_Mode; 						// Mode
	
	GPIO_Init(GPIOx, &GPIO_Structure); 								// PORT
	
	GPIO_SetBits(GPIOx, GPIO_Pin);										// Gia tri ban dau
	
}

