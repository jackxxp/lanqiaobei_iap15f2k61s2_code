#include "led.h"

void led(u8 p ,bit sw)
{
    static u8 led_temp = 0x00;
    static u8 led_last = 0xff;

    if(sw)
    {
        led_temp |= (0x01 << p);
    }else
    {
        led_temp &= ~(0x01 << p);
    }

    if(led_last != led_temp)
    {
        P0 = ~ led_temp;sys_latch(4);sys_latch(0);
        led_last = led_temp;
    }
}
