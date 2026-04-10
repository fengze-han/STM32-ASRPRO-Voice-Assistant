#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

extern int8_t    fan;
extern int8_t     bianliang;
void uart_init(u32 bound);
void dedaoshuzi (uint8_t *tqq);
void getnewdata (uint8_t data);
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN],get_num,Res,other_flag; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	

extern uint8_t  num_buff[3],think_flag;	

void Serial_SendByte(uint16_t Byte);
#endif


