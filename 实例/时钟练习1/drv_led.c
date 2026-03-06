#include "drv_led.h"

uint8 led_ram[8] = {0,0,0,0,0,0,0,0};

void drv_led_run()
{
	static uint8 led_tick = 0;
	static uint8 led_last = 0x00;
	static uint8 led_temp = 0x00;
	
	if(led_ram[led_tick])
	{
		led_temp = led_temp | (0x01 << led_tick++);
	}else
	{
		led_temp = led_temp & ~ (0x01 << led_tick++);
	}
	led_tick %= 8;
	
	if(led_last != led_temp)
	{
		y4;
		P0 = ~ led_temp;
		y0;
		led_last = led_temp;
	}

}
	

void drv_led_set(uint8 p ,bit sw)
{
	led_ram[p] = sw;
}