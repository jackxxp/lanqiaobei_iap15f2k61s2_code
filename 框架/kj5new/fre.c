#include "fre.h"

void fre_init()
{
    AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD |= 0x04;			//设置定时器模式
	TL0 = 0x00;				//设置定时初始值
	TH0 = 0x00;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	

}
u16 fre_get()
{
    u16 fr_out = 0;

    TR0 = 0;
	fr_out= ((TH0<<8)|TL0);
	TH0 = 0;
	TL0 = 0;
	TR0 = 1;

    return fr_out;
}