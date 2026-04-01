#include "ne555.h"

void ne555_init()
{

    AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD |= 0x04;			//设置定时器模式
	TL0 = 0xff;				//设置定时初始值
	TH0 = 0xff;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
	PT0 =1;

}

