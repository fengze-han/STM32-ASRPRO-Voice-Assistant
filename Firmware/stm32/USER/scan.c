#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "24cxx.h"
#include "w25qxx.h"
#include "touch.h"
#include "time.h"
#include "myiic.h"
#include "imu_data_decode.h"
#include "packet.h"
#include "stm32f10x_it.h" 
#include "pid.h"
#include "scan.h"

u8 strin[30] = {0};
void MOD1_int(void)
{
	LCD_Clear(WHITE);//清屏
	while(1)
 {
	  while(1)
		{	
		LCD_ShowString(0,0,200,16,16,"Mode one:Normal freight mode");	 
		LCD_ShowString(0,24,200,12,12,"How much cargo");	
		LCD_ShowString(20,50,200,24,24,"1"); LCD_ShowString(20,90,200,24,24,"2");
		LCD_DrawRectangle(0, 40, 60, 80);	LCD_DrawRectangle(0, 80, 60, 120);	
		tp_dev.scan(0);	
		if(tp_dev.sta&TP_PRES_DOWN)
		{
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){cargo_num=1;delay_ms(1000);LCD_Clear(WHITE);break;}
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){cargo_num=2;delay_ms(1000);LCD_Clear(WHITE);break;}	
		}
	  } 			
		while(1)
	{
		if(cargo_num==1)
		{
		LCD_ShowString(0,0,200,16,16,"Mode one:Normal freight mode");
    LCD_ShowString(0,24,200,12,12,"Please select a location");	 		
    LCD_ShowString(20,50,200,24,24,"1"); LCD_ShowString(80,50,200,24,24,"2"); LCD_ShowString(140,50,200,24,24,"3");LCD_ShowString(200,50,200,24,24,"4");
    LCD_ShowString(20,90,200,24,24,"5"); LCD_ShowString(80,90,200,24,24,"6"); LCD_ShowString(140,90,200,24,24,"7");LCD_ShowString(200,90,200,24,24,"8");			
		LCD_DrawRectangle(0, 40, 60, 80);	LCD_DrawRectangle(60, 40, 120, 80);	LCD_DrawRectangle(120, 40, 180, 80);	LCD_DrawRectangle(180, 40, 240, 80);
		LCD_DrawRectangle(0, 80, 60, 120);	LCD_DrawRectangle(60, 80, 120, 120);	LCD_DrawRectangle(120, 80, 180, 120);	LCD_DrawRectangle(180, 80, 240, 120);
	  tp_dev.scan(0);	
		if(tp_dev.sta&TP_PRES_DOWN)
		{			
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=1;delay_ms(1000);break;}
		if((tp_dev.x[0]>60&&tp_dev.x[0]<120)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=2;delay_ms(1000);break;}
		if((tp_dev.x[0]>120&&tp_dev.x[0]<180)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=3;delay_ms(1000);break;}
		if((tp_dev.x[0]>180&&tp_dev.x[0]<240)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=4;delay_ms(1000);break;}
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=5;delay_ms(1000);break;}
		if((tp_dev.x[0]>60&&tp_dev.x[0]<120)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=6;delay_ms(1000);break;}
		if((tp_dev.x[0]>120&&tp_dev.x[0]<180)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=7;delay_ms(1000);break;}
		if((tp_dev.x[0]>180&&tp_dev.x[0]<240)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=8;delay_ms(1000);break;}
		}
	  }
		 else
		if(cargo_num==2&&choose_num1==0)
	{

		LCD_ShowString(0,0,200,16,16,"Mode one:Normal freight mode");
    LCD_ShowString(0,24,200,12,12,"Please select the 1st location");	 		
    LCD_ShowString(20,50,200,24,24,"1"); LCD_ShowString(80,50,200,24,24,"2"); LCD_ShowString(140,50,200,24,24,"3");LCD_ShowString(200,50,200,24,24,"4");
    LCD_ShowString(20,90,200,24,24,"5"); LCD_ShowString(80,90,200,24,24,"6"); LCD_ShowString(140,90,200,24,24,"7");LCD_ShowString(200,90,200,24,24,"8");			
		LCD_DrawRectangle(0, 40, 60, 80);	LCD_DrawRectangle(60, 40, 120, 80);	LCD_DrawRectangle(120, 40, 180, 80);	LCD_DrawRectangle(180, 40, 240, 80);
		LCD_DrawRectangle(0, 80, 60, 120);	LCD_DrawRectangle(60, 80, 120, 120);	LCD_DrawRectangle(120, 80, 180, 120);	LCD_DrawRectangle(180, 80, 240, 120);
		tp_dev.scan(0);
		if(tp_dev.sta&TP_PRES_DOWN)
		{		
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=1;delay_ms(1000);LCD_Clear(WHITE);}
		if((tp_dev.x[0]>60&&tp_dev.x[0]<120)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=2;delay_ms(1000);LCD_Clear(WHITE);}
		if((tp_dev.x[0]>120&&tp_dev.x[0]<180)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=3;delay_ms(1000);LCD_Clear(WHITE);}
		if((tp_dev.x[0]>180&&tp_dev.x[0]<240)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=4;delay_ms(1000);LCD_Clear(WHITE);}
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=5;delay_ms(1000);LCD_Clear(WHITE);}
		if((tp_dev.x[0]>60&&tp_dev.x[0]<120)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=6;delay_ms(1000);LCD_Clear(WHITE);}
		if((tp_dev.x[0]>120&&tp_dev.x[0]<180)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=7;delay_ms(1000);LCD_Clear(WHITE);}
		if((tp_dev.x[0]>180&&tp_dev.x[0]<240)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=8;delay_ms(1000);LCD_Clear(WHITE);}		
		}
		}
	    if(choose_num1!=0)
		{
	
		LCD_ShowString(0,0,200,16,16,"Mode one:Normal freight mode");
    LCD_ShowString(0,24,200,12,12,"Please select the 2st location");
		LCD_ShowString(20,50,200,24,24,"1"); LCD_ShowString(80,50,200,24,24,"2"); LCD_ShowString(140,50,200,24,24,"3");LCD_ShowString(200,50,200,24,24,"4");
    LCD_ShowString(20,90,200,24,24,"5"); LCD_ShowString(80,90,200,24,24,"6"); LCD_ShowString(140,90,200,24,24,"7");LCD_ShowString(200,90,200,24,24,"8");			
		LCD_DrawRectangle(0, 40, 60, 80);	LCD_DrawRectangle(60, 40, 120, 80);	LCD_DrawRectangle(120, 40, 180, 80);	LCD_DrawRectangle(180, 40, 240, 80);
		LCD_DrawRectangle(0, 80, 60, 120);	LCD_DrawRectangle(60, 80, 120, 120);	LCD_DrawRectangle(120, 80, 180, 120);	LCD_DrawRectangle(180, 80, 240, 120);
		tp_dev.scan(0);
			if(tp_dev.sta&TP_PRES_DOWN)
		{		
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num2=1;delay_ms(1000);break;}
		if((tp_dev.x[0]>60&&tp_dev.x[0]<120)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num2=2;delay_ms(1000);break;}
		if((tp_dev.x[0]>120&&tp_dev.x[0]<180)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num2=3;delay_ms(1000);break;}
		if((tp_dev.x[0]>180&&tp_dev.x[0]<240)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num2=4;delay_ms(1000);break;}
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num2=5;delay_ms(1000);break;}
		if((tp_dev.x[0]>60&&tp_dev.x[0]<120)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num2=6;delay_ms(1000);break;}
		if((tp_dev.x[0]>120&&tp_dev.x[0]<180)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num2=7;delay_ms(1000);break;}
		if((tp_dev.x[0]>180&&tp_dev.x[0]<240)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num2=8;delay_ms(1000);break;}	
	}		
			}
			
	}	
