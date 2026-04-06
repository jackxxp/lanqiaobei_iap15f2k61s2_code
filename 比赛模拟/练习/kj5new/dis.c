#include "dis.h"

void Delay12us(void)    // @12.000MHz，实测12.166μs
{
    unsigned char i;
    _nop_();
    _nop_();
    i = 33;
    while (--i);
}



void Send40kHz(void)
{
    u8 i;
    
    EA = 0;                     // 关中断，保证时序
    for(i = 0; i < 8; i++) {
        SONIC_TX = 1;
        Delay12us();            // 高电平 12.166μs
        SONIC_TX = 0;
        Delay12us();            // 低电平 12.166μs
    }
    EA = 1;
}



void dis_init()
{
	AUXR &= 0xBF;			//定时器时钟12T模式
	TMOD &= 0x0F;			//设置定时器模式
	TL1 = 0x00;				//设置定时初始值
	TH1 = 0x00;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
	TR1 = 0;				//定时器1tz计时
    ET1 = 0;
}
u8 dis_get()
{
    u8 distance = 0;
    u16 time = 0;

    TR1 = 0;
	TL1 = 0;TH1 = 0;
    TF1 = 0;

    Send40kHz();

    while(SONIC_RX == 0);

    TR1 = 1;
	

    while(SONIC_RX == 1 && TF1 == 0);
    
    TR1 = 0;
    
    if(TF1 == 1) {return 255;}

    time = (TH1 << 8) | TL1;
    return (unsigned int)(time * 0.017);

}