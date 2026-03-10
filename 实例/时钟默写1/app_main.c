#include "app_main.h"

#include "drv_rtc.h"
#include "drv_temp.h"

u8 page = 0;
u16 d_t =213;
u8 time_s =0;
u8 time_m =0;
u8 time_h =7;
u16 set_temp =230;
bit relay_sw = 0;
bit mode = 0;

drv_rtc_type rtc;


void app_init()
{
	static bit initok = 0;
	if(initok != 1)
	{
		initok =1;
		drv_rtc_init();
		drv_temp_init();		
	}
	
}
void debug_time_set()
{
	rtc.s = 55;
	rtc.m = 59;
	rtc.h = 22;
	drv_rtc_set(&rtc);
}
void seg_display()
{
	switch(page)
	{
		case 0:{drv_seg_set_all(25,1,16,16,16,d_t/100,d_t%100/10+32,d_t%10);break;}
		case 1:{drv_seg_set_all(25,2,16,time_h/10,time_h%10,17,time_m/10,time_m%10);break;}
		case 2:{drv_seg_set_all(25,3,16,16,16,16,set_temp/100,set_temp%100/10);break;}
		case 11:{drv_seg_set_all(relay_sw,16,16,16,16,16,time_s/10,time_s%10);break;}
	}
}
void key_ctrl()
{
	if(drv_key_is(13)){mode ^=1;}
	switch(page)
	{
		case 0:if(drv_key_is(12)){page = 1;}break;
		case 1:if(drv_key_is(12)){page = 2;}if(drv_key_is(17)){page = 11;}break;
		case 2:if(drv_key_is(12)){page = 0;}if(drv_key_is(17)&&set_temp>100){set_temp-=10;}if(drv_key_is(16)&&set_temp<990){set_temp+=10;}break;
		case 11:if(drv_key_is(16)){debug_time_set();}if(drv_key_is(17)){page = 1;}break;
	}	
}
void led_0_ctrl()
{
	if(time_m == 0 &&time_s == 0){drv_led_set(0,1);}
	if(time_s > 4){drv_led_set(0,0);}	
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
void mode_run()
{
	drv_led_set(1,~mode);
	if(mode)
	{
		if(time_m == 0 &&time_s == 0){relay_sw = 1;}
		if(time_s > 4){relay_sw = 0;}			
	}else
	{
		if(d_t > set_temp){relay_sw=1;}
		else{relay_sw=0;}
	}

}

void app_task_100ms()
{
	app_init();
	seg_display();
	key_ctrl();
	led_0_ctrl();
	relay_ctrl();
	mode_run();
}
void app_task_500ms()
{
	drv_rtc_get(&rtc);
	time_s = rtc.s;
	time_m = rtc.m;	
	time_h = rtc.h;
	d_t = drv_temp_get();
}