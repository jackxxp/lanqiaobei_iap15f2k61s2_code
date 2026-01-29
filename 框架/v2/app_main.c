//app_main.c
#include "app_main.h"
#include "app_main.h"

static uint16 last_10ms   = 0;
static uint16 last_100ms  = 0;
static uint16 last_1000ms = 0;


//任务
void app_task_1_10ms()
{
   
}

void app_task_2_100ms()
{
   
}

void app_task_3_1000ms()
{
    
}


//调度器
void app_main_run()
{
    uint16 now = sys_tick_ms;

    if ((uint16)(now - last_10ms) >= 10){last_10ms = now;app_task_1_10ms();}
    if ((uint16)(now - last_100ms) >= 100){last_100ms = now;app_task_2_100ms();}
    if ((uint16)(now - last_1000ms) >= 1000){last_1000ms = now;app_task_3_1000ms();}
}