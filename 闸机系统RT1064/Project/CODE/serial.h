//
//  user_interface.h
//  emc_smc
//
//  Created by fukai on 2018/10.
//  Copyright © 2018年 赛博智能车实验室. All rights reserved.
//

#ifndef serial_h
#define serial_h
#include "headfile.h"
extern unsigned char uart_data;
extern uint8 uart_send;
extern char data_stream[11];
extern char data_stream2[4];
void serialInit(void);
void example_uart_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);


#endif
