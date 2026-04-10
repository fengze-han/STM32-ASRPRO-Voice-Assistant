#include "adc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//STM32C8T6开发板
//ADC单通道初始化   
//闲鱼关注：强哥电子；CSDN：Dandelion701：B站：Dandelion701
//修改日期:2024.1.17
//////////////////////////////////////////////////////////////////////////////////	
u16 Value[2]={0,0};
void ADC_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1 | RCC_APB2Periph_AFIO, ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // 72/6=12

    GPIO_InitStructure.GPIO_Pin = ADC1_Pin | ADC2_Pin; // 添加ADC2_Pin作为通道1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // 模拟输入
    GPIO_Init(ADC_PROT, &GPIO_InitStructure);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; // 独立模式
    ADC_InitStructure.ADC_ScanConvMode = ENABLE; // 启用扫描模式，用于多通道
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; // 连续转换
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件触发方式
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 2; // 两个通道
    ADC_Init(ADC1, &ADC_InitStructure);
    ADC_ClearFlag(ADC1, ADC_FLAG_EOC); // 清除中断标志位
    ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE); // 启用中断
    // 配置通道0和通道1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);
    ADC_Cmd(ADC1, ENABLE);
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetSoftwareStartConvStatus(ADC1));
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
float ADCx_MQ_3(void)
{
	float Temp = 0;
	for(u8 i=0;i<10;i++){
			Temp +=Value;
	}
	Temp/=10;//10次平均值
	return Temp * 125/4095;
}

float ADCx_MQ_2(void)
{
	float Temp = 0;
	for(u8 i=0;i<10;i++){
			Temp +=Value;
	}
	Temp/=10;//10次平均值
	return Temp * 99/4096;
}

void ADC1_2_IRQHandler(void){

	if(ADC_GetITStatus(ADC1,ADC_IT_EOC) !=RESET){
	
		Value = ADC_GetConversionValue(ADC1);
		
		ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);//清空中断标志位
	
	}
}




