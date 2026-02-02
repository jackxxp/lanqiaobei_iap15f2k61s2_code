// led.c


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

void led_set0()
{
	led_ram[0]=0;led_ram[1]=0;led_ram[2]=0;led_ram[3]=0;led_ram[4]=0;led_ram[5]=0;led_ram[6]=0;led_ram[7]=0;
}


//#include "led.h"

//uint8 led_ram[8] = {0, 0, 0, 0, 0, 0, 0, 0};

//void led_init()
//{
//    decoder_set(4);
//    P0 = 0xFF; // 共阳全灭
//    decoder_set(0);
//}

//void led_set(uint8 position, bit value)
//{
//    led_ram[position] = value;
//}

//void led_run()
//{
//		static uint8 led_last = 0x00; 
//    uint8 led_temp = 0x00;
//    uint8 i; // ✅ 变量声明必须在块开头（C90 要求）

//    // 重建整个 led_temp
//    for (i = 0; i < 8; i++) {
//        if (led_ram[i]) {
//            led_temp |= (1 << i);
//        }
//    }



//    if (led_last != led_temp) {
//        decoder_set(4);
//        P0 = ~led_temp; // ✅ 改为半角 ～
//        decoder_set(0);
//        led_last = led_temp;
//    }
//}

//void led_set0()
//{
//    uint8 i; // ✅ 同样，for 循环变量要提前声明
//    for (i = 0; i < 8; i++) {
//        led_ram[i] = 0;
//    }
//}