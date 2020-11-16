/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.24
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�



//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������



#include "headfile.h"






//ʵ������˵������RX TX�̽� Ȼ��ʵ���Է����յĹ���
//ͨ�����ߵ��Կ��Կ��� uart_data�����ڳ�����һ����
void SetIRQ()
{
	NVIC_SetPriority(PIT_IRQn,2);
	NVIC_SetPriority(LPUART1_IRQn,1);         //���ô����ж����ȼ� ��Χ0-15 ԽС���ȼ�Խ��
}

void BoardInit()
{
		pwm_init(PWM4_MODULE3_CHA_C31, 80, 5000);
	  simiic_init();
	  pit_init();
	  pit_interrupt_ms(PIT_CH0,3);
    uart_init (USART_1, 115200,UART1_TX_B12,UART1_RX_B13);	//��ʼ������   ������Ϊ115200 TXΪD16 RXΪD17
    uart_rx_irq(USART_1,1);
    serialInit();
	  oled_init();
		gpio_init(C15, GPO, 0, GPIO_PIN_CONFIG);
}

int main(void)
{
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    BoardInit();
	  SetIRQ();
    EnableGlobalIRQ(0);
    
    pwm_duty(PWM4_MODULE3_CHA_C31,0);
    
    while(1)
    {
        //�����ֽڷ���
				UserInterfaceOled();
				//uart_putchar(USART_1,uart_data);
        //���๦�ܺ��� ���в���zf_uart�ļ�
//        systick_delay_ms(100);
//			  pwm_duty(PWM4_MODULE3_CHA_C31,1000);
//        systick_delay_ms(100);
//			  pwm_duty(PWM4_MODULE3_CHA_C31,0);
//				systick_delay_ms(100);
    }

    
}





