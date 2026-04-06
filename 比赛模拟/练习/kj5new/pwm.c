#include "pwm.h"

static u8 pwm_d = 50;

void pwm_init()
{
    AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xF6;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
}

void pwm_isr() interrupt 1
{
    static u8 pwm_tick = 0;

    if(pwm_tick < pwm_d)
    {
        P22 = 1;
    }else
    {
        P22 = 0;
    }
    pwm_tick++;if(pwm_tick >= 100){pwm_tick = 0;}
}

void pwm_set(u8 d)
{
    pwm_d = d;
}