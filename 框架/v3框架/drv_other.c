//drv_other.c
#include "drv_other.h"

uint8 y5driver_ram[2] = {0, 0};  // [0]=继电器, [1]=蜂鸣器

void drv_other_run(void)
{
    static uint8 y5driver_last = 0xaf;  // 初始化为0xAF确保第一次刷新
    uint8 y5driver_temp = 0x00;
    
    if(y5driver_ram[0]) y5driver_temp |= (1 << 4);  // P0.4 = 继电器
    if(y5driver_ram[1]) y5driver_temp |= (1 << 6);  // P0.6 = 蜂鸣器
    
    if(y5driver_last != y5driver_temp)
    {
        y5;                    
        P0 = y5driver_temp;
        y0;                    
        y5driver_last = y5driver_temp;
    }
}
void drv_relay_set(bit sw)
{
    y5driver_ram[0] = sw;
}
void drv_buzz_set(bit sw)
{
    y5driver_ram[1] = sw;
}