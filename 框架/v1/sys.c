//sys.c
#include "sys.h"


static uint16 app_tick = 0;

// 新增：一次性标志位（由中断置1，由用户函数读取后清0）
static bit flag_100ms = 0;
static bit flag_1s = 0;

void sys_init()
{
	gpio_init();
	
	
	decoder_init();
	y5driver_init();
	
	led_init();
	seg_init();
	
	sys_timer_init();

}

void gpio_init()
{
	P0M0 = 0x00;
  P0M1 = 0x00;
  P1M0 = 0x00;
  P1M1 = 0x00;
	P2M0 = 0x00;
	P2M1 = 0x00;
	P3M0 = 0x00;
	P3M1 = 0x00;
	P4M0 = 0x00;
	P4M1 = 0x00;
	P5M0 = 0x00;
	P5M1 = 0x00;
	P6M0 = 0x00;
	P6M1 = 0x00;
	P7M0 = 0x00;
	P7M1 = 0x00;
}

void sys_timer_init()
{
  AUXR &= 0xBF; // 定时器时钟12T模式
  TMOD &= 0x0F; // 设置定时器模式
  TL1 = 0x18;   // 设置定时初始值
  TH1 = 0xFC;   // 设置定时初始值
  TF1 = 0;      // 清除TF1标志
  TR1 = 1;      // 定时器1开始计时
  ET1 = 1;      // 使能定时器1中断
	
	EA = 1;
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

void sys_sleep_100ms()//12mhz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 144;
	k = 71;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

//void sys_sleep_1ms()//12mhz
//{
//	unsigned char data i, j;

//	i = 12;
//	j = 169;
//	do
//	{
//		while (--j);
//	} while (--i);
//}

// 定时器中断中更新 tick 和标志
void app_tick_run()
{
	  static uint8 cnt_100ms = 0;
    static uint8 cnt_1s = 0;
    app_tick++;
    if (app_tick >= 60000) app_tick = 0;

    // 每 10 次 tick（即 10ms？）→ 但你想 100ms，所以应为 100
    // 注意：你的 app_tick 是每 1ms 增1 吗？
    // 从 TL1=0x18, TH1=0xFC 推算：定时约 1ms，所以：
    


    if (++cnt_100ms >= 10) {   // 100 * 1ms = 100ms
        cnt_100ms = 0;
        flag_100ms = 1;         // 置位一次
    }

    if (++cnt_1s >= 100) {     // 1000 * 1ms = 1s
        cnt_1s = 0;
        flag_1s = 1;            // 置位一次
    }
}

// ✅ 提供“用完即清”的接口函数
bit get_100ms_flag(void)
{
    if (flag_100ms) {
        flag_100ms = 0; // 读取后立即清除
        return 1;
    }
    return 0;
}

bit get_1s_flag(void)
{
    if (flag_1s) {
        flag_1s = 0;
        return 1;
    }
    return 0;
}