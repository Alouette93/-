#ifndef oled_h
#define oled_h



//定义OLED的GPIO
#define OLED_RCC				RCC_AHB1Periph_GPIOB	//定义OLED端口时钟总线		
#define OLED_GPIOx				GPIOB
#define OLED_SCL_GPIO_Pin		GPIO_Pin_10
#define OLED_SDA_CPIO_Pin		GPIO_Pin_4
#define OLED_RES_GPIO_Pin		GPIO_Pin_5
#define OLED_DC_GPIO_Pin		GPIO_Pin_3

#include "delay.h"
#define OledDelayMs(ms) 			delay_ms(ms)


//模式
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

//OLED端口定义
//OLED的时钟引脚(SCL)
#define OLED_SCL_L() GPIO_ResetBits(OLED_GPIOx,OLED_SCL_GPIO_Pin)
#define OLED_SCL_H() GPIO_SetBits(OLED_GPIOx,OLED_SCL_GPIO_Pin)
//OLED的数据引脚(SDA)
#define OLED_SDA_L() GPIO_ResetBits(OLED_GPIOx,OLED_SDA_CPIO_Pin)
#define OLED_SDA_H() GPIO_SetBits(OLED_GPIOx,OLED_SDA_CPIO_Pin)
//OLED的复位引脚(RES)
#define OLED_RST_L() GPIO_ResetBits(OLED_GPIOx,OLED_RES_GPIO_Pin)
#define OLED_RST_H() GPIO_SetBits(OLED_GPIOx,OLED_RES_GPIO_Pin)
//OLED的数据/命令控制引脚(DC)
#define OLED_DC_L() GPIO_ResetBits(OLED_GPIOx,OLED_DC_GPIO_Pin)
#define OLED_DC_H() GPIO_SetBits(OLED_GPIOx,OLED_DC_GPIO_Pin)

//模式
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据



//函数声明
void OledCls(void);//清屏函数
void OledInit(void);//OLED初始化
void OledShow6x8Char(unsigned char x, unsigned char y, char ch);//显示一个6x8标准ASCII字符
void OledShow6x8Str(unsigned char x, unsigned char y, char *ch);//写入一组6x8标准ASCII字符串
void OledPrintValueI(unsigned char x, unsigned char y, int data);//将一个整型数转换成5位数进行显示	
void OledPrintValueF(unsigned char x, unsigned char y, float data, unsigned char num);//将一个float型数转换成5位数带小数和符号的数据进行显示
void OledPrintImage(unsigned char *pucTable, unsigned int usRowNum, unsigned int usColumnNum);//显示图像
void OledTimeValueShow(unsigned char x, unsigned char y, int data);//用于时间显示
void OledYearValueShow(unsigned char x, unsigned char y, int data);//年份显示

#endif


