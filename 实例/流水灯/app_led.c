#include "app_led.h"

void app_led_run() 
{ 
	static uint8 ledapp_tick = 0; 
	if(ledapp_tick < 8) 
	{
		drv_seg_set(0,ledapp_tick/10); 
		drv_seg_set(1,ledapp_tick%10); 
		drv_led_set(ledapp_tick++,1); 
	}
	if(ledapp_tick >= 8) 
	{ 
		drv_seg_set(0,ledapp_tick/10); 
		drv_seg_set(1,ledapp_tick%10); 
		drv_led_set(ledapp_tick++ -8,0); 
	} 
	if(ledapp_tick >= 16) 
	{
		ledapp_tick = 0;
	} 
}