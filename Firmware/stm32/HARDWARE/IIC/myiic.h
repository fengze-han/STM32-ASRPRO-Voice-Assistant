#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

//IO方向设置
#define SDA_IN()  {GPIOA->CRH&=0XFFFF0FFF;GPIOA->CRH|=8<<12;}
#define SDA_OUT() {GPIOA->CRH&=0XFFFF0FFF;GPIOA->CRH|=3<<12;}


//IO操作函数	 
#define IIC_SCL    PAout(12) 		//SCL
#define IIC_SDA    PAout(11) 		//SDA	 
#define READ_SDA   PAin(11) 	 		//输入SDA 

#define PCA_Addr 0x80
#define PCA_Model 0x00
#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09
#define PCA_Pre 0xFE

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  


void PCA9685_Init(float hz,u8 angle);

void PCA9685_Write(u8 addr,u8 data);

u8 PCA9685_Read(u8 addr);

void PCA9685_setPWM(u8 num,u32 on,u32 off);

void PCA9685_setFreq(float freq);

void setAngle(u8 num,u8 angle);


#endif
















