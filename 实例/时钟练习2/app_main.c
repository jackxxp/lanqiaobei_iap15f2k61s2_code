#include "app_main.h"

#include "drv_rtc.h"
#include "drv_temp.h"

uint8 app_page = 0;
uint16 d_t = 213;
uint8 time_s = 50;
uint8 time_m = 12;
uint8 time_h = 15;
uint16 set_temp = 230;
bit relay_sw = 0;
bit ctrl_mode = 0;

drv_rtc_type rtc;

void app_init()
{
	static bit initok = 0;
	if(initok == 0)
	{
		initok = 1;
		drv_rtc_init();
		drv_temp_init();
	}
}
void debug_set_time()
{
	rtc.rtc_s = 55;
	rtc.rtc_m = 59;
	rtc.rtc_h = 19;
	drv_rtc_set(&rtc);
}

void seg_display()
{
	switch(app_page)
	{
		case 0:drv_seg_set_all(25,1,16,16,16,d_t/100,(d_t%100/10)+32,d_t%10);break;
		case 1:drv_seg_set_all(25,2,16,time_h/10,time_h%10,17,time_m/10,time_m%10);break;
		case 2:drv_seg_set_all(25,3,16,16,16,16,set_temp/100,set_temp%100/10);break;
		case 9:drv_seg_set_all(29,17,relay_sw,16,5,17,time_s/10,time_s%10);break;
	}
}
void key_ctrl()
{
	if(drv_key_is(13)){ctrl_mode ^= 1;}
	switch(app_page)
	{
		case 0:if(drv_key_is(12)){app_page = 1;}break;
		case 1:if(drv_key_is(12)){app_page = 2;}if(drv_key_is(17)){app_page = 9;}break;
		case 2:if(drv_key_is(12)){app_page = 0;}if(drv_key_is(17) && set_temp > 100){set_temp -= 10;}if(drv_key_is(16) && set_temp < 990){set_temp += 10;}break;
		case 9:if(drv_key_is(17)){app_page = 1;}if(drv_key_is(16)){debug_set_time();}break;
	}
}
void relay_ctrl()
{
	static bit led2 = 0;
	if(relay_sw)
	{
		drv_relay_set(1);
		drv_led_set(2,led2);
		led2 ^= 1;
	}else
	{
		drv_relay_set(0);
		drv_led_set(2,0);
	}
}
void led_0_ctrl()
{
	if(time_m == 0 && time_s == 0){drv_led_set(0,1);}
	if(time_s > 4){drv_led_set(0,0);}
}
void mode_run()
{
	drv_led_set(1,~ ctrl_mode);
	if(ctrl_mode)
	{
		if(time_m == 0 && time_s == 0){relay_sw = 1;}
		if(time_s > 4){relay_sw = 0;}		
	}else
	{
		if(d_t > set_temp){relay_sw = 1;}	
		else{relay_sw = 0;}
	}
}	
void app_task_100ms()
{
	app_init();
	seg_display();
	key_ctrl();
	relay_ctrl();
	led_0_ctrl();
	mode_run();
}
void app_task_500ms()
{
	drv_rtc_get(&rtc);
	time_s = rtc.rtc_s;
	time_m = rtc.rtc_m;
	time_h = rtc.rtc_h;
	d_t = drv_temp_get();
}