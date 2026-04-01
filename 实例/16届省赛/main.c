#include "main.h"

static u16 sys_tick = 0;

static u16 last_led = 0;

static u16 last_app_task_100ms = 0;
static u16 last_app_task_10ms = 0;
static u16 last_app_task_500ms = 0;
static u16 last_app_task_1000ms = 0;

Timer2_Isr(void) interrupt 12
{
    sys_tick++;
		seg_run();
}
void drv_run()
{
    u16 now = sys_tick;
    if(now - last_led >= 5)
    {
        last_led = now;
        led_run();
    }

}

void app_run()
{
    u16 now = sys_tick;
    if(now - last_app_task_100ms >= 100)
    {
        last_app_task_100ms = now;
        app_task_100ms();
    }
    if(now - last_app_task_10ms >= 10)
    {
        last_app_task_10ms = now;
        app_task_10ms();
    }
    if(now - last_app_task_500ms >= 500)
    {
        last_app_task_500ms = now;
        app_task_500ms();
    }
    if(now - last_app_task_1000ms >= 1000)
    {
        last_app_task_1000ms = now;
        app_task_1000ms();
    }
}

void main()
{
    sys_init();
		while(1)
		{
				drv_run();
				app_run();
		}
	
}

