//drv_rtc.c
#include "drv_rtc.h"
#include <intrins.h>


#define uint8_t unsigned char
	
// 定义全局数组（用于兼容你原来的函数）
uint8_t time_now[3] = {0, 0, 0};
const uint8_t time_init[7] = {0x50, 0x59, 0x23, 0x09, 0x04, 0x03, 0x25};

// 写地址数组（秒、分、时、日、月、星期、年）
const uint8_t code write_address[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8A, 0x8C};
// 读地址数组（秒、分、时、日、月、星期、年）
const uint8_t code read_address[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8B, 0x8D};

//==============================================================================
// 内部函数：向DS1302写入一个字节（底层时序）
//==============================================================================
static void Write_Ds1302(uint8_t temp) 
{
    uint8_t i;
    for (i = 0; i < 8; i++)     	
    { 
        SCK = 0;
        SDA = temp & 0x01;
        temp >>= 1; 
        SCK = 1;
    }
}

//==============================================================================
// 内部函数：向指定地址写入一个字节
//==============================================================================
static void Write_Ds1302_Byte(uint8_t address, uint8_t dat)     
{
    RST = 0;	_nop_();
    SCK = 0;	_nop_();
    RST = 1; 	_nop_();  
    Write_Ds1302(address);	
    Write_Ds1302(dat);		
    RST = 0; 
}

//==============================================================================
// 内部函数：从指定地址读取一个字节
//==============================================================================
static uint8_t Read_Ds1302_Byte(uint8_t address)
{
    uint8_t i, temp = 0x00;
    RST = 0;	_nop_();
    SCK = 0;	_nop_();
    RST = 1;	_nop_();
    Write_Ds1302(address);
    for (i = 0; i < 8; i++) 	
    {		
        SCK = 0;
        temp >>= 1;	
        if(SDA)
            temp |= 0x80;	
        SCK = 1;
    } 
    RST = 0;	_nop_();
    SCK = 0;	_nop_();
    SCK = 1;	_nop_();
    SDA = 0;	_nop_();
    SDA = 1;	_nop_();
    return (temp);			
}

//==============================================================================
// 内部函数：十六进制转BCD码
//==============================================================================
static uint8_t hex_to_bcd(uint8_t hex)
{
    return (hex / 10 * 16) + (hex % 10);
}

//==============================================================================
// 内部函数：BCD码转十六进制
//==============================================================================
static uint8_t bcd_to_hex(uint8_t bcd)
{
    return (bcd / 16 * 10) + (bcd % 16);
}

//==============================================================================
// 函数名称：RTC_Init
// 功能描述：初始化RTC驱动
//==============================================================================
void RTC_Init(void)
{
    // 初始化引脚状态
    RST = 0;
    SCK = 0;
    SDA = 0;
}

//==============================================================================
// 函数名称：RTC_SetTime
// 功能描述：设置RTC时间
//==============================================================================
void RTC_SetTime(RTC_TimeType *time)
{
    uint8_t i;
    uint8_t time_bcd[7];
    
    // 将十进制时间转换为BCD码
    time_bcd[0] = hex_to_bcd(time->second);  // 秒
    time_bcd[1] = hex_to_bcd(time->minute);  // 分
    time_bcd[2] = hex_to_bcd(time->hour);    // 时
    time_bcd[3] = hex_to_bcd(time->day);     // 日
    time_bcd[4] = hex_to_bcd(time->month);   // 月
    time_bcd[5] = hex_to_bcd(time->week);    // 星期
    time_bcd[6] = hex_to_bcd(time->year);    // 年
    
    // 关闭写保护
    Write_Ds1302_Byte(RTC_WP, 0x00);
    
    // 写入所有时间数据
    for(i = 0; i < 7; i++)
    {
        Write_Ds1302_Byte(write_address[i], time_bcd[i]);
    }
    
    // 开启写保护
    Write_Ds1302_Byte(RTC_WP, 0x80);
}

//==============================================================================
// 函数名称：RTC_GetTime
// 功能描述：读取RTC时间
//==============================================================================
void RTC_GetTime(RTC_TimeType *time)
{
    uint8_t i;
    uint8_t time_bcd[7];
    
    // 读取所有时间数据（BCD码格式）
    for(i = 0; i < 7; i++)
    {
        time_bcd[i] = Read_Ds1302_Byte(read_address[i]);
    }
    
    // 将BCD码转换为十进制，并存入结构体
    time->second = bcd_to_hex(time_bcd[0] & 0x7F);  // 屏蔽时钟暂停位
    time->minute = bcd_to_hex(time_bcd[1] & 0x7F);
    time->hour = bcd_to_hex(time_bcd[2] & 0x3F);    // 屏蔽12/24小时制标志位
    time->day = bcd_to_hex(time_bcd[3] & 0x3F);
    time->month = bcd_to_hex(time_bcd[4] & 0x1F);
    time->week = bcd_to_hex(time_bcd[5] & 0x07);
    time->year = bcd_to_hex(time_bcd[6]);
}


