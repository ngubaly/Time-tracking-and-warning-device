#ifndef __I2C
#define __I2C
#define SCL GPIO_Pin_6
#define SDA GPIO_Pin_7
void I2C_Start();
void I2C_Stop();
unsigned char I2C_Write(unsigned char Data);
unsigned char I2C_Read(void);
#endif