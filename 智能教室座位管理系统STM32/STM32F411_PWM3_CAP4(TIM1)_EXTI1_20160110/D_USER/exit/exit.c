/**********ͷ�ļ�����**********/
#include "exit.h" 
#include "key.h"
#include "delay.h"
/******************************/

/*********�ļ���������*********/
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);//PC12 ���ӵ��ж���12
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�13
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//����
	
	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOCʱ��PC12
//	
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
//	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource12);//PC12 ���ӵ��ж���12
//	
//	EXTI_InitStructure.EXTI_Line = EXTI_Line12;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж�
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�������ش���
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
//	EXTI_Init(&EXTI_InitStructure);//����
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�12
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;//�����ȼ�2
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//	NVIC_Init(&NVIC_InitStructure);//����
	
}


//void EXTI15_10_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line12)!=RESET)
//	{
//		EXTI_ClearITPendingBit(EXTI_Line12); //���LINE0�ϵ��жϱ�־λ
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


