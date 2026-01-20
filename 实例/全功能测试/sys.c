//sys.c
#include "sys.h"

void sys_init()
{
	decoder_init();
	led_init();
	seg_init();
	

}

void sys_sleep_1s()//12mhz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 46;
	j = 153;
	k = 245;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
