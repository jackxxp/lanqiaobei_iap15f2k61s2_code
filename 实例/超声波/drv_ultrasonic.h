#ifndef __DRV_ULTRASONIC_H__
#define __DRV_ULTRASONIC_H__

#include "sys_main.h"

/* 初始化 PCA 超声波 */
void drv_ultrasonic_init(void);

/* 触发一次测距（非阻塞） */
void drv_ultrasonic_trigger(void);

/* 是否测距完成 */
bit drv_ultrasonic_is_done(void);

/* 获取 Echo 高电平时间（us） */
uint16 drv_ultrasonic_get_time_us(void);

/* 获取距离（mm） */
uint16 drv_ultrasonic_get_distance_mm(void);

void drv_ultrasonic_reset(void);

extern volatile uint16 pca_int_cnt;

#endif
