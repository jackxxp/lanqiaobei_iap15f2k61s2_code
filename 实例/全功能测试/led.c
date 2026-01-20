//led.c
#include "led.h"



void led_init()
{
	decoder_set(4);
	P0=0xff;
	decoder_set(0);
}

//static uint8 led_state = 0x00; 

//void led_set(uint8 index, bit value) 
//{
//  if (value)
//	{
//		led_state |= (1 << index);
//	}else
//	{
//		led_state &= ~(1 << index);
//	}
//}

//// 时间片调用（每 1～2ms 一次）
//void led_run(void) 
//{
//  decoder_set(4);
//  P0 = ~led_state; // 共阳：逻辑1 → 物理0
//}


uint8 led_ram[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void led_set(uint8 position, bit value){led_ram[position] = value;}

void led_run()
{
	static uint8 led_tick =0;
	static uint8 led_last =0x00;
	static uint8 led_temp = 0x00;
	
	if(led_ram[led_tick])
	{
		led_temp = led_temp | (0x01<<led_tick++);
	}else
	{
		led_temp = led_temp & ~(0x01<<led_tick++);
	}
	
	if(led_tick >= 8){led_tick = 0;}
	
	if(led_last != led_temp)
	{
		decoder_set(4);
		P0 = ~led_temp;
		decoder_set(0);
		led_last = led_temp;
	}	
}