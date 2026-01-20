//sys.h
#ifndef __SYS_H__
#define __SYS_H__

#include <STC15F2K60S2.H>
#include "intrins.h"

#define uint8 unsigned char
#define uint16 unsigned int
	
#include "decoder.h"
#include "led.h"
#include "seg.h"
#include "key.h"

void sys_init();
void sys_sleep_1s();
void sys_sleep_100ms();

void gpio_init();
void sys_timer_init();

#endif