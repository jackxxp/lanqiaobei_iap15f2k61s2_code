//app_main.c
#include "app_main.h"

static uint8 last_10ms   = 0;
static uint8 last_100ms  = 0;

//任务
void app_task_1_10ms()
{
   
}

void app_task_2_100ms()
{
   app_task_1_run();
}


//调度器
void app_main_run()
{
    uint8 now = sys_tick_ms;

    if ((uint8)(now - last_10ms) >= 10){last_10ms = now;app_task_1_10ms();}
    if ((uint8)(now - last_100ms) >= 100){last_100ms = now;app_task_2_100ms();}
}