///////////////////////////////////////////////////////////////////////////////
	  PCA9685_Init(50,90);//PA 11sda 12scl舵机		
	  setAngle(YTXZ,100);		
	  setAngle(YTFY,155);
	  USART3_int();//串口3pb10 11 opemmv 02
	for(int i=0;i<5;i++)
		{
	  USART_SendData(USART3,0x0d);
	  while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);
	  USART_SendData(USART3,cargo_num);
	  while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);
		USART_SendData(USART3,choose_num1);
	  while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);
		USART_SendData(USART3,choose_num2);
	  while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);
		USART_SendData(USART3,0x5b);
	  while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);
		}
///////////////////////////////////////////////////////////////////////////////		
		LED_Init();//IO初始化：PG6.7货物输入，PF12.13.14.15输出（12左，13右，14炮，15风扇）	
		LCD_Init();	//pb0,pd014589 10 14 15 pe78910 11 12 13 14 15 pg0 12
		tp_dev.init();//触屏		
    LCD_ShowString(0,0,200,16,16,"Mode one:Normal freight mode");	
//////////////////////////////////////////////////
	if(cargo_num==1)
	{
		GPIO_SetBits(Rightlight);
    LCD_ShowString(0,24,200,12,12,"put it at green light");
		while(1)
		{
			if(GPIO_ReadInputDataBit(Rightbox))
			{
				GPIO_ResetBits(Rightlight);
				LCD_ShowString(0,24,200,12,12,"Thank you");
				break;
			}
		}
	}
		if(cargo_num==2)
	{
		GPIO_SetBits(Rightlight);
    LCD_ShowString(0,24,200,12,12,"put 1st at green light");
		while(1)
		{
			if(GPIO_ReadInputDataBit(Rightbox))
			{
				GPIO_ResetBits(Rightlight);
				LCD_ShowString(0,24,200,12,12,"Thank you");
				break;
			}
		}
		GPIO_SetBits(Leftlight);
		LCD_ShowString(0,24,200,12,12,"put 2st at Red light");
		while(1)
		{
			if(GPIO_ReadInputDataBit(Leftbox))
			{
				GPIO_ResetBits(Leftlight);
				LCD_ShowString(0,24,200,12,12,"Thank you");
				LCD_Clear(WHITE);
				break;
			}
		}	
	}
    
	  break;
    }
    USART2_Init(115200);//pa23陀螺仪 	  03   
		TIM4_PWM_Init(999,71);//pa 8 11电机 
		Wave_SRD_Init();//超声波初始化pe 46	
		Timer2_SRD_Init(9999,7199);//超声波定时
		Motor_12_Config();//电机控制pf891011
		imu_data_decode_init(); //映射解析函数	  
		TIM5_Getsample_Int(4999,719);//程序中断定时器50ms01
		//TIM3_Getsample_Int(9999, 719);//超声波中断100ms10   超声波00	
}



