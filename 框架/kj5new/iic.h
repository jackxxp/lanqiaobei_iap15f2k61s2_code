#ifndef __IIC_H__
#define __IIC_H__

#include "sys.h"

sbit sda = P2^1;
sbit scl = P2^0;

u8 eeprom_r(u8 addr);
void eeprom_w(u8 addr, u8 dat);
u8 adc(u8 add);
void dac(u8 v);

#endif