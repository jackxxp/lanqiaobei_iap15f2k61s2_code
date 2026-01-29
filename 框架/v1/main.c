//main.c
#include "main.h"

uint8 run_flag[5]={0,0,0,0,0};

void sys_timer_1ms() interrupt 3
{
	static uint8 sys_tick = 0;
	
	if(sys_tick % 10 == 0)
	{
		app_tick_run();
	}	
	
	if(sys_tick % 3 == 0)
	{
		led_run();
	}
	if(sys_tick % 2 == 0)
	{
		seg_run();
	}
	if(sys_tick % 10  == 0)
	{
		key_run();
	}
	if(sys_tick % 50  == 0)
	{
		y5driver_run();
	}	
	sys_tick %= 200;
}



void main()
{
	
	sys_init();
	
	while(1)
	{
	
	}
	seg_set_all(5,26,12,16,2,12,25,25);
	led_set(0,1);sys_sleep_100ms();
	led_set(1,1);sys_sleep_100ms();
	led_set(2,1);sys_sleep_100ms();
	led_set(3,1);sys_sleep_100ms();
	led_set(4,1);sys_sleep_100ms();
	led_set(5,1);sys_sleep_100ms();
	led_set(6,1);sys_sleep_100ms();
	led_set(7,1);sys_sleep_100ms();
	seg_set0();
	seg_set_all(25,14,29,16,16,2+32,0,1);
	sys_sleep_1s();seg_set0();led_set0();
	relay_set(1);sys_sleep_100ms();	buzz_set(1);sys_sleep_100ms();buzz_set(0);sys_sleep_100ms();relay_set(0);
	

}