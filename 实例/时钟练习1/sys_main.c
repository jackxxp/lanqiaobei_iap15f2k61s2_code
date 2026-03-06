#include "sys_main.h"

void gpio_init()
{
    P0M0 = 0x00; P0M1 = 0x00; 
    P1M0 = 0x00; P1M1 = 0x00; 
    P2M0 = 0x00; P2M1 = 0x00; 
    P3M0 = 0x00; P3M1 = 0x00; 
}

void drv_init()
{
	sys_decoder(4);P0 = 0xff;
	sys_decoder(6);P0 = 0x00;
	sys_decoder(7);P0 = 0xff;
	sys_decoder(5);P0 = 0xaf;
	sys_decoder(0);

}

void tick_timer_init()
{

	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
	
	EA = 1;

}
void sys_decoder(uint8 pin)
{
	P2 = (P2 & 0x1f) | ((pin << 5) & 0xe0);
}	

void sys_init()
{
	gpio_init();
	drv_init();
	tick_timer_init();
}