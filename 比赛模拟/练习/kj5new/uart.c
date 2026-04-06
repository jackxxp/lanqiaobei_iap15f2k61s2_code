#include "uart.h"


void uart_init(void)
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xC7;			//设置定时初始值
	TH1 = 0xFE;			//设置定时初始值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
}

void uart_send_byte(u8 dat)
{
    SBUF = dat;
    while(TI == 0);
    TI = 0;
}


void uart_send_num(u8 num)
{
    switch(num) {
        case 0: uart_send_byte('0'); break;
        case 1: uart_send_byte('1'); break;
        case 2: uart_send_byte('2'); break;
        case 3: uart_send_byte('3'); break;
        case 4: uart_send_byte('4'); break;
        case 5: uart_send_byte('5'); break;
        case 6: uart_send_byte('6'); break;
        case 7: uart_send_byte('7'); break;
        case 8: uart_send_byte('8'); break;
        case 9: uart_send_byte('9'); break;
        default: uart_send_byte('?'); break;  // 超出范围显示?
    }
}