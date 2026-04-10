#ifndef __DHT11_H
#define __DHT11_H
#include "stm32f10x.h"                  // Device header

extern uint8_t dat[4];//接收数据

void Data_Out_Init(void);
void Data_In_Init(void);
void DHT11_start(void);
uint8_t DHT11_rec_byte(void);
void DHT11_rec_data(void) ;//温度 湿度

#endif

