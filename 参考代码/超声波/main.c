#include <STC15F2K60S2.H>
#include "intrins.h"

#define uchar unsigned char
#define uint  unsigned int

sbit TX = P1^0;
sbit RX = P1^1;

/* 数码管段码 */
code uchar DuanMa[] =
{
    0xc0,0xf9,0xa4,0xb0,0x99,
    0x92,0x82,0xf8,0x80,0x90,
    0xbf,0xff
};

uchar SMGa[8] = {11,11,11,11,11,11,11,11};
uchar SMGi = 0;

/* ================== 数码管控制 ================== */
void control(char x, char y)
{
    switch(x)
    {
        case 4: P2 = (P2 & 0x1f) | 0x80; break;
        case 5: P2 = (P2 & 0x1f) | 0xa0; break;
        case 6: P2 = (P2 & 0x1f) | 0xc0; break;
        case 7: P2 = (P2 & 0x1f) | 0xe0; break;
    }
    P0 = y;
    P2 &= 0x1f;
}

void aloneSMG(char pos, char value)
{
    control(7, 0xff);
    control(6, 0x01 << pos);
    control(7, DuanMa[value]);
}

/* ================== 定时器0：1ms ================== */
uchar Wave_Delay = 0;

void T0_Init(void)
{
    AUXR &= 0x7F;
    TMOD &= 0xF0;
    TMOD |= 0x01;
    TH0 = 0xFC;
    TL0 = 0x18;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;
    EA  = 1;
}

void T0_ISR(void) interrupt 1
{
    TH0 = 0xFC;
    TL0 = 0x18;

    aloneSMG(SMGi, SMGa[SMGi]);
    if(++SMGi == 8) SMGi = 0;

    if(++Wave_Delay >= 200)
        Wave_Delay = 0;
}

/* ================== 延时 ================== */
void Delay12us(void)
{
    uchar i = 33;
    while(--i);
}

/* ================== PCA 测距 ================== */
uint Get_Distance(void)
{
    uint time_us;
    uint timeout;

    CMOD = 0x00;
    CCON = 0x00;
    CH = 0;
    CL = 0;

    TX = 1;
    Delay12us();
    TX = 0;

    timeout = 30000;
    while(RX == 0)
        if(--timeout == 0) return 0;

    CH = 0;
    CL = 0;
    CR = 1;

    timeout = 30000;
    while(RX == 1)
        if(--timeout == 0)
        {
            CR = 0;
            return 0;
        }

    CR = 0;

    time_us = ((uint)CH << 8) | CL;
    return time_us / 58;
}

/* ================== 主函数 ================== */
uint Distance = 0;

void main(void)
{
    uint New_Distance = 0;

    T0_Init();

    while(1)
    {
        if(Wave_Delay == 199)
        {
            New_Distance = Get_Distance();

            /* 无效值保护 */
            if(New_Distance > 0)
            {
                /* 指数平滑滤波（核心） */
                Distance = (Distance * 7 + New_Distance * 3) / 10;
            }
        }

        SMGa[0] = 11;
        SMGa[1] = 11;
        SMGa[2] = 11;
        SMGa[3] = 11;
        SMGa[4] = 11;
        SMGa[5] = Distance / 100 % 10;
        SMGa[6] = Distance / 10  % 10;
        SMGa[7] = Distance % 10;
    }
}
