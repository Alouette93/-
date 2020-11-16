#ifndef __KEY_H
#define __KEY_H
/**********头文件声明**********/
#include "sys.h"
#include "delay.h"
/******************************/

/*********全局变量声明*********/
/******************************/

/**********宏定义声明**********/		
#define KEY0 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)
/******************************/

/***********函数声明***********/
void KEY_Init(void);
u8 KEY_Scan(u8 mode);
/******************************/

#endif
