#include "led.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//LED≥ı ºªØ
//////////////////////////////////////////////////////////////////////////////////	
float Distance;

void LED_Init(void)
{
 
  GPIO_InitTypeDef GPIO_InitStructure;  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); 
}
 
void LED_MQ_3_ON(void)
{
  GPIO_SetBits(GPIOB,GPIO_Pin_13); 
}

void LED_MQ_3_OFF(void)
{
  GPIO_ResetBits(GPIOB,GPIO_Pin_13); 
}

void LED_MQ_2_ON(void)
{
  GPIO_SetBits(GPIOB,GPIO_Pin_14); 
}

void LED_MQ_2_OFF(void)
{
  GPIO_ResetBits(GPIOB,GPIO_Pin_14); 
}
void LED_SR_ON(void)
{
  GPIO_SetBits(GPIOB,GPIO_Pin_15); 
}

void LED_SR_OFF(void)
{
  GPIO_ResetBits(GPIOB,GPIO_Pin_15); 
}

