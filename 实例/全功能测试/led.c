//led.c
#include "led.h"

void led_init()
{
	decoder_set(4);
	P0=0xff;
	decoder_set(0);

}