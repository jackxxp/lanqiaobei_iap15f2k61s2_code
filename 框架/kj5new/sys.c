#include "sys.h"


void sys_latch(u8 drv)
{
    P2 = (P2 & 0x1f) | (drv << 5);
}

void sys_init()
{
    P0M0 = 0x00; P0M1 = 0x00; 
    P1M0 = 0x00; P1M1 = 0x00; 
    P2M0 = 0x00; P2M1 = 0x00; 
    P3M0 = 0x00; P3M1 = 0x00; 
    P4M0 = 0x00; P4M1 = 0x00; 
    P5M0 = 0x00; P5M1 = 0x00; 
    P6M0 = 0x00; P6M1 = 0x00; 
    P7M0 = 0x00; P7M1 = 0x00; 

    sys_latch(0);
    P0 = 0xff;sys_latch(4);sys_latch(0);
    P0 = 0x00;sys_latch(6);sys_latch(0);
    P0 = 0xff;sys_latch(7);sys_latch(0);
    P0 = 0xaf;sys_latch(5);sys_latch(0);

	AUXR &= 0xFB;			//定时器时钟12T模式
	T2L = 0x18;				//设置定时初始值
	T2H = 0xFC;				//设置定时初始值
	AUXR |= 0x10;			//定时器2开始计时
	IE2 |= 0x04;			//使能定时器2中断

    EA = 1;

}