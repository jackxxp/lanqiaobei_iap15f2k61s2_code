#ifndef __DIS_H__
#define __DIS_H__

#include "sys.h"

sbit SONIC_TX = P1^0;
sbit SONIC_RX = P1^1;

void dis_init();
u8 dis_get();


#endif