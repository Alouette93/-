#ifndef __IPTCAP_H
#define __IPTCAP_H
/**********ͷ�ļ�����**********/
#include "sys.h"
#include "delay.h"
#include "usart2.h"	
/******************************/

/*********ȫ�ֱ�������*********/
extern u32 TimCapHigh1;
extern u32 TimCapHigh2;
extern u32 TimCapHigh3;
extern u32 TimCapHigh4;
/******************************/

/**********�궨������**********/		
#define PR printf
/******************************/

/***********��������***********/
void TIM1_Cap_Init(u16 arr,u16 psc);
/******************************/

#endif
