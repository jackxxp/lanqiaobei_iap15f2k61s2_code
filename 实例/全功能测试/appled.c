#include "appled.h"

void appled_main()
{
	uint8 mode = 1;
	uint8 key_temp;
	uint8 tick = 0;
	
	seg_set0();
	while(1)
	{
		key_temp = key_get();
		if (key_temp == 6 ){mode += 1;if(mode == 10){mode = 1;}}		
		if (key_temp == 7 ){mode -= 1;if(mode == 0){mode = 9;}}
		if (key_temp == 4 ){break;}		
		
		seg_set(7,mode);
		
		switch(mode)
		{
			case 1:
			{
			seg_set(0,16);seg_set(1,16);led_set(0,1);led_set(1,1);led_set(2,1);led_set(3,1);led_set(4,1);led_set(5,1);led_set(6,1);led_set(7,1);
			}break;
			case 2:
			{
			seg_set(0,16);seg_set(1,16);led_set(0,1);led_set(1,0);led_set(2,1);led_set(3,0);led_set(4,1);led_set(5,0);led_set(6,1);led_set(7,0);
			}break;
			case 3:
			{
			seg_set(0,16);seg_set(1,16);
			if(tick<8)
			{
				led_set(tick,1);tick++;
				sys_sleep_100ms();
			}
			if(tick>=8)
			{	
				led_set(tick-8,0);tick++;
				sys_sleep_100ms();
			}
			if(tick == 16)
			{
				tick=0;sys_sleep_100ms();
			}
			}break;
			default:{led_set0();seg_set(0, 22);seg_set(1, 0);seg_set(2, 16);seg_set(3, 16);seg_set(4,16);seg_set(5, 16);seg_set(6, 16);}			
		}
		
	
	}
}