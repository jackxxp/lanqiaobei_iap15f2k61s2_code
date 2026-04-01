//drv_led.h
#ifndef __DRV_LED_H__
#define __DRV_LED_H__

#include "sys_main.h"

void drv_led_run();
void drv_led_set(uint8 position, bit value);
void drv_led_set0();
void drv_led_set_all(uint8 p0,p1,p2,p3,p4,p5,p6,p7);
bit drv_led_get(uint8 position);

#endif