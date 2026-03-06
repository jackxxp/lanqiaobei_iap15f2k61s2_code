//app_main.c

#include "app_main.h"

#include "drv_rtc.h"
#include "drv_temp.h"

uint8 page = 0;
uint8 rtc_h = 23;
uint8 rtc_m = 59;
uint8 rtc_s = 58;
uint16 ds_t = 213;
uint16 set_t = 230;
bit set_mode = 0;
bit relay_sw = 1;

RTC_TimeType rtc_time;

void app_init()
{
	static bit init_ok = 0;
	if(init_ok == 0)
	{
    RTC_Init();
		Temp_Init();
    rtc_time.year = 24;
    rtc_time.month = 3;
    rtc_time.day = 15;
    rtc_time.week = 5;
    rtc_time.hour = 14;
    rtc_time.minute = 01;
    rtc_time.second = 02;    
    RTC_SetTime(&rtc_time);			
		init_ok =1;
	}

}

void seg_display()
{
	if(page == 0)
	{
		drv_seg_set_all(25,1,16,16,16,ds_t/100,ds_t/10%10+32,ds_t%10);
	}
	if(page == 1)
	{
		drv_seg_set_all(25,2,16,rtc_h/10,rtc_h%10,17,rtc_m/10,rtc_m%10);
	}
	if(page == 2)
	{
		drv_seg_set_all(25,3,16,16,16,16,set_t/100,set_t/10%10);
	}
	if(page == 11)
	{
		drv_seg_set_all(25,2,16,rtc_m/10,rtc_m%10,17,rtc_s/10,rtc_s%10);
	}
}
void key_ctrl()
{
	if(drv_key_is(4))
	{
    rtc_time.year = 24;
    rtc_time.month = 3;
    rtc_time.day = 15;
    rtc_time.week = 5;
    rtc_time.hour = 14;
    rtc_time.minute = 59;
    rtc_time.second = 55;    
    RTC_SetTime(&rtc_time);	
	}	
	if(drv_key_is(13))
	{
		set_mode = ~ set_mode;
	}
	if(page == 0)
	{
		if(drv_key_is(12)){page=1;}
	}
	if(page == 1)
	{
		if(drv_key_is(12)){page=2;}
		if(drv_key_get_now() == 17){page=11;}		
	}
	if(page == 2)
	{
		if(drv_key_is(12)){page=0;}
		if(drv_key_is(17) && set_t >100){set_t -= 10;}
		if(drv_key_is(16) && set_t <900){set_t += 10;}
	}
	if(page == 11)
	{
		if(drv_key_get_now() != 17){page=1;}		
	}
}
void mode_run()
{
	drv_led_set(1,~ set_mode);
	if(set_mode == 0)
	{
		if(ds_t >set_t){relay_sw = 1;}
		else{relay_sw = 0;}
		if(set_mode == 1){relay_sw = 0;}
	}
	if(set_mode == 1)
	{
		if(rtc_m == 0 && rtc_s == 0){relay_sw = 1;}
		else{if (rtc_s >= 5){relay_sw = 0;}}
		if(set_mode == 0){relay_sw = 0;}
	}	
}

void led0_ctrl()
{
	if(rtc_m == 0 && rtc_s == 0){drv_led_set(0,1);}
	else{if (rtc_s >= 5){drv_led_set(0,0);}}
}

void led2_ctrl()
{
	if(relay_sw)
	{
		static bit l3 = 0;
		drv_relay_set(1);
		drv_led_set(2,l3);l3 = ~ l3;
	}else
	{drv_relay_set(0);drv_led_set(2,0);}
}

void app_task_100ms()
{
	app_init();
	seg_display();
	key_ctrl();
	mode_run();
	led0_ctrl();
	led2_ctrl();

}
void app_task_500ms()
{
	RTC_GetTime(&rtc_time);
	rtc_h = rtc_time.hour;
	rtc_m = rtc_time.minute;
	rtc_s = rtc_time.second;
	
	ds_t = read_temp_int();
}