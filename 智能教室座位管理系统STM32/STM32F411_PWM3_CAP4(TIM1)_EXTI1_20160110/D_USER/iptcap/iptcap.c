/**********头文件声明**********/
#include "iptcap.h"
/******************************/

/*********文件变量声明*********/
u8 TIM1CH1_STA=0;
u8 TIM1CH2_STA=0;
u8 TIM1CH3_STA=0;
u8 TIM1CH4_STA=0;
/******************************/

//定时器1通道1输入捕获配置
//arr：自动重装值(TIM1是16位寄存器)
//psc：时钟预分频数
//tim1的时钟线在APB2上，频率为50M，psc不为1时为100M
void TIM1_Cap_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef  TIM1_ICInitStructure;

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM1时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA0

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	
	

	//初始化TIM1输入捕获参数
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_1;//使能四个通道
	TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射CH1->TI1,CH2->TI2,CH3->TI3,CH4->TI4
	TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
	TIM1_ICInitStructure.TIM_ICFilter = 0x00;//配置输入滤波器 不滤波
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_2;//使能四个通道
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_3;//使能四个通道
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_4;//使能四个通道
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
		
	TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许捕获中断	
	//TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	
	TIM_Cmd(TIM1,ENABLE ); 	//使能定时器1

 
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x00;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x01;		//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	
}



//更新中断
void TIM1_UP_TIM10_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET) //溢出中断
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);  //清除中断标志位
		TIM1CH1_STA++;
		TIM1CH2_STA++;
		TIM1CH3_STA++;
		TIM1CH4_STA++;
	}
}

//捕获中断
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
