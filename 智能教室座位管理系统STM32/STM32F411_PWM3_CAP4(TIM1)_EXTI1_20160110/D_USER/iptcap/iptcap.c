/**********ͷ�ļ�����**********/
#include "iptcap.h"
/******************************/

/*********�ļ���������*********/
u8 TIM1CH1_STA=0;
u8 TIM1CH2_STA=0;
u8 TIM1CH3_STA=0;
u8 TIM1CH4_STA=0;
/******************************/

//��ʱ��1ͨ��1���벶������
//arr���Զ���װֵ(TIM1��16λ�Ĵ���)
//psc��ʱ��Ԥ��Ƶ��
//tim1��ʱ������APB2�ϣ�Ƶ��Ϊ50M��psc��Ϊ1ʱΪ100M
void TIM1_Cap_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef  TIM1_ICInitStructure;

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM1ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA0

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	
	

	//��ʼ��TIM1���벶�����
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_1;//ʹ���ĸ�ͨ��
	TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ��CH1->TI1,CH2->TI2,CH3->TI3,CH4->TI4
	TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM1_ICInitStructure.TIM_ICFilter = 0x00;//���������˲��� ���˲�
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_2;//ʹ���ĸ�ͨ��
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_3;//ʹ���ĸ�ͨ��
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_4;//ʹ���ĸ�ͨ��
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
		
	TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//��������ж� ,�������ж�	
	//TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	
	TIM_Cmd(TIM1,ENABLE ); 	//ʹ�ܶ�ʱ��1

 
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x00;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x01;		//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	
}



//�����ж�
void TIM1_UP_TIM10_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET) //����ж�
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);  //����жϱ�־λ
		TIM1CH1_STA++;
		TIM1CH2_STA++;
		TIM1CH3_STA++;
		TIM1CH4_STA++;
	}
}

//�����ж�
void TIM1_CC_IRQHandler(void)
{
	static u32 	TIM1CH1_CAPTURE_STA1;		    				
	static u16	TIM1CH1_CAPTURE_VAL1;
	static u32 	TIM1CH1_CAPTURE_STA2;		    				
	static u16	TIM1CH1_CAPTURE_VAL2;
	static u32 	TIM1CH2_CAPTURE_STA1;		    				
	static u16	TIM1CH2_CAPTURE_VAL1;
	static u32 	TIM1CH2_CAPTURE_STA2;		    				
	static u16	TIM1CH2_CAPTURE_VAL2;
	static u32 	TIM1CH3_CAPTURE_STA1;		    				
	static u16	TIM1CH3_CAPTURE_VAL1;
	static u32 	TIM1CH3_CAPTURE_STA2;		    				
	static u16	TIM1CH3_CAPTURE_VAL2;
	static u32 	TIM1CH4_CAPTURE_STA1;		    				
	static u16	TIM1CH4_CAPTURE_VAL1;
	static u32 	TIM1CH4_CAPTURE_STA2;		    				
	static u16	TIM1CH4_CAPTURE_VAL2;
	/***********TIM1CH1**********/
	if(TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
	{
		static u8 TimCapFlag1=1;
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
		if(TimCapFlag1==1)
		{
			TIM1CH1_CAPTURE_STA1=TIM1CH1_STA;
			TIM1CH1_CAPTURE_VAL1=TIM_GetCapture1(TIM1);
//			PR("\r\nsta1=%10d;val1=%10d;",TIM1CH1_CAPTURE_STA1,TIM1CH1_CAPTURE_VAL1);
			TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);
			TimCapFlag1=0;
		}
		else if(TimCapFlag1==0)
		{
			TIM1CH1_CAPTURE_STA2=TIM1CH1_STA;
			TIM1CH1_CAPTURE_VAL2=TIM_GetCapture1(TIM1);
//			PR("\r\nsta2=%10d;val2=%10d;",TIM1CH1_CAPTURE_STA2,TIM1CH1_CAPTURE_VAL2);
//			PR("\r\nval1=%10d;val2=%10d",TIM1CH1_CAPTURE_VAL1,TIM1CH1_CAPTURE_VAL2);
			TimCapHigh1=(TIM1CH1_CAPTURE_STA2-TIM1CH1_CAPTURE_STA1)*40000+TIM1CH1_CAPTURE_VAL2-TIM1CH1_CAPTURE_VAL1;
//			PR("\r\ntimhigh=%10d;",TimCapHigh1);
			TIM1CH1_CAPTURE_STA1=0;
			TIM1CH1_CAPTURE_VAL1=0;
			TIM1CH1_CAPTURE_STA2=0;
			TIM1CH1_CAPTURE_VAL2=0;
			TIM1CH1_STA=0;
		TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising);
			TimCapFlag1=1;
		}
	}
	
	/****************************/
	
	/***********TIM1CH2**********/
