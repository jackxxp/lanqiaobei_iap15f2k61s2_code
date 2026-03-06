//app_main.c

#include "app_main.h"

void app_task_100ms()
{

	if(drv_key_is(4)){drv_relay_set(1);}
	if(drv_key_is(5)){drv_relay_set(0);}
	if(drv_key_is(6)){drv_buzz_set(1);}
	if(drv_key_is(7)){drv_buzz_set(0);}	

	drv_led_set(0,~(drv_led_get(0)));

	
	drv_seg_set(6,drv_key_get_now()/10);drv_seg_set(7,drv_key_get_now()%10);
}