#ifndef __DRV_RTC_H__
#define __DRV_RTC_H__

#include "sys_main.h"

sbit SDA = P2^3;
sbit SCK = P1^7;
sbit RST= P1^3;


typedef struct
{
	uint8 rtc_s;
	uint8 rtc_m;
	uint8 rtc_h;
}rtc_timetype;

void drv_rtc_init();
void drv_rtc_set(rtc_timetype *time);
void drv_rtc_get(rtc_timetype *time);

#endif