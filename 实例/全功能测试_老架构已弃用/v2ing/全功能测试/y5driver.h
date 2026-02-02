//y5driver.h
#ifndef __Y5DRIVER_H__
#define __Y5DRIVER_H__

#include "sys.h"

void y5driver_init();
void relay_set(uint8 sw);
void buzz_set(uint8 sw);
void y5driver_run();


#endif