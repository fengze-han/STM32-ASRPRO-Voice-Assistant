#include "myiic.h"
#include "delay.h"
#include <math.h>
//////////////////////////////////////////////////////////////////////////////////	 
//舵机拓展板IIC  
//////////////////////////////////////////////////////////////////////////////////	
 
//初始化IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //í?íìê?3?
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	IIC_SCL=1;
	IIC_SDA=1;

}

void IIC_Start(void)
{
	SDA_OUT();     
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//?ˉ×?I2C×ü??￡?×?±?·￠?í?ò?óê?êy?Y 
}	  
//2úéúIICí￡?1D?o?
void IIC_Stop(void)
{
	SDA_OUT();//sda??ê?3?
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//·￠?íI2C×ü???áê?D?o?
	delay_us(4);							   	
}
//μè′yó|′eD?o?μ?à′
//·μ???μ￡o1￡??óê?ó|′eê§°ü
//        0￡??óê?ó|′e3é1|
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDAéè???aê?è?  
	IIC_SDA=1;delay_us(2);	   
	IIC_SCL=1;delay_us(2);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ê±?óê?3?0 	   
	return 0;  
} 
//2úéúACKó|′e
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//2?2úéúACKó|′e		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC·￠?íò???×??ú
//·μ??′ó?úóD?Tó|′e
//1￡?óDó|′e
//0￡??Tó|′e			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//à-μíê±?ó?aê?êy?Y′?ê?
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //??TEA5767?aèy???óê±??ê?±?D?μ?
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//?á1??×??ú￡?ack=1ê±￡?·￠?íACK￡?ack=0￡?·￠?ínACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDAéè???aê?è?
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//·￠?ínACK
    else
        IIC_Ack(); //·￠?íACK   
    return receive;
}



void PCA9685_Init(float hz,u8 angle)
{
	u32 off = 0;
	IIC_Init();
	PCA9685_Write(PCA_Model,0x00);
	PCA9685_setFreq(hz);
	off = (u32)(145+angle*2.4);
	PCA9685_setPWM(0,0,off);
	PCA9685_setPWM(1,0,off);
	PCA9685_setPWM(2,0,off);
	PCA9685_setPWM(3,0,off);
	PCA9685_setPWM(4,0,off);
	PCA9685_setPWM(5,0,off);
	PCA9685_setPWM(6,0,off);
	PCA9685_setPWM(7,0,off);
	PCA9685_setPWM(8,0,off);
	PCA9685_setPWM(9,0,off);
	PCA9685_setPWM(10,0,off);
	PCA9685_setPWM(11,0,off);
	PCA9685_setPWM(12,0,off);
	PCA9685_setPWM(13,0,off);
	PCA9685_setPWM(14,0,off);
	PCA9685_setPWM(15,0,off);

	delay_ms(100);
	
}

void PCA9685_Write(u8 addr,u8 data)
{
	IIC_Start();
	
	IIC_Send_Byte(PCA_Addr);
	IIC_NAck();
	
	IIC_Send_Byte(addr);
	IIC_NAck();
	
	IIC_Send_Byte(data);
	IIC_NAck();
	
	IIC_Stop();
	
	
}

u8 PCA9685_Read(u8 addr)
{
	u8 data;
	
	IIC_Start();
	
	IIC_Send_Byte(PCA_Addr);
	IIC_NAck();
	
	IIC_Send_Byte(addr);
	IIC_NAck();
	
	IIC_Stop();
	
	delay_us(10);

	
	IIC_Start();

	IIC_Send_Byte(PCA_Addr|0x01);
	IIC_NAck();
	
	data = IIC_Read_Byte(0);
	
	IIC_Stop();
	
	return data;
	
}

void PCA9685_setPWM(u8 num,u32 on,u32 off)
{
	IIC_Start();
	
	IIC_Send_Byte(PCA_Addr);
	IIC_Wait_Ack();
	
	IIC_Send_Byte(LED0_ON_L+4*num);
	IIC_Wait_Ack();
	
	IIC_Send_Byte(on&0xFF);
	IIC_Wait_Ack();
	
	IIC_Send_Byte(on>>8);
	IIC_Wait_Ack();
	
	IIC_Send_Byte(off&0xFF);
	IIC_Wait_Ack();
	
	IIC_Send_Byte(off>>8);
	IIC_Wait_Ack();
	
	IIC_Stop();
	
}

void PCA9685_setFreq(float freq)
{
	u8 prescale,oldmode,newmode;
	
	double prescaleval;
	
	//freq *= 0.92;
	prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;
	prescale = floor(prescaleval+0.5f);
	oldmode = PCA9685_Read(PCA_Model);
	
	newmode = (oldmode&0x7F)|0x10;
	PCA9685_Write(PCA_Model,newmode);
	PCA9685_Write(PCA_Pre,prescale);
	PCA9685_Write(PCA_Model,oldmode);
	delay_ms(5);
	PCA9685_Write(PCA_Model,oldmode|0xa1);
	
	
}

void setAngle(u8 num,u8 angle)
{
	u32 off = 0;
	off = (u32)(158+angle*2.2);
	PCA9685_setPWM(num,0,off);
}
























