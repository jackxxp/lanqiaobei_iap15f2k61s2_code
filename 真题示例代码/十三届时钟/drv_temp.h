#ifndef __DRV_TEMP_H__
#define __DRV_TEMP_H__

#include "sys_main.h"

sbit DQ = P1^4;

void drv_temp_init();
u16 drv_temp_get();

#endif