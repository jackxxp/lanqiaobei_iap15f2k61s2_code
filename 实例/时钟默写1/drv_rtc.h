#ifndef __DRV_RTC_H__
#define __DRV_RTC_H__

#include "sys_main.h"

sbit RST = P1^3;
sbit SCK = P1^7;
sbit SDA = P2^3;

typedef struct{
	u8 s;
	u8 m;
	u8 h;
}drv_rtc_type;

void drv_rtc_init();
void drv_rtc_set(drv_rtc_type *time);
void drv_rtc_get(drv_rtc_type *time);

#endif