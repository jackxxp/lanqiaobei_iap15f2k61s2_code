//main.c
#include "main.h"

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
	
	sys_tick++;
	if(sys_tick >= 200){sys_tick = 0;}
}



void main()
{
	static uint16 page = 1;
	
	sys_init();
	
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
	
	while(1)
	{	
		uint8 temp;
		while(1)
		{
			temp = key_get();
			seg_set(0,page/10);seg_set(1,page%10+32);
			switch(page)
			{
				case 1:{seg_set(2, 16);seg_set(3, 16);seg_set(4, 16);seg_set(5, 21);seg_set(6,14);seg_set(7, 13);}break;
				case 2:{seg_set(2, 16);seg_set(3, 16);seg_set(4, 16);seg_set(5, 5);seg_set(6,14);seg_set(7, 27);}break;
				case 3:{seg_set(2, 16);seg_set(3, 16);seg_set(4, 16);seg_set(5, 20);seg_set(6,14);seg_set(7, 31);}break;
				default:{seg_set(2, 16);seg_set(3, 16);seg_set(4, 22);seg_set(5, 23);seg_set(6,22);seg_set(7, 14);}			
			}
		
			if (temp == 6 ){page += 1;if(page == 100){page = 1;}}		
			if (temp == 7 ){page -= 1;if(page == 0){page = 99;}}
			if (temp == 5)
			{
				
				switch(page)
				{
					case 1:{appled_main();}break;	
					case 2:{appseg_main();}break;
					case 3:{appkey_main();}break;
				}				
			}		
		}

	}
}