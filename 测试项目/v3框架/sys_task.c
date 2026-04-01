//sys_task.c

#include "sys_task.h"

static uint16 sys_tick_ms = 0;

static uint16 last_led  = 0;
static uint16 last_key  = 0;
static uint16 last_other = 0;

static uint16 last_app_task_1_run = 0;
static uint16 last_app_task_2_run = 0;
static uint16 last_app_task_3_run = 0;

void sys_task_isr()
{
	  sys_tick_ms++;
	
		drv_seg_run();
}
	
void sys_task_drv_run()
{
	uint16 now = sys_tick_ms;
  if (now - last_led >= 5)
  {
		last_led = now;drv_led_run();
  }
	if (now - last_key >= 10)
  {
    last_key = now;drv_key_run();       
  }
  if (now - last_other >= 20)
  {
		last_other = now;drv_other_run();
  }
}

void sys_task_app_run()
{
	uint16 now = sys_tick_ms;
  if (now - last_app_task_1_run >= 100)
  {
		last_app_task_1_run = now;app_task_100ms();
  }
//  if (last_app_task_2_run >= 5)
//  {
//		last_app_task_2_run = now;
//		_nop_;
//  }
//  if (last_app_task_3_run >= 5)
//  {
//		last_app_task_3_run = now;
//		_nop_;
//  }
}