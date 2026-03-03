//sys_task.c
#include "sys_task.h"

/* ========================
   全局 1ms tick
   ======================== */
volatile uint8 sys_tick_ms = 0;

/* 上次运行时间 */
static uint16 last_seg  = 0;
static uint16 last_led  = 0;
static uint16 last_key  = 0;
static uint16 last_misc = 0;

/* ========================
   1ms 中断调用
   ======================== */
void sys_task_isr(void)
{
    sys_tick_ms++;
//    if (sys_tick_ms >= 200)
//    {
//        sys_tick_ms = 0;
//    }
}

/* ========================
   主循环调度器
   ======================== */
void sys_task_run(void)
{
    uint16 now = sys_tick_ms;

    /* 数码管：2ms */
    if ((uint16)(now - last_seg) >= 2)
    {
        last_seg = now;
        drv_seg_run();
    }

    /* LED：5ms */
    if ((uint16)(now - last_led) >= 5)
    {
        last_led = now;
        drv_led_run();
    }

    /* 按键：10ms */
    if ((uint16)(now - last_key) >= 10)
    {
        last_key = now;
        drv_key_run();
    }

    /* 继电器 / 蜂鸣器：50ms */
    if ((uint16)(now - last_misc) >= 50)
    {
        last_misc = now;
        drv_other_run();
    }
}
