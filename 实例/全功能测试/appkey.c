#include "appkey.h"

void appkey_main()
{
	uint8 mode = 1;
	uint8 key_temp;
	
	bit appkey_tick_0 = 1;
	
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
					if(appkey_tick_0){seg_set(4,12);seg_set(5,0);seg_set(6,13);seg_set(7,14);appkey_tick_0 = 0;}
					else{seg_set(4,26);seg_set(5,14);seg_set(6,5);seg_set(7,26);appkey_tick_0 = 1;}						
        }
				  


			} break;
			default:{led_set0();seg_set(2, 22);seg_set(3, 0);seg_set(1, 16);seg_set(7, 16);seg_set(4,16);seg_set(5, 16);seg_set(6, 16);}			
		}
		if (key_temp == 5 ){appkey_key_code_test();}	
	}
}

void appkey_key_code_test()
{
	seg_set0();led_set0();	
	seg_set(0,21);seg_set(1,23);seg_set(2,23);seg_set(3,27);seg_set(4,24);seg_set(5,29);seg_set(6,14);seg_set(7,5);sys_sleep_1s();sys_sleep_1s();
	seg_set(0,5);seg_set(1,4);seg_set(2,16);seg_set(3,16);seg_set(4,11);seg_set(5,10);seg_set(6,12);seg_set(7,20);sys_sleep_1s();sys_sleep_1s();
	seg_set0();
	seg_set(5,16);seg_set(6,0);seg_set(7,0);
	while(1)
	{
		uint8 key_temp;
		key_temp = key_get();
		if(key_temp != 201)
		{
			switch(key_temp)
			{
				case 4:{seg_set(5,16);seg_set(6,0);seg_set(7,4);}break;
				case 5:{seg_set(5,16);seg_set(6,0);seg_set(7,5);}break;
				case 6:{seg_set(5,16);seg_set(6,0);seg_set(7,6);}break;
				case 7:{seg_set(5,16);seg_set(6,0);seg_set(7,7);}break;
				
				case 8:{seg_set(5,16);seg_set(6,0);seg_set(7,8);}break;
				case 9:{seg_set(5,16);seg_set(6,0);seg_set(7,9);}break;
				case 10:{seg_set(5,16);seg_set(6,1);seg_set(7,0);}break;
				case 11:{seg_set(5,16);seg_set(6,1);seg_set(7,1);}break;
				
				case 12:{seg_set(5,16);seg_set(6,1);seg_set(7,2);}break;
				case 13:{seg_set(5,16);seg_set(6,1);seg_set(7,3);}break;
				case 14:{seg_set(5,16);seg_set(6,1);seg_set(7,4);}break;
				case 15:{seg_set(5,16);seg_set(6,1);seg_set(7,5);}break;
				
				case 16:{seg_set(5,16);seg_set(6,1);seg_set(7,6);}break;
				case 17:{seg_set(5,16);seg_set(6,1);seg_set(7,7);}break;
				case 18:{seg_set(5,16);seg_set(6,1);seg_set(7,8);}break;
				case 19:{seg_set(5,16);seg_set(6,1);seg_set(7,9);}break;
				
				case 104:{seg_set(5,21);seg_set(6,0);seg_set(7,4);}break;
				case 105:{seg_set(5,21);seg_set(6,0);seg_set(7,5);}break;
				case 106:{seg_set(5,21);seg_set(6,0);seg_set(7,6);}break;
				case 107:{seg_set(5,21);seg_set(6,0);seg_set(7,7);}break;
				
				case 108:{seg_set(5,21);seg_set(6,0);seg_set(7,8);}break;
				case 109:{seg_set(5,21);seg_set(6,0);seg_set(7,9);}break;
				case 110:{seg_set(5,21);seg_set(6,1);seg_set(7,0);}break;
				case 111:{seg_set(5,21);seg_set(6,1);seg_set(7,1);}break;
				
				case 112:{seg_set(5,21);seg_set(6,1);seg_set(7,2);}break;
				case 113:{seg_set(5,21);seg_set(6,1);seg_set(7,3);}break;
				case 114:{seg_set(5,21);seg_set(6,1);seg_set(7,4);}break;
				case 115:{seg_set(5,21);seg_set(6,1);seg_set(7,5);}break;
				
				case 116:{seg_set(5,21);seg_set(6,1);seg_set(7,6);}break;
				case 117:{seg_set(5,21);seg_set(6,1);seg_set(7,7);}break;
				case 118:{seg_set(5,21);seg_set(6,1);seg_set(7,8);}break;
				case 119:{seg_set(5,21);seg_set(6,1);seg_set(7,9);}break;
			
			}
		}
		if(key_temp == 104)
		{
			break;
		}
	
	
	}
	
}