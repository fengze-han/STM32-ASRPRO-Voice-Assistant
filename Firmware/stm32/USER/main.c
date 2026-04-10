#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	 
#include "time.h"
#include "oled.h"
#include "beep.h"
#include "SR602.h"
#include "dht11.h"
#include "MOTOR.h"
#include "ADCM.h"

int i=0;
uint8_t g_person_detected = 0;
u8 string[30] = {0},string1[30] = {0};
float ADC_ConvertedValueLocal[NOFCHANEL];   
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];


void Use_SR602(void)
{
			if(g_person_detected==1)
			{
				LED_SR_ON();
			}
			else
			{
				LED_SR_OFF();
			}
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==1)
			{     
				
					//BEEP_ON();
				g_person_detected=1;
       
					LED_SR_ON();
			}
				else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0)
				{
					//LED_SR_OFF();
					g_person_detected=0;
						//BEEP_OFF();
				}
}

void Use_DHT11(void)
{		
		DHT11_rec_data();//dht11初始化
	OLED_ShowChinese(0, 16, 0, 12, 1);
	OLED_ShowChinese(12, 16, 1, 12, 1);
	
	sprintf((char *)string,":%d.",dat[0]);//温度整数
	
	  OLED_ShowString(26,16,string,12,1);
		OLED_ShowNum(49,16,dat[1],2,12,1);//温度小数
	OLED_ShowChinese(62, 16, 7, 12, 1);
		//OLED_DrawPoint(51,29,1);//小数点
	OLED_ShowChinese(0, 28, 2, 12, 1);
	OLED_ShowChinese(12, 28, 1, 12, 1);
	
	sprintf((char *)string,":%d.",dat[2]);//湿度整数
		OLED_ShowString(26,28,string,12,1);
		OLED_ShowNum(49,28,dat[3],2,12,1);//湿度小数
	OLED_ShowChar(61,28,'%',12,1);
	OLED_ShowChar(67,28,'R',12,1);
	OLED_ShowChar(73,28,'H',12,1);
		//OLED_DrawPoint(69,30,1);
}

void Use_ASRPRO(void)	
{
				OLED_ShowChinese(82, 16, 3, 12, 1);
				OLED_ShowChinese(94, 16, 4, 12, 1);
				sprintf((char *)string,":");
				//sprintf((char *)string,":%d",fan);//显示接收到的数据//风扇开启状态，0—>>关；1—>>开
				OLED_ShowString(105,17,string,12,1);
				if(fan==1)
					{
						OLED_ShowChinese(115, 16, 5, 12, 1);
						Motor_ZHENG();
						TIM_SetCompare3(TIM3,1000);
					}
					else if(fan==0)
					{
						OLED_ShowChinese(115, 16, 6, 12, 1);
						Motor_OFF();
					}
}
			
void Use_MQ_3(void)
{				
				ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]*125/4095;
	//ADC_ConvertedValue[0]=ADC_ConvertedValue[0]-3;
	//ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/2.778;
	   OLED_ShowChinese(0, 40, 8, 12, 1);
	   OLED_ShowChinese(12, 40, 9, 12, 1);
	  // OLED_ShowChinese(24, 40, 12, 12, 1);
	
        sprintf((char *)string,"MQ3:%f",ADC_ConvertedValueLocal[0]);
				OLED_ShowString(24,40,string,12,1);			
					if(ADC_ConvertedValueLocal[0]>100)
					{
						Serial_SendByte(0xAA);
						Serial_SendByte(0x00);
						Serial_SendByte(0x01);
						LED_MQ_3_ON();
						BEEP_ON();
						delay_ms(1000);
					}
					else if(ADC_ConvertedValueLocal[0]<100)
					{
						BEEP_OFF();
						LED_MQ_3_OFF();

					}
}
void Use_MQ_2(void)
{
				ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]*99/4096;
	  OLED_ShowChinese(0, 50, 10, 12, 1);
	OLED_ShowChinese(12, 50, 11, 12, 1);
	//OLED_ShowChinese(24, 50, 12, 12, 1);
        sprintf((char *)string,"MQ2:%f",ADC_ConvertedValueLocal[1]);
				OLED_ShowString(24,50,string,12,1);			
					if(ADC_ConvertedValueLocal[1]>100)
					{
						Serial_SendByte(0xAA);
						Serial_SendByte(0x00);
						Serial_SendByte(0x02);
						LED_MQ_2_ON();
						BEEP_ON();
						delay_ms(1000);
					}
					else if(ADC_ConvertedValueLocal[1]<100)
					{
						BEEP_OFF();
						LED_MQ_2_OFF();			
					}
}
void TiMu(void)
{
	int q=0;
	for (int i = 12; i <=19; i++) {
		q=(i-12)*12+18;
    OLED_ShowChinese(q, 3, i, 12, 1);
}
}

 int main(void)
{	 	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先
		delay_init();//延时函数初始化	
	  uart_init(115200);//串口2
	
		LED_Init();
	
		OLED_Init();//oled显示屏初始化
		OLED_ColorTurn(0); //0正常显示，1 反色显示
		OLED_DisplayTurn(0); //屏幕旋转180度调整
		
		BEEP_Init();//蜂鸣器初始化
		SR602_Init();//人体感应初始化
		TiMu();
		TIM3_PWM_Init(999,71);//定时器3初始化
		Motor_AIN();//风扇I/O初始化
		ADCx_Init();//ADC通道初始化
	
	 while(1)
	 {	
		  
        
        
     
				OLED_Refresh();//oled刷新
				Use_SR602();
				Use_DHT11();
				Use_ASRPRO();
		 
				Use_MQ_3();			
				Use_MQ_2();
	 }
}	

