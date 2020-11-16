#ifndef _TIMER_H
#define _TIMER_H
/**********头文件声明**********/
#include "sys.h"
#include "usart2.h"
#include "delay.h"
#include "led.h" 
#include "hc.h"
#include "oled.h"
/******************************/
typedef enum 
{
	WAIT=0,
	READY,
	WARNING,
	TRANSMIT,
}PhoneStatusNode;
/*********全局变量声明*********/
extern u32 TIME_GRADE;
extern u32 TIME_CYCLE;
extern u32 tiktok;
extern u8 mul;
extern  PhoneStatusNode PhoneStatus;
/******************************/

/**********宏定义声明**********/		
/******************************/

/***********函数声明***********/
void TIM3_Init(u16 arr,u16 psc);
void TIM4_Init(u16 arr,u16 psc);
void TIM5_Init(u16 arr,u16 psc);
/******************************/

#endif
