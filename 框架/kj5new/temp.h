#ifndef __TEMP_H__
#define __TEMP_H__

#include "sys.h"

sbit DQ = P1^4;

void temp_init();
u16 temp_get();
#endif