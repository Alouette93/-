/**********ͷ�ļ�����**********/
#include "timer.h"
/******************************/

/*********�ļ���������*********/
#define HEIGHT 7
#define TINECOUNT 10
PhoneStatusNode PhoneStatus=WAIT;
/******************************/

//ͨ�ö�ʱ��3�жϳ�ʼ��
void TIM3_Init(u16 arr,u16 psc)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
		TIME_GRADE++;
		LED0=~LED0;
	}
	else
		delay_us(5);
}
//ͨ�ö�ʱ��3�жϳ�ʼ��
void TIM5_Init(u16 arr,u16 psc)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///ʹ��TIM3ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM5,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//��ʱ��3�жϷ�����
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //����ж�
	{
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //����жϱ�־λ
//		switch(PhoneStatus)
//		{
//			case WAIT:
//				USART_SendData(USART1,'a');
//				break;
//			case READY:
//				USART_SendData(USART1,'b');
//				break; 
//			case WARNING:
//				break;
//			case TRANSMIT:
//				USART_SendData(USART1,'c');
//				break;
//		}
	}
	else
		delay_us(5);
}
//ͨ�ö�ʱ��4�жϳ�ʼ��
void TIM4_Init(u16 arr,u16 psc)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//��ʱ��4�жϷ�����
void TIM4_IRQHandler(void)
{
	static u8 readyflag=0;
	static u8 warningflag=0;
	static u8 backflag=0;
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //����ж�
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //����жϱ�־λ
		switch(PhoneStatus)
		{
			case WAIT:{
				if(distance<HEIGHT) ++readyflag;
				else readyflag=0;
				if(readyflag>=4)
				{
					readyflag=0;
					OledCls();
					PhoneStatus=READY;
				}
				break;
			}
			case READY:{
				if(distance>HEIGHT) ++warningflag;
				else warningflag=0;
				if(warningflag>=4)
				{
					warningflag=0;
					OledCls();
					PhoneStatus=WARNING;
				}
				break; 
			}
			case WARNING:{
				if(tiktok==666) tiktok=TINECOUNT*mul;
				--tiktok;
				if(distance<HEIGHT) ++backflag;
				else backflag=0;
				if(backflag>=2)
				{
					backflag=0;
					tiktok=TINECOUNT*mul;
					OledCls();
					PhoneStatus=READY;
				}
				if(tiktok==0)
				{
					tiktok=TINECOUNT*mul;
					PhoneStatus=TRANSMIT;
					OledCls();
				}
				break;
			}	
			case TRANSMIT:
				break;
			
		}
	}
}
