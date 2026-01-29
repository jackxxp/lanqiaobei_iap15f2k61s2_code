//y5driver.c
#include "y5driver.h"

// y5driver_ram[0]: 继电器 (P0.4)
// y5driver_ram[1]: 蜂鸣器 (P0.6)
uint8 y5driver_ram[2] = {0, 0};

void y5driver_init()
{
	decoder_set(5);
	P0 = 0xaf;
	decoder_set(0);
}


void relay_set(uint8 sw)
{
    y5driver_ram[0] = (sw != 0) ? 1 : 0;
}

void buzz_set(uint8 sw)
{
    y5driver_ram[1] = (sw != 0) ? 1 : 0;
}

void y5driver_run(void)
{
    static uint8 y5driver_last = 0;
    uint8 new_val = 0;

    if (y5driver_ram[0]) new_val |= (1 << 4);  // P0.4 = 继电器
    if (y5driver_ram[1]) new_val |= (1 << 6);  // P0.6 = 蜂鸣器

    if (y5driver_last != new_val)
    {
        decoder_set(5);
        P0 = new_val;
        decoder_set(0);
        y5driver_last = new_val;
    }
}