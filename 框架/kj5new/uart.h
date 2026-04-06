#ifndef __UART_H__
#define __UART_H__

#include "sys.h"
#include <stdio.h> 

void uart_init(void);
void uart_send_byte(u8 dat);
void uart_send_num(u8 num);

#endif