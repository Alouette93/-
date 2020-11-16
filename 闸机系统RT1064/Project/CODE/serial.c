/*
 * @Description: 
 * @Version: 1.0
 * @Autor: Alouette
 * @Date: 2020-11-13 19:08:29
 * @LastEditors: Alouette
 * @LastEditTime: 2020-11-13 19:10:32
 */
//
//  user_interface.c
//  emc_smc
//
//  Created by fukai on 2018/10.
//  Copyright © 2018年 赛博智能车实验室. All rights reserved.
//

#include "headfile.h"

uint8 example_rx_buffer;
lpuart_transfer_t example_receivexfer;
lpuart_handle_t example_g_lpuartHandle;

uint8 uart_send;
uint8 uart_data;
uint8 cnt=0;
char data_stream[11];
char data_stream2[4];
void example_uart_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
  if (kStatus_LPUART_RxIdle == status)
  {
    //Êý¾ÝÒÑ¾­±»Ð´Èëµ½ÁË Ö®Ç°ÉèÖÃµÄBUFFÖÐ
    //±¾Àý³ÌÊ¹ÓÃµÄBUFFÎª example_rx_buffer
    uart_data = example_rx_buffer; //½«Êý¾ÝÈ¡³ö
  }

  handle->rxDataSize = example_receivexfer.dataSize; //»¹Ô­»º³åÇø³¤¶È
  handle->rxData = example_receivexfer.data;         //»¹Ô­»º³åÇøµØÖ·
	if(cnt==14)
	{
		cnt=0;
	}
	if(cnt<10)
	{
		data_stream[cnt]=uart_data;
	}
	if(10<cnt&&cnt<13)
	{
		data_stream2[cnt-11]=uart_data;
	}
	cnt++;
}

void serialInit()
{
	//ÅäÖÃ´®¿Ú½ÓÊÕµÄ»º³åÇø¼°»º³åÇø³¤¶È
    example_receivexfer.dataSize = 1;
    example_receivexfer.data = &example_rx_buffer;
    
    //ÉèÖÃÖÐ¶Ïº¯Êý¼°Æä²ÎÊý
    uart_set_handle(USART_1, &example_g_lpuartHandle, example_uart_callback, NULL, 0, example_receivexfer.data, 1);
}