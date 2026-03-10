#include "drv_other.h"

static bit relay_ram = 0;

void drv_other_run()
{
    static u8 other_last = 0xaf;
    u8 other_temp = 0xaf;
    if(relay_ram)
    {
        other_temp = 0xbf;
    }else
    {
        other_temp = 0xaf;
    }
    if(other_last != other_temp)
    {
        P0 = other_temp;y5;y0;
        other_last = other_temp;
    }
}
void drv_relay_set(bit sw)
{
    relay_ram = sw;
}