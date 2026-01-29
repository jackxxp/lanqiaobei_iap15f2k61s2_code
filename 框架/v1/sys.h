//sys.h
#ifndef __SYS_H__
#define __SYS_H__

#include <STC15F2K60S2.H>
#include "intrins.h"

#define uint8 unsigned char
#define uint16 unsigned int
	
#include "decoder.h"
#include "y5driver.h"
#include "led.h"
#include "seg.h"
#include "key.h"

void sys_init();
void sys_sleep_1s();
void sys_sleep_100ms();
//void sys_sleep_1ms();

void app_tick_run();
//void app_tick_set0();
bit get_100ms_flag(void);
bit get_1s_flag(void);


void gpio_init();
void sys_timer_init();

#endif