#include "stm32f4xx.h"
#include "loudspeaker.h"
#include "timer.h"
void loudspeaker_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	//Trig
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
void voice_play()
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_14);
	GPIO_SetBits(GPIOA, GPIO_Pin_14);
	delay_ms(50);
	GPIO_ResetBits(GPIOA, GPIO_Pin_14);
}




