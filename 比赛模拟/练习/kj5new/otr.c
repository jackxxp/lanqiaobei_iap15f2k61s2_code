#include "otr.h"

static u8 otr_temp = 0xaf;
static u8 otr_last = 0xff;


void relay(bit sw)
{

    if(sw)
    {
        otr_temp |= 0x10;// 0001 0000
    }else
    {
        otr_temp &= ~ 0x10;// 1110 1111
    }

    if(otr_last != otr_temp)
    {
        P0 = otr_temp;sys_latch(5);sys_latch(0);
        otr_last = otr_temp;
    }
}

void buzz(bit sw)
{
    if(sw)
    {
        otr_temp |= 0x40;//0100 0000
    }else
    {
        otr_temp &= ~ 0x40;//1011 1111
    }  
    if(otr_last != otr_temp)
    {
        P0 = otr_temp;sys_latch(5);sys_latch(0);
        otr_last = otr_temp;
    }
}

