#include "main.h"

void Timer0_Isr(void) interrupt 1
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