#include "drv_led.h"

static u8 led_ram[8] = {0,0,0,0,0,0,0,0};

void drv_led_run()
{
    static led_tick = 0;
    static led_last = 0x00;
    static led_temp = 0x00;
    if(led_ram[led_tick])
    {
        led_temp |= (0x01<<led_tick);
    }else
    {
        led_temp &= ~(0x01<<led_tick);
    }
    if(led_last != led_temp)
    {
        P0 = ~ led_temp;y4;y0;
        led_last = led_temp;
    }
    led_tick++;led_tick %= 8;
}
void drv_led_set(u8 p,bit sw)
{
    led_ram[p] = sw;
}