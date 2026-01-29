//drv_led.h
#ifndef __DRV_LED_H__
#define __DRV_LED_H__

#include "sys_main.h"

void drv_led_run();
void drv_led_set(uint8 position, bit value);
void drv_led_set0();

#endif