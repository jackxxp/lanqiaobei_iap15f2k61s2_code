//app_task_1.c
#include "app_task_1.h"

void app_task_1_run()
{
	uint8 key_z;
	key_z = drv_key_get();
	if(key_z != 201)
	{
	drv_led_set(7,0);	
	drv_seg_set(0,key_z/100);
	drv_seg_set(1,key_z/10%10);
	drv_seg_set(2,key_z%10);	
	}else
	{
			drv_led_set(7,1);	
	}
}