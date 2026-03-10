#include "drv_other.h"

bit other_ram = 0;

void drv_other_run()
{
	static other_temp = 0xaf;
	static other_last = 0xaf;
	
	if(other_ram)
	{
		other_temp = 0xbf;
	}else
	{
		other_temp = 0xaf;
	}
	if(other_last != other_temp)
	{
		y5;P0 = other_temp;y0;
		other_last = other_temp;
	}
}
void drv_relay_set(bit sw)
{
	other_ram = sw;
}