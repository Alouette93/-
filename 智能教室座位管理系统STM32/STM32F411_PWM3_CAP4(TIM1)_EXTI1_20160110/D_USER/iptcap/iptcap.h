#ifndef __IPTCAP_H
#define __IPTCAP_H
/**********头文件声明**********/
#include "sys.h"
#include "delay.h"
#include "usart2.h"	
/******************************/

/*********全局变量声明*********/
extern u32 TimCapHigh1;
extern u32 TimCapHigh2;
extern u32 TimCapHigh3;
extern u32 TimCapHigh4;
/******************************/

/**********宏定义声明**********/		
#define PR printf
/******************************/

/***********函数声明***********/
void TIM1_Cap_Init(u16 arr,u16 psc);
/******************************/

#endif
