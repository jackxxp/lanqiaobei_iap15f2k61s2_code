#include "sys.h"

void gpio_init()
{
    P0M0 = 0x00; P0M1 = 0x00; 
    P1M0 = 0x00; P1M1 = 0x00; 
    P2M0 = 0x00; P2M1 = 0x00; 
    P3M0 = 0x00; P3M1 = 0x00; 
    P4M0 = 0x00; P4M1 = 0x00; 
    P5M0 = 0x00; P5M1 = 0x00; 
    P6M0 = 0x00; P6M1 = 0x00; 
    P7M0 = 0x00; P7M1 = 0x00; 
}

void drv_init()
{
    sys_decoder(0);
    P0 = 0xff;sys_decoder(4);sys_decoder(0);
    P0 = 0x00;sys_decoder(6);sys_decoder(0);
    P0 = 0xff;sys_decoder(7);sys_decoder(0);
    P0 = 0xaf;sys_decoder(5);sys_decoder(0);
}

void sys_tick_timer_init()
{
    AUXR &= 0xFB;			//定时器时钟12T模式
	T2L = 0x18;				//设置定时初始值
	T2H = 0xFC;				//设置定时初始值
	AUXR |= 0x10;			//定时器2开始计时
	IE2 |= 0x04;			//使能定时器2中断

    EA = 1;
}


void sys_decoder(u8 pin)
{
    P2 = (P2 &= 0x1f) | (pin<<5);
}

void sys_init()
{
    gpio_init();
    drv_init();
    sys_tick_timer_init();
}