void MOD2_int(void)
{
	LCD_Clear(WHITE);//清屏
	while(1)
 {
	  while(1)
		{	
		LCD_ShowString(0,0,200,16,16,"Mode two");	 
		LCD_ShowString(0,24,200,12,12,"How much cargo");	
		LCD_ShowString(20,50,200,24,24,"1"); LCD_ShowString(20,90,200,24,24,"2");
		LCD_DrawRectangle(0, 40, 60, 80);	LCD_DrawRectangle(0, 80, 60, 120);	
		tp_dev.scan(0);	
		if(tp_dev.sta&TP_PRES_DOWN)
		{
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){cargo_num=1;delay_ms(1000);LCD_Clear(WHITE);break;}
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){cargo_num=2;delay_ms(1000);LCD_Clear(WHITE);break;}	
		}
	  } 			
		while(1)
	{
		if(cargo_num==1)
		{
		LCD_ShowString(0,0,200,16,16,"Mode two");
    LCD_ShowString(0,24,200,12,12,"Please select a location");	 		
    LCD_ShowString(20,50,200,24,24,"1"); LCD_ShowString(80,50,200,24,24,"2"); LCD_ShowString(140,50,200,24,24,"3");LCD_ShowString(200,50,200,24,24,"4");
    LCD_ShowString(20,90,200,24,24,"5"); LCD_ShowString(80,90,200,24,24,"6"); LCD_ShowString(140,90,200,24,24,"7");LCD_ShowString(200,90,200,24,24,"8");			
		LCD_DrawRectangle(0, 40, 60, 80);	LCD_DrawRectangle(60, 40, 120, 80);	LCD_DrawRectangle(120, 40, 180, 80);	LCD_DrawRectangle(180, 40, 240, 80);
		LCD_DrawRectangle(0, 80, 60, 120);	LCD_DrawRectangle(60, 80, 120, 120);	LCD_DrawRectangle(120, 80, 180, 120);	LCD_DrawRectangle(180, 80, 240, 120);
	  tp_dev.scan(0);	
		if(tp_dev.sta&TP_PRES_DOWN)
		{			
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=1;delay_ms(1000);break;}
		if((tp_dev.x[0]>60&&tp_dev.x[0]<120)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=2;delay_ms(1000);break;}
		if((tp_dev.x[0]>120&&tp_dev.x[0]<180)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=3;delay_ms(1000);break;}
		if((tp_dev.x[0]>180&&tp_dev.x[0]<240)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=4;delay_ms(1000);break;}
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=5;delay_ms(1000);break;}
		if((tp_dev.x[0]>60&&tp_dev.x[0]<120)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=6;delay_ms(1000);break;}
		if((tp_dev.x[0]>120&&tp_dev.x[0]<180)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=7;delay_ms(1000);break;}
		if((tp_dev.x[0]>180&&tp_dev.x[0]<240)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=8;delay_ms(1000);break;}
		}
	  }
		 else
		if(cargo_num==2&&choose_num1==0)
	{

		LCD_ShowString(0,0,200,16,16,"Mode two");
    LCD_ShowString(0,24,200,12,12,"Please select the 1st location");	 		
    LCD_ShowString(20,50,200,24,24,"1"); LCD_ShowString(80,50,200,24,24,"2"); LCD_ShowString(140,50,200,24,24,"3");LCD_ShowString(200,50,200,24,24,"4");
    LCD_ShowString(20,90,200,24,24,"5"); LCD_ShowString(80,90,200,24,24,"6"); LCD_ShowString(140,90,200,24,24,"7");LCD_ShowString(200,90,200,24,24,"8");			
		LCD_DrawRectangle(0, 40, 60, 80);	LCD_DrawRectangle(60, 40, 120, 80);	LCD_DrawRectangle(120, 40, 180, 80);	LCD_DrawRectangle(180, 40, 240, 80);
		LCD_DrawRectangle(0, 80, 60, 120);	LCD_DrawRectangle(60, 80, 120, 120);	LCD_DrawRectangle(120, 80, 180, 120);	LCD_DrawRectangle(180, 80, 240, 120);
		tp_dev.scan(0);
		if(tp_dev.sta&TP_PRES_DOWN)
		{		
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=1;delay_ms(1000);LCD_Clear(WHITE);}
		if((tp_dev.x[0]>60&&tp_dev.x[0]<120)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=2;delay_ms(1000);LCD_Clear(WHITE);}
		if((tp_dev.x[0]>120&&tp_dev.x[0]<180)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=3;delay_ms(1000);LCD_Clear(WHITE);}
		if((tp_dev.x[0]>180&&tp_dev.x[0]<240)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num1=4;delay_ms(1000);LCD_Clear(WHITE);}
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=5;delay_ms(1000);LCD_Clear(WHITE);}
		if((tp_dev.x[0]>60&&tp_dev.x[0]<120)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=6;delay_ms(1000);LCD_Clear(WHITE);}
		if((tp_dev.x[0]>120&&tp_dev.x[0]<180)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=7;delay_ms(1000);LCD_Clear(WHITE);}
		if((tp_dev.x[0]>180&&tp_dev.x[0]<240)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num1=8;delay_ms(1000);LCD_Clear(WHITE);}		
		}
		}
	    if(choose_num1!=0)
		{
	
		LCD_ShowString(0,0,200,16,16,"Mode two");
    LCD_ShowString(0,24,200,12,12,"Please select the 2st location");
		LCD_ShowString(20,50,200,24,24,"1"); LCD_ShowString(80,50,200,24,24,"2"); LCD_ShowString(140,50,200,24,24,"3");LCD_ShowString(200,50,200,24,24,"4");
    LCD_ShowString(20,90,200,24,24,"5"); LCD_ShowString(80,90,200,24,24,"6"); LCD_ShowString(140,90,200,24,24,"7");LCD_ShowString(200,90,200,24,24,"8");			
		LCD_DrawRectangle(0, 40, 60, 80);	LCD_DrawRectangle(60, 40, 120, 80);	LCD_DrawRectangle(120, 40, 180, 80);	LCD_DrawRectangle(180, 40, 240, 80);
		LCD_DrawRectangle(0, 80, 60, 120);	LCD_DrawRectangle(60, 80, 120, 120);	LCD_DrawRectangle(120, 80, 180, 120);	LCD_DrawRectangle(180, 80, 240, 120);
		tp_dev.scan(0);
			if(tp_dev.sta&TP_PRES_DOWN)
		{		
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num2=1;delay_ms(1000);break;}
		if((tp_dev.x[0]>60&&tp_dev.x[0]<120)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num2=2;delay_ms(1000);break;}
		if((tp_dev.x[0]>120&&tp_dev.x[0]<180)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num2=3;delay_ms(1000);break;}
		if((tp_dev.x[0]>180&&tp_dev.x[0]<240)&&(tp_dev.y[0]>40&&tp_dev.y[0]<80)){choose_num2=4;delay_ms(1000);break;}
		if((tp_dev.x[0]>0&&tp_dev.x[0]<60)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num2=5;delay_ms(1000);break;}
		if((tp_dev.x[0]>60&&tp_dev.x[0]<120)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num2=6;delay_ms(1000);break;}
		if((tp_dev.x[0]>120&&tp_dev.x[0]<180)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num2=7;delay_ms(1000);break;}
		if((tp_dev.x[0]>180&&tp_dev.x[0]<240)&&(tp_dev.y[0]>80&&tp_dev.y[0]<120)){choose_num2=8;delay_ms(1000);break;}	
	}		
			}
			
	}	
