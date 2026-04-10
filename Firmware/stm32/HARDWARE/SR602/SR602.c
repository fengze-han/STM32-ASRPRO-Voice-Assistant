#include "stm32f10x.h"
#include "SR602.h"
#include "sys.h" 
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//人体感应模块初始化 
//////////////////////////////////////////////////////////////////////////////////	
void SR602_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_10; 
	GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);
		
}
void SR602_ON(void)
{
GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==1;
}

void SR602_OFF(void)
{
GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0;
}
