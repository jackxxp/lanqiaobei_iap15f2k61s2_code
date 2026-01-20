//led.h
#ifndef __LED_H__
#define __LED_H__

#include "sys.h"
#include "decoder.h"

void led_init();
void led_set(uint8 position, bit value);
void led_run();

#endif