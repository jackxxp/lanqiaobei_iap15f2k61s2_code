//app_task_1.c
#include "app_task_1.h"

#include "drv_rtc.h"

uint8 task1_tick = 0;
uint8 page = 0;
uint8 rtc_h = 23;
uint8 rtc_m = 59;
uint8 rtc_s = 58;
uint16 ds_t = 213;
uint16 set_t = 230;
bit set_mode = 0;
bit relay = 0;

RTC_TimeType rtc_time;


void app_task_1_run()
{
	static uint8 rtc_read_tick = 0;
	
	
	if(task1_tick == 0)
	{
		RTC_Init();
    rtc_time.year = 24;      // 2024年
    rtc_time.month = 3;      // 3月
    rtc_time.day = 15;       // 15日
    rtc_time.week = 5;       // 星期五（1=星期一，7=星期日）
    rtc_time.hour = 14;      // 14时
    rtc_time.minute = 30;    // 30分
    rtc_time.second = 0;     // 0秒
		task1_tick = 1;
	}
	if(task1_tick == 1)
	{	
		uint8 key_p = drv_key_get();
		if(key_p == 13){set_mode = ~ set_mode;key_p = 200;}
		drv_led_set(1,~ set_mode);
		
		if(relay)
		{
			static bit l3 = 0;
			relay_set(1);
			drv_led_set(2,l3);l3 = ~ l3;
		}else
		{relay_set(0);drv_led_set(2,0);}
		
		if(rtc_m == 0 && rtc_s == 0){drv_led_set(0,1);}
		else{if (rtc_s >= 5){drv_led_set(0,0);}}
		
		
		if(rtc_read_tick++ == 4)
		{
			RTC_GetTime(&rtc_time);
			rtc_h = rtc_time.hour;
			rtc_m = rtc_time.minute;
			rtc_s = rtc_time.second;
		}if(rtc_read_tick >= 5){rtc_read_tick = 0;}
		
		
		if(set_mode == 0)
		{
			if(ds_t >set_t){relay = 1;}
			else{relay = 0;}
			if(set_mode == 1){relay = 0;}
		}
		if(set_mode == 1)
		{
			if(rtc_m == 0 && rtc_s == 0){relay = 1;}
			else{if (rtc_s >= 5){relay = 0;}}
			if(set_mode == 0){relay = 0;}
		}	
		
		
		if (page == 0)
		{
			drv_seg_set_all(25,1,16,16,16,16,16,16);
			drv_seg_set(5,ds_t/100);drv_seg_set(6,(ds_t%100/10)+32);drv_seg_set(7,ds_t%100%10);
			if(key_p == 12){page = 1;key_p=200;}
			
		
		}
		if (page == 1)
		{
			drv_seg_set_all(25,2,16,16,16,17,16,16);
			drv_seg_set(3,rtc_h/10);drv_seg_set(4,rtc_h%10);drv_seg_set(6,rtc_m/10);drv_seg_set(7,rtc_m%10);

			if(drv_key_get_now() == 17){page = 11;}		
			if(key_p == 12){page = 2;key_p=200;}

		}
		if (page == 2)
		{
			drv_seg_set_all(25,3,16,16,16,16,16,16);
			drv_seg_set(6,set_t/10/10);drv_seg_set(7,set_t/10%10);
			
			if(key_p == 12){page = 0;key_p=200;}
			if(key_p == 17){if(set_t > 100){set_t -= 10;key_p=200;}}
			if(key_p == 16){if(set_t < 990){set_t += 10;key_p=200;}}


		}
		if (page == 11)
		{
			drv_seg_set_all(25,2,16,16,16,17,16,16);
			drv_seg_set(3,rtc_m/10);drv_seg_set(4,rtc_m%10);drv_seg_set(6,rtc_s/10);drv_seg_set(7,rtc_s%10);
			
			if(drv_key_get_now() == 200){page = 1;}
		
		}
	
	}
}