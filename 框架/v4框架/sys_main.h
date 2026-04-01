//sys_main.h

#ifndef __SYS_MAIN_H__
#define __SYS_MAIN_H__

#include <STC15F2K60S2.H>
#include "intrins.h"

#define uint8 unsigned char
#define uint16 unsigned int
	
#define u8 unsigned char
#define u16 unsigned int

#define y0 sys_decoder(0)
#define y4 sys_decoder(4)
#define y5 sys_decoder(5)
#define y6 sys_decoder(6)
#define y7 sys_decoder(7)

#include "drv_led.h"
#include "drv_seg.h"
#include "drv_other.h"
#include "drv_key.h"

#include "sys_task.h"
#include "app_main.h"

void sys_decoder(uint8 pin);
void sys_init();

#endif