///////////////////////////////////////////////////////////////////////////////
	  PCA9685_Init(50,90);//PA 11sda 12scl舵机		
	  setAngle(YTXZ,100);		
	  setAngle(YTFY,155);
	  USART3_int();//串口3pb10 11 opemmv 02
	for(int i=0;i<5;i++)
		{
	  USART_SendData(USART3,0x0d);
	  while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);
	  USART_SendData(USART3,cargo_num);
	  while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);
		USART_SendData(USART3,choose_num1);
	  while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);
		USART_SendData(USART3,choose_num2);
	  while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);
		USART_SendData(USART3,0x5b);
	  while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);
		}
///////////////////////////////////////////////////////////////////////////////		
		LED_Init();//IO初始化：PG6.7货物输入，PF12.13.14.15输出（12左，13右，14炮，15风扇）	
		LCD_Init();	//pb0,pd014589 10 14 15 pe78910 11 12 13 14 15 pg0 12
		tp_dev.init();//触屏		
    LCD_ShowString(0,0,200,16,16,"Mode two");	
//////////////////////////////////////////////////
	if(cargo_num==1)
	{
		GPIO_SetBits(Rightlight);
    LCD_ShowString(0,24,200,12,12,"put it at green light");
		while(1)
		{
			if(GPIO_ReadInputDataBit(Rightbox))
			{
				GPIO_ResetBits(Rightlight);
				LCD_ShowString(0,24,200,12,12,"Thank you");
				break;
			}
		}
	}
		if(cargo_num==2)
	{
		GPIO_SetBits(Rightlight);
    LCD_ShowString(0,24,200,12,12,"put 1st at green light");
		while(1)
		{
			if(GPIO_ReadInputDataBit(Rightbox))
			{
				GPIO_ResetBits(Rightlight);
				LCD_ShowString(0,24,200,12,12,"Thank you");
				break;
			}
		}
		GPIO_SetBits(Leftlight);
		LCD_ShowString(0,24,200,12,12,"put 2st at Red light");
		while(1)
		{
			if(GPIO_ReadInputDataBit(Leftbox))
			{
				GPIO_ResetBits(Leftlight);
				LCD_ShowString(0,24,200,12,12,"Thank you");
				LCD_Clear(WHITE);
				break;
			}
		}	
	}
    
	  break;
    }
    USART2_Init(115200);//pa23陀螺仪 	  03   
		TIM4_PWM_Init(999,71);//pa 8 11电机 
		Wave_SRD_Init();//超声波初始化pe 46	
		Timer2_SRD_Init(9999,7199);//超声波定时
		Motor_12_Config();//电机控制pf891011
		imu_data_decode_init(); //映射解析函数	  
		TIM5_Getsample_Int(4999,719);//程序中断定时器50ms01
		GPIO_SetBits(fengshan);
		//TIM3_Getsample_Int(9999, 719);//超声波中断100ms10   超声波00	
}


