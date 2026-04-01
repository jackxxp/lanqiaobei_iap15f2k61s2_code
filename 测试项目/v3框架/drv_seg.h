//drv_seg.h
#ifndef __DRV_SEG_H__
#define __DRV_SEG_H__

#include "sys_main.h"

void drv_seg_run();
void drv_seg_set(uint8 position, uint8 number);
void drv_seg_set0();
void drv_seg_set_all(uint8 s0,s1,s2,s3,s4,s5,s6,s7);

#endif