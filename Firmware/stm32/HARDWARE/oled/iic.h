#ifndef __IIC_H
#define __IIC_H
#include "sys.h"

/****************
注意：模拟IIC时，任意IO口（除JTAG口外，都可以做SDA和SCL）
****************/
#define OLED_SCL_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_8)//SCL
#define OLED_SCL_Set() GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_9)//SDA
#define OLED_SDA_Set() GPIO_SetBits(GPIOB,GPIO_Pin_9)

void IIC_delay(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(u8 dat);

#endif
