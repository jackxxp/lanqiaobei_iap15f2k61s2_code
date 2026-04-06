#ifndef __SYS_H__
#define __SYS_H__

#include <STC15F2K60S2.H>
#include "intrins.h"

#define u8 unsigned char
#define u16 unsigned int

#include "app.h"

#include "seg.h"
#include "led.h"
#include "otr.h"

void sys_latch(u8 drv);
void sys_init();


#endif