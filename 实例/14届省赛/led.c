#include "led.h"

u8 led_ram[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void led_run()
{
	static u8 led_tick = 0;
	static u8 led_last = 0x00;
	static u8 led_temp = 0x00;
	
	if(led_ram[led_tick])
	{
		led_temp = led_temp | (0x01<<led_tick++);
	}else
	{
		led_temp = led_temp & ~(0x01<<led_tick++);
	}
	
	if(led_tick >= 8){led_tick = 0;}
	
	if(led_last != led_temp)
	{
		sys_decoder(4);
		P0 = ~led_temp;
		sys_decoder(0);
		led_last = led_temp;
	}	
}

void led_set(u8 position, bit value)
{
	led_ram[position] = value;
}