void test(void)
{
	  LCD_Clear(WHITE);//清屏
	  PCA9685_Init(50,90);//PA 11sda 12scl舵机
	  setAngle(CSBDJ,90);		
	while(1){LCD_ShowString(0,0,200,12,12,"Mode three:camera test");}
}


void MOD3_int(void)
{
	LCD_Clear(WHITE);
	LED_Init();
	PCA9685_Init(50,90);//PA 11sda 12scl舵机		
	UART4_Init(115200);//蓝牙	 
	TIM4_PWM_Init(999,71);//pa 8 11电机
	Motor_12_Config();//电机控制pf891011
	GPIO_SetBits(fengshan);
	LCD_ShowString(0,0,200,12,12,"Mode three:Blue");
	while(1)
	{
		
	 pwm_R=Push;
	 pwm_L=Push;
	 pwm_R=pwm_R-RL;
	 pwm_L=pwm_L+RL;
		if(pwm_L>0)
	{	 	
		Motor_1_PRun();
		TIM_SetCompare3(TIM4,pwm_L);//OK8
	}
	else
	if(pwm_L==0)
	{
		Motor_1_STOP();
	}
	else
	if(pwm_L<0)	
	{
		
		Motor_1_NRun();
		TIM_SetCompare3(TIM4,-pwm_L);//OK8
		
	}
	
	if(pwm_R>0)
	{	 
	  Motor_2_PRun();		
	  TIM_SetCompare4(TIM4,pwm_R);//OK11
	}
	else
	if(pwm_R==0)
	{
	  Motor_2_STOP();	
	}
	else
	if(pwm_R<0)	
	{  	
    Motor_2_NRun();				
	  TIM_SetCompare4(TIM4,-pwm_R);//OK11
		
	}
		setAngle(YTXZ,90+(YTX/2));		//>90左转
	  setAngle(YTFY,90+(YTF/2));
		if(fire_flag==1) 
		{
			GPIO_SetBits(DCP);
		}
		else
		{
			GPIO_ResetBits(DCP);
		}
		  sprintf((char *)strin,"FF:%d",fire_flag);//距离
		  LCD_ShowString(0,12,480,800,12,strin);
	}
}
