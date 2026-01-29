//drv_other.c
#include "drv_other.h"


uint8 y5driver_ram[2] = {0, 0};



void relay_set(uint8 sw)
{
    y5driver_ram[0] = (sw != 0) ? 1 : 0;
}

void buzz_set(uint8 sw)
{
    y5driver_ram[1] = (sw != 0) ? 1 : 0;
}

void drv_other_run(void)
{
    static uint8 y5driver_last = 0;
    uint8 new_val = 0;

    if (y5driver_ram[0]) new_val |= (1 << 4);  // P0.4 = 继电器
    if (y5driver_ram[1]) new_val |= (1 << 6);  // P0.6 = 蜂鸣器

    if (y5driver_last != new_val)
    {
        y5;
        P0 = new_val;
        y0;
        y5driver_last = new_val;
    }
}