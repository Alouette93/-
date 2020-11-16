#include "hc.h"
#include "stm32f4xx.h"
#include "timer.h"
#include "oled.h"
int count=0;
float distance=0;

void HC_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	//Trig
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	//ECHO
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	
}
void Timer3_Config(void){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_TimeBaseInitStructure.TIM_Prescaler = 99;
	TIM_TimeBaseInitStructure.TIM_Period = 49999;	//50000000/50000 = 1ms
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);	
}
float Distance_Calculate()
{
	//cm
	//v = 340m/s = 34000cm/s = 34000cm/10^6us = 0.034cm/us
	//s = vt/2 = t*0.034/2 = t*0.017 ˜ t/58
    float Distance = 0;
    Distance = ((float)count / 58);
    return Distance;

}
void distance_measure()
{

		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		GPIO_SetBits(GPIOB, GPIO_Pin_8);
		delay_us(10);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		TIM3->CNT = 0;	
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0);	
		TIM_Cmd(TIM3, ENABLE);
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 1){}
		TIM_Cmd(TIM3, DISABLE);
		count = TIM3->CNT;
		distance = Distance_Calculate();
		delay_ms(50);
}

