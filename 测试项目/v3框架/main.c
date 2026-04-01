//main.c

#include "main.h"

void timer_0_isr() interrupt 1
{
	sys_task_isr();
}

void main()
{
	sys_init();

	while(1)
	{
		sys_task_drv_run();
		sys_task_app_run();
	}
}