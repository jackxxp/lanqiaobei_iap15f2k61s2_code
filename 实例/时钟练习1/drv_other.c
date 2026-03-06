#include "drv_other.h"

uint8 other_ram[2] = {0,0};


void drv_other_run()
{
	static uint8 other_last = 0xaf; 
	uint8 other_temp = 0x00;
	
	if(other_ram[0])
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
	other_ram[0] = sw;
}