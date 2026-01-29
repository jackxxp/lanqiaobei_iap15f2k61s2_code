//main.c
#include "main.h"

void timer1_isr(void) interrupt 3
{
	sys_task_isr();
}

void main()
{
    sys_main_mcu_init();//系统初始化
    while (1)
    {
			sys_task_run();
			app_main_run();
    }
}
