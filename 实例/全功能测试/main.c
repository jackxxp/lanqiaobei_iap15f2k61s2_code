//main.c
#include "main.h"

void sys_timer_1ms() interrupt 3
{
	static uint8 sys_tick = 0;
	
	if(sys_tick % 3)
	{
		led_run();
	}
	if(sys_tick % 2)
	{
		seg_run();
	}

	sys_tick++;
	if(sys_tick >= 200){sys_tick = 0;}
}



void main()
{
	sys_init();
	seg_set(0, 5);seg_set(1, 26);seg_set(2, 12);seg_set(3, 16);seg_set(4, 2);seg_set(5, 12);seg_set(6,25);seg_set(7, 25);
	sys_sleep_1s();
	seg_set0();
	while(1)
	{
		sys_sleep_1s();
		seg_set(3, 0);
		led_set(1, 1);
		sys_sleep_1s();	
		led_set(5, 1);
		seg_set(3, 1);
		sys_sleep_1s();
		led_set(5, 0);
		sys_sleep_1s();
		led_set(1, 0);
	
		
		
	}
}