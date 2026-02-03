//sys_task.h
#ifndef __SYS_TASK_H__
#define __SYS_TASK_H__

#include "sys_main.h"

extern volatile uint8 sys_tick_ms;


void sys_task_isr();
void sys_task_run();

#endif
