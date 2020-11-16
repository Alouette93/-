/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.24
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/


//整套推荐IO查看Projecct文件夹下的TXT文本



//打开新的工程或者工程移动了位置务必执行以下操作
//第一步 关闭上面所有打开的文件
//第二步 project  clean  等待下方进度条走完



#include "headfile.h"






//实验现象说明：将RX TX短接 然后实现自发自收的功能
//通过在线调试可以看到 uart_data数据在持续加一操作
void SetIRQ()
{
	NVIC_SetPriority(PIT_IRQn,2);
	NVIC_SetPriority(LPUART1_IRQn,1);         //设置串口中断优先级 范围0-15 越小优先级越高
}

void BoardInit()
{
		pwm_init(PWM4_MODULE3_CHA_C31, 80, 5000);
	  simiic_init();
	  pit_init();
	  pit_interrupt_ms(PIT_CH0,3);
    uart_init (USART_1, 115200,UART1_TX_B12,UART1_RX_B13);	//初始换串口   波特率为115200 TX为D16 RX为D17
    uart_rx_irq(USART_1,1);
    serialInit();
	  oled_init();
		gpio_init(C15, GPO, 0, GPIO_PIN_CONFIG);
}

int main(void)
{
    DisableGlobalIRQ();
    board_init();   //务必保留，本函数用于初始化MPU 时钟 调试串口
    BoardInit();
	  SetIRQ();
    EnableGlobalIRQ(0);
    
    pwm_duty(PWM4_MODULE3_CHA_C31,0);
    
    while(1)
    {
        //串口字节发送
				UserInterfaceOled();
				//uart_putchar(USART_1,uart_data);
        //更多功能函数 自行查阅zf_uart文件
//        systick_delay_ms(100);
//			  pwm_duty(PWM4_MODULE3_CHA_C31,1000);
//        systick_delay_ms(100);
//			  pwm_duty(PWM4_MODULE3_CHA_C31,0);
//				systick_delay_ms(100);
    }

    
}





