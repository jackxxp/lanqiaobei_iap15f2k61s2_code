#ifndef __SYS_H__
#define __SYS_H__

#include <STC15F2K60S2.H>
#include "intrins.h"

#define u8 unsigned char
#define u16 unsigned int

void sys_decoder(u8 pin);
void sys_init();

#include "led.h"
#include "seg.h"
#include "key.h"


#include "app.h"

#endif