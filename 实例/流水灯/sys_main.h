//sys_main.h
#ifndef __SYS_MAIN_H__
#define __SYS_MAIN_H__

#include <STC15F2K60S2.H> //引入STC MCU头文件
#include "intrins.h" //引入一些MCU指令


#define uint8 unsigned char //定义常用数据类型
#define uint16 unsigned int //定义常用数据类型
	
void sys_main_mcu_init();
void sys_main_decoder_set(uint8 pin);

#define y0 sys_main_decoder_set(0)
#define y4 sys_main_decoder_set(4)
#define y5 sys_main_decoder_set(5)
#define y6 sys_main_decoder_set(6)
#define y7 sys_main_decoder_set(7)

#include "drv_led.h"
#include "drv_seg.h"
#include "drv_key.h"
#include "drv_other.h"

#include "sys_task.h"
#include "app_main.h"

#endif