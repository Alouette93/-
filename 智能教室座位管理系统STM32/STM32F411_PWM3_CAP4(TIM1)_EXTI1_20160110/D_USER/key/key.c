/**********ͷ�ļ�����**********/
#include "key.h"
/******************************/

/*********�ļ���������*********/
/******************************/

//ʹ��PC13��Ϊ������ʶ��ڣ�Ĭ���Ǹߵ�ƽ������Ϊ�͵�ƽ
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOCʱ��PC13
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
	
//mode=0 ��֧��������,��ס�������㰴һ��
//mode=1 ֧������������һ�¿��ܰ����˺ܶ���
u8 KEY_Scan(u8 mode)
{
	static u8 key_free=1;
	if(mode)key_free=1;
	if(key_free&&~KEY0)
	{
		delay_ms(4);//ȥ����
		key_free=0;
		if (KEY0==0)
		return 1;
	}	
	else if(KEY0)
		key_free=1;
		return 0;
}