else if(TIM_GetITStatus(TIM1, TIM_IT_CC2) != RESET)
	{
		static u8 TimCapFlag2=1;
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);
		if(TimCapFlag2==1)
		{
			TIM1CH2_CAPTURE_STA1=TIM1CH2_STA;
			TIM1CH2_CAPTURE_VAL1=TIM_GetCapture2(TIM1);
			//PR("\r\nsta1=%10d;val1=%10d;",TIM1CH1_CAPTURE_STA1,TIM1CH1_CAPTURE_VAL1);
			TIM_OC2PolarityConfig(TIM1,TIM_ICPolarity_Falling);
			TimCapFlag2=0;
		}
		else if(TimCapFlag2==0)
		{
			TIM1CH2_CAPTURE_STA2=TIM1CH2_STA;
			TIM1CH2_CAPTURE_VAL2=TIM_GetCapture2(TIM1);
			//PR("\r\nsta2=%10d;val2=%10d;",TIM1CH1_CAPTURE_STA2,TIM1CH1_CAPTURE_VAL2);
			//PR("\r\nval1=%10d;val2=%10d",TIM1CH1_CAPTURE_VAL1,TIM1CH1_CAPTURE_VAL2);
			TimCapHigh2=(TIM1CH2_CAPTURE_STA2-TIM1CH2_CAPTURE_STA1)*40000+TIM1CH2_CAPTURE_VAL2-TIM1CH2_CAPTURE_VAL1;
			//PR("\r\ntimhigh=%10d;",TimCapHigh1);
			TIM1CH2_CAPTURE_STA1=0;
			TIM1CH2_CAPTURE_VAL1=0;
			TIM1CH2_CAPTURE_STA2=0;
			TIM1CH2_CAPTURE_VAL2=0;
			TIM1CH2_STA=0;
			TIM_OC2PolarityConfig(TIM1,TIM_ICPolarity_Rising);
			TimCapFlag2=1;
		}
	}
	/****************************/
	
	/***********TIM1CH3**********/
	else if(TIM_GetITStatus(TIM1, TIM_IT_CC3) != RESET)
	{
		static u8 TimCapFlag3=1;
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);
		if(TimCapFlag3==1)
		{
			TIM1CH3_CAPTURE_STA1=TIM1CH3_STA;
			TIM1CH3_CAPTURE_VAL1=TIM_GetCapture3(TIM1);
			//PR("\r\nsta1=%10d;val1=%10d;",TIM1CH1_CAPTURE_STA1,TIM1CH1_CAPTURE_VAL1);
			TIM_OC3PolarityConfig(TIM1,TIM_ICPolarity_Falling);
			TimCapFlag3=0;
		}
		else if(TimCapFlag3==0)
		{
			TIM1CH3_CAPTURE_STA2=TIM1CH3_STA;
			TIM1CH3_CAPTURE_VAL2=TIM_GetCapture3(TIM1);
			//PR("\r\nsta2=%10d;val2=%10d;",TIM1CH1_CAPTURE_STA2,TIM1CH1_CAPTURE_VAL2);
			//PR("\r\nval1=%10d;val2=%10d",TIM1CH1_CAPTURE_VAL1,TIM1CH1_CAPTURE_VAL2);
			TimCapHigh3=(TIM1CH3_CAPTURE_STA2-TIM1CH3_CAPTURE_STA1)*40000+TIM1CH3_CAPTURE_VAL2-TIM1CH3_CAPTURE_VAL1;
			//PR("\r\ntimhigh=%10d;",TimCapHigh1);
			TIM1CH3_CAPTURE_STA1=0;
			TIM1CH3_CAPTURE_VAL1=0;
			TIM1CH3_CAPTURE_STA2=0;
			TIM1CH3_CAPTURE_VAL2=0;
			TIM1CH3_STA=0;
			TIM_OC3PolarityConfig(TIM1,TIM_ICPolarity_Rising);
			TimCapFlag3=1;
		}
	}
	/****************************/
	
	/***********TIM1CH4**********/
	else if(TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET)
	{
		static u8 TimCapFlag4=1;
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);
		if(TimCapFlag4==1)
		{
			TIM1CH4_CAPTURE_STA1=TIM1CH4_STA;
			TIM1CH4_CAPTURE_VAL1=TIM_GetCapture4(TIM1);
			//PR("\r\nsta1=%10d;val1=%10d;",TIM1CH1_CAPTURE_STA1,TIM1CH1_CAPTURE_VAL1);
			TIM_OC4PolarityConfig(TIM1,TIM_ICPolarity_Falling);
			TimCapFlag4=0;
		}
		else if(TimCapFlag4==0)
		{
			TIM1CH4_CAPTURE_STA2=TIM1CH4_STA;
			TIM1CH4_CAPTURE_VAL2=TIM_GetCapture4(TIM1);
			//PR("\r\nsta2=%10d;val2=%10d;",TIM1CH1_CAPTURE_STA2,TIM1CH1_CAPTURE_VAL2);
			//PR("\r\nval1=%10d;val2=%10d",TIM1CH1_CAPTURE_VAL1,TIM1CH1_CAPTURE_VAL2);
			TimCapHigh4=(TIM1CH4_CAPTURE_STA2-TIM1CH4_CAPTURE_STA1)*40000+TIM1CH4_CAPTURE_VAL2-TIM1CH4_CAPTURE_VAL1;
			//PR("\r\ntimhigh=%10d;",TimCapHigh1);
			TIM1CH4_CAPTURE_STA1=0;
			TIM1CH4_CAPTURE_VAL1=0;
			TIM1CH4_CAPTURE_STA2=0;
			TIM1CH4_CAPTURE_VAL2=0;
			TIM1CH4_STA=0;
			TIM_OC4PolarityConfig(TIM1,TIM_ICPolarity_Rising);
			TimCapFlag4=1;
		}
	}
	/****************************/
	
}
