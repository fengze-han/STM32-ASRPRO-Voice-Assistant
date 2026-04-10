#ifndef __ADC_H
#define __ADC_H

#include "sys.h"
#include "delay.h"
#include "stdio.h"
extern u16 Value[2]={0,0};
#define ADC1_Pin GPIO_Pin_0//MQ-3¾Æ¾«
#define ADC2_Pin GPIO_Pin_1//MQ-2ÑÌÎí
#define ADC_PROT GPIOA

void ADC_GPIO_Init(void);
float ADCx_MQ_3(void);
float ADCx_MQ_2(void);

#endif
