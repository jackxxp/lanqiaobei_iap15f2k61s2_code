#include "sys_task.h"

unsigned int sys_tick_ms = 0;

unsigned int last_led =0;
unsigned int last_key =0;
unsigned int last_other =0;

unsigned int last_app_task_1 =0;
unsigned int last_app_task_2 =0;

void sys_task_isr()
{
	sys_tick_ms++;
	drv_seg_run();
}

void sys_task_drv_run()
{
	unsigned int now = sys_tick_ms;
	if(now - last_led >= 5){last_led = now;drv_led_run();}
	if(now - last_key >= 10){last_key = now;drv_key_run();}
	if(now - last_other >= 20){last_other = now;drv_other_run();}
}
void sys_task_app_run()
{
	unsigned int now = sys_tick_ms;
	if(now - last_app_task_1 >= 100){last_app_task_1 = now;app_task_100ms();}
	if(now - last_app_task_2 >= 500){last_app_task_2 = now;app_task_500ms();}
}