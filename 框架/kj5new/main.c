#include "sys.h"

static u8 volatile sys_tick_ms = 0;
static u8 volatile sys_tick_10ms = 0;


static u8 xdata task_10ms_last = 0;
static u8 xdata task_100ms_last = 0;
static u8 xdata task_500ms_last = 0;

void sys_tick_isr() interrupt 12
{
    seg_run();
    sys_tick_ms++;
    if(sys_tick_ms >= 10)
    {
        sys_tick_ms = 0;
        sys_tick_10ms++;
    }
}

void main()
{
    static u8 now_time = 0;
    sys_init();
    while(1)
    {
        now_time = sys_tick_10ms;
        if(now_time - task_10ms_last >= 1)
        {
            task_10ms_last = now_time;
            app_10ms_task();
        }
        if(now_time - task_100ms_last >= 10)
        {
            task_100ms_last = now_time;
            app_100ms_task();
        }
        if(now_time - task_500ms_last >= 50)
        {
            task_500ms_last = now_time;
            app_500ms_task();
    }
    }
}
