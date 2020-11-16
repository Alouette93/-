#include "sys.h"
#include "delay.h"
#include "usart2.h"
#include "led.h"
#include "timer.h"
#include "exit.h" 
#include "pwm.h"
#include "iptcap.h"
#include "key.h"
#include "oled.h"
#include "hc.h"
#include "loudspeaker.h"

void DisplayTimeCycle(void);
void DisplayHighPlus(void);

#define PR printf

u32 TIME_GRADE=0;
u32 TIME_CYCLE=0;
float FRU_S=0;
u32 TimCapHigh1;
u32 TimCapHigh2;
u32 TimCapHigh3;
u32 TimCapHigh4;

u32 tiktok=666;
u8 mul=4;




u8 dir=1;
u16 led0pwmval=0;  
void led_breathe()
{
	if(dir)led0pwmval++;//dir==1 led0pwmval递增
	else led0pwmval--;	//dir==0 led0pwmval递减 
 	if(led0pwmval>200)dir=0;//led0pwmval到达300后，方向为递减
	if(led0pwmval==0)dir=1;	//led0pwmval递减到0后，方向改为递
	TIM_SetCompare1(TIM2,led0pwmval);	//修改比较值，修改占空比
};
void ShowDis(void)
{
//	OledShow6x8Str(0,0,"count:");
//	OledPrintValueI(0,1,count);
	OledShow6x8Str(0,0,"dis(cm):");
	OledPrintValueF(0,1,distance,3);
}

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//int flag=0;
	LED_Init();			      //初始化LED端口
	KEY_Init();
	delay_init(168);		  //初始化延时函数
      
	

	usart1_init(115200);                      
	//TIM2_PWM_Init(500-1,84-1);//12ms
    //TIM_SetCompare1(TIM2,0);
	//TIM4_Init(50000-1,50-1);//30ms
	//EXIT_Init();
	//TIM1_Cap_Init(40000-1,100-1);
	
	TIM4_Init(1999,4999);//1s
	OledInit();
	loudspeaker_Config();
	Timer3_Config();
	HC_Config();
	//TIM5_Init(999,4999);
	while(1)
	{  
	    distance_measure();

		switch(PhoneStatus)
		{
			case WAIT:{
				
				//ShowDis();
				USART_SendData(USART1,'b');
				OledShow6x8Str(40,3,"Put Phone");
				break;
			}
			case READY:{
				OledCls();
				//ShowDis();
				USART_SendData(USART1,'b');
				OledShow6x8Str(43,3,"READY");
				break;
			}
			case WARNING:{
				//ShowDis();
				OledShow6x8Str(40,3,"WARNING");
				OledShow6x8Str(26,4,"Timing:");
				OledPrintValueI(70,4,tiktok/mul);
				break;
			}
			case TRANSMIT:{
				OledShow6x8Str(35,3,"TRANSMIT...");
				delay_ms(500);
				delay_ms(500);
				USART_SendData(USART1,'c');
				OledCls();
				OledShow6x8Str(18,3,"TRANSMIT SUCCESS");
				delay_ms(500);
				//delay_ms(500);
				OledCls();
				PhoneStatus=WAIT;
				break;
			}
		}
		
	}

}



































void DisplayTimeCycle(void)
{
	if((int)FRU_S!=0)
	{
		PR("\r\nFrequencyS=%8.2f;CycleMS=%8.2f;",FRU_S,1000/FRU_S);
		FRU_S=0;
	}
}


void DisplayHighPlus(void)
{
	/***********TIM1CH1**********/
	if(TimCapHigh1!=0)
	{
		PR("\r\nHighPlusCh1=%d;",TimCapHigh1);
		TimCapHigh1=0;
	}	

	/****************************/
	
	/***********TIM1CH2**********/
	if(TimCapHigh2!=0)
	{
		PR("\r\nHighPlusCh2=%d;",TimCapHigh2);
		TimCapHigh2=0;
	}
	/****************************/
	
	/***********TIM1CH3**********/
	if(TimCapHigh3!=0)
	{
		PR("\r\nHighPlusCh3=%d;",TimCapHigh3);
		TimCapHigh3=0;
	}
	/****************************/
	
	/***********TIM1CH4**********/
	if(TimCapHigh4!=0)
	{
		PR("\r\nHighPlusCh4=%d;",TimCapHigh4);
		TimCapHigh4=0;
	}
}



