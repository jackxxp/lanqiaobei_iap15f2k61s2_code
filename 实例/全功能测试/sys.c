//sys.c
#include "sys.h"

void sys_init()
{
	gpio_init();
	
	decoder_init();
	led_init();
	seg_init();
	
	sys_timer_init();

}

void gpio_init()
{
	P0M0 = 0x00;
  P0M1 = 0x00;
  P1M0 = 0x00;
  P1M1 = 0x00;
	P2M0 = 0x00;
	P2M1 = 0x00;
	P3M0 = 0x00;
	P3M1 = 0x00;
	P4M0 = 0x00;
	P4M1 = 0x00;
	P5M0 = 0x00;
	P5M1 = 0x00;
	P6M0 = 0x00;
	P6M1 = 0x00;
	P7M0 = 0x00;
	P7M1 = 0x00;
}

void sys_timer_init()
{
  AUXR &= 0xBF; // 定时器时钟12T模式
  TMOD &= 0x0F; // 设置定时器模式
  TL1 = 0x18;   // 设置定时初始值
  TH1 = 0xFC;   // 设置定时初始值
  TF1 = 0;      // 清除TF1标志
  TR1 = 1;      // 定时器1开始计时
  ET1 = 1;      // 使能定时器1中断
	
	EA = 1;
}

void sys_sleep_1s()//12mhz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 46;
	j = 153;
	k = 245;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void sys_sleep_100ms()//12mhz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 144;
	k = 71;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

