/**********头文件声明**********/
#include "key.h"
/******************************/

/*********文件变量声明*********/
/******************************/

//使用PC13作为按键的识别口，默认是高电平，按下为低电平
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟PC13
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
	
//mode=0 不支持连续按,按住不松手算按一下
//mode=1 支持连续按，按一下可能按下了很多下
u8 KEY_Scan(u8 mode)
{
	static u8 key_free=1;
	if(mode)key_free=1;
	if(key_free&&~KEY0)
	{
		delay_ms(4);//去抖动
		key_free=0;
		if (KEY0==0)
		return 1;
	}	
	else if(KEY0)
		key_free=1;
		return 0;
}



