//seg.h
#ifndef __SEG_H__
#define __SEG_H__

#include "sys.h"

void seg_init();
void seg_set(uint8 position, uint8 number);
void seg_run();
void seg_set0();
void seg_set_all(uint8 s0,s1,s2,s3,s4,s5,s6,s7);

#endif