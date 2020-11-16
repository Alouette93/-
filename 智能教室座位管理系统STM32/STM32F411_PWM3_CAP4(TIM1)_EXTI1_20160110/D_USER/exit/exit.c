/**********头文件声明**********/
#include "exit.h" 
#include "key.h"
#include "delay.h"
/******************************/

/*********文件变量声明*********/
u8 Init_flg=1;
u16 grade01=0;
u16 grade1=0;
u32 grade02=0;
u32 grade2=0;
/******************************/

void EXIT_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;

	
	//KEY_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);//PC12 连接到中断线12
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
	EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断13
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置
	
	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟PC12
//	
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
//	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource12);//PC12 连接到中断线12
//	
//	EXTI_InitStructure.EXTI_Line = EXTI_Line12;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿沿触发
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
//	EXTI_Init(&EXTI_InitStructure);//配置
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断12
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;//子优先级2
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//	NVIC_Init(&NVIC_InitStructure);//配置
	
}


//void EXTI15_10_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line12)!=RESET)
//	{
//		EXTI_ClearITPendingBit(EXTI_Line12); //清除LINE0上的中断标志位
//		if(Init_flg==1)//the first
//		{			
//			TIM3_Init(50000-1,50-1);
//			Init_flg=0;
//			TIME_GRADE=0;
//		}
//		// get the total sum:grade1(us)
//		grade01=TIM_GetCounter(TIM3);
//		grade02=TIME_GRADE;
//		TIME_GRADE=0;
////		printf("\r\ngrade01=%d;grade02=%d;",grade01,grade02);		
//		
//		grade2=grade02*50000+grade01-grade1;

//		grade1=grade01;
//		if(grade2==0) {grade2=1000;printf("\r\nwrong!\r\n");}
//		FRU_S=1000000/(float)grade2;		 
//	}
//	else delay_us(5);
//}

void EXTI15_10_IRQHandler(void)
{
	if(KEY_Scan(0))
	{
		LED0=~LED0;
	}
}


