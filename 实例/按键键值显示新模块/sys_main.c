//sys_main.c
#include "sys_main.h"

//内部函数

void gpio_init()//GPIO 模式设置
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

void timer1_init()//定时器1启动
{
  AUXR &= 0xBF; // 定时器时钟12T模式
  TMOD &= 0x0F; // 设置定时器模式
  TL1 = 0x18;   // 设置定时初始值
  TH1 = 0xFC;   // 设置定时初始值
  TF1 = 0;      // 清除TF1标志
  TR1 = 1;      // 定时器1开始计时
  ET1 = 1;      // 使能定时器1中断
	
	EA = 1; //中断总开关
}
void driver_init()//设备初始化
{
	sys_main_decoder_set(4);//LED灯
	P0=0xff;
	sys_main_decoder_set(0);

	sys_main_decoder_set(6); //数码管位选
	P0 = 0x00;
  sys_main_decoder_set(7);//数码管段选
  P0 = 0xff;
  sys_main_decoder_set(0);

	sys_main_decoder_set(5);//继电器与蜂鸣器
	P0 = 0xaf;
	sys_main_decoder_set(0);
}


//外部调用函数

void sys_main_mcu_init()//MCU初始化
{
	gpio_init();//GPIO模式设置
	sys_main_decoder_set(0);//译码器初始化
	driver_init();//设备初始化
	timer1_init();//定时器1启动
	

}

void sys_main_decoder_set(uint8 pin)
{
    P2 = (P2 & 0x1F) | ((pin << 5) & 0xE0);// 读取当前 P2 值，保留低5位（P2.0～P2.4），替换高3位（P2.5～P2.7）
}

