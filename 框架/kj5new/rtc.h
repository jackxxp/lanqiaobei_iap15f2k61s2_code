#ifndef __RTC_H__
#define __RTC_H__

#include "sys.h"

sbit RST = P1^3;
sbit SCK = P1^7;
sbit SDA = P2^3;

typedef struct{
    u8 s;
    u8 m;
    u8 h;
    u8 day;
    u8 mon;
    u8 year;
    u8 week;
}rtc_type;

void rtc_init();
void rtc_set(rtc_type *time);
void rtc_get(rtc_type *time);

#endif