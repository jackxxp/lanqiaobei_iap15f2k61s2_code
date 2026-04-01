//sys_task.h

#ifndef __SYS_TASK_H__
#define __SYS_TASK_H__

#include "sys_main.h"

void sys_task_isr();
void sys_task_drv_run();
void sys_task_app_run();

#endif