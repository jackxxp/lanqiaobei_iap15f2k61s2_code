#ifndef __I2C_H__
#define __I2C_H__

#include "sys.h"

sbit scl = P2^0;
sbit sda = P2^1;

u8 adc_get();
#endif