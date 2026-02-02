#include "appseg.h"


void appseg_main()
{
	uint8 mode = 1;
	uint8 key_temp;
	uint8 appseg_tick_0 = 0;
	
	seg_set0();led_set0();
	while(1)
	{
		
		key_temp = key_get();
		if (key_temp == 6 ){mode += 1;if(mode == 10){mode = 1;}seg_set0();led_set0();}		
		if (key_temp == 7 ){mode -= 1;if(mode == 0){mode = 9;}seg_set0();led_set0();}
		if (key_temp == 4 ){seg_set0();led_set0();break;}		
			
		seg_set(0,mode+32);
		
		switch(mode)
		{
      case 1:
      {
             
        if(get_1s_flag())
        {
					seg_set(4,appseg_tick_0/10);seg_set(5,appseg_tick_0%10);seg_set(6,17);seg_set(7,appseg_tick_0++);
					if(appseg_tick_0 >= 43){appseg_tick_0 = 0;}
				} break;

			} break;
			default:{led_set0();seg_set(2, 22);seg_set(3, 0);seg_set(1, 16);seg_set(7, 16);seg_set(4,16);seg_set(5, 16);seg_set(6, 16);}			
		}

	}
}