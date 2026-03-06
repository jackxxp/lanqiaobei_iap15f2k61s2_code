#include "app_main.h"

#include "drv_rtc.h"
#include "drv_temp.h"

static uint8 page = 0;
static uint16 d_temp = 231;
static uint8 time_h = 12;
static uint8 time_m = 59;
static uint8 time_s = 55;
static uint16 set_temp = 230;
bit ctrl_mode = 0;
bit relay_sw = 0;

rtc_timetype rtc_time;

void app_init()
{
	static bit init_ok = 0;
	if(init_ok != 1)
	{
		init_ok = 1;
		drv_rtc_init();
		drv_temp_init();
	}
}

void test_set_time()
{
		rtc_time.rtc_s = 55;rtc_time.rtc_m = 59;rtc_time.rtc_h = 10;
		drv_rtc_set(&rtc_time);
}

void seg_display()
{
	switch(page)
	{
		case 0:drv_seg_set_all(25,1,16,16,16,d_temp/100,(d_temp%100/10)+32,d_temp%10);break;
		case 1:drv_seg_set_all(25,2,16,time_h/10,time_h%10,17,time_m/10,time_m%10);break;
		case 2:drv_seg_set_all(25,3,16,16,16,16,set_temp/100,set_temp/10%10);break;
		case 11:drv_seg_set_all(25,2,16,16,16,16,time_s/10,time_s%10);break;
	}
}
void key_ctrl()
{
	if(drv_key_is(13)){ctrl_mode = ~ ctrl_mode;}
	switch(page)
	{
		case 0:if(drv_key_is(12)){page = 1;}break;
		case 1:if(drv_key_is(12)){page = 2;}if(drv_key_is(17)){page = 11;}break;
		case 2:if(drv_key_is(12)){page = 0;}if(drv_key_is(17) && set_temp > 100){set_temp -= 10;}if(drv_key_is(16) && set_temp < 990){set_temp +=10;}break;
		case 11:if(drv_key_is(17)){page = 1;}if(drv_key_is(16)){test_set_time();}break;
	}
}

void relay_ctrl()
{	
	static bit l3 = 0;
	if(relay_sw)
	{
		drv_led_set(2,l3);
		l3 = ~ l3;
		drv_relay_set(1);
	}else
	{
		drv_led_set(2,0);
		drv_relay_set(0);
	}
}
void led1_ctrl()
{
	if(time_m == 0 & time_s == 0){drv_led_set(0,1);}
	if(time_s > 4){drv_led_set(0,0);}
}

void mode_run()
{
	drv_led_set(1,~ ctrl_mode);
	if(ctrl_mode)
	{
		if(time_m == 0 & time_s == 0){relay_sw = 1;}
		if(time_s > 4){relay_sw = 0;}		
	}else
	{
		if(d_temp > set_temp){relay_sw = 1;}
		else{relay_sw = 0;}
	}
}


void app_task_100ms()
{
	app_init();
	seg_display();
	key_ctrl();
	relay_ctrl();
	led1_ctrl();
	mode_run();
}
void app_task_500ms()
{
	drv_rtc_get(&rtc_time);
	time_h = rtc_time.rtc_h;time_m = rtc_time.rtc_m;time_s = rtc_time.rtc_s;
	d_temp = drv_temp_get();
}