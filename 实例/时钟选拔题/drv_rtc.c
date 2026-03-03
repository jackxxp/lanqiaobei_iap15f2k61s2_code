#include "drv_rtc.h"
#include <intrins.h>

// 写地址数组（秒、分、时、日、月、星期、年）
const unsigned char code write_address[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8A, 0x8C};
// 读地址数组（秒、分、时、日、月、星期、年）
const unsigned char code read_address[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8B, 0x8D};

//==============================================================================
// 内部函数：向DS1302写入一个字节（底层时序）
// 注意：改名为 RTC_WriteByte_Internal 避免冲突
//==============================================================================
static void RTC_WriteByte_Internal(unsigned char dat)
{
    unsigned char i;
    for(i = 0; i < 8; i++)
    {
        RTC_SCLK = 0;
        RTC_IO = dat & 0x01;
        dat >>= 1;
        RTC_SCLK = 1;
    }
}

//==============================================================================
// 内部函数：从DS1302读取一个字节（底层时序）
// 注意：改名为 RTC_ReadByte_Internal 避免冲突
//==============================================================================
static unsigned char RTC_ReadByte_Internal(void)
{
    unsigned char i;
    unsigned char dat = 0;
    
    for(i = 0; i < 8; i++)
    {
        RTC_SCLK = 0;
        dat >>= 1;
        if(RTC_IO)
        {
            dat |= 0x80;
        }
        RTC_SCLK = 1;
    }
    return dat;
}

//==============================================================================
// 内部函数：BCD码转十进制
//==============================================================================
static unsigned char BCD2Hex(unsigned char bcd)
{
    return (bcd >> 4) * 10 + (bcd & 0x0F);
}

//==============================================================================
// 内部函数：十进制转BCD码
//==============================================================================
static unsigned char Hex2BCD(unsigned char hex)
{
    return ((hex / 10) << 4) | (hex % 10);
}

//==============================================================================
// 函数名称：RTC_Init
// 功能描述：初始化RTC驱动
//==============================================================================
void RTC_Init(void)
{
    RTC_RST = 0;
    RTC_SCLK = 0;
    RTC_IO = 0;
}

//==============================================================================
// 函数名称：RTC_WriteByte
// 功能描述：向指定地址写入一个字节（外部调用接口）
//==============================================================================
void RTC_WriteByte(unsigned char addr, unsigned char dat)
{
    RTC_RST = 0;
    _nop_();
    RTC_SCLK = 0;
    _nop_();
    RTC_RST = 1;
    _nop_();
    
    RTC_WriteByte_Internal(addr);   // 写入地址
    RTC_WriteByte_Internal(dat);     // 写入数据
    
    RTC_RST = 0;
    _nop_();
    RTC_SCLK = 0;
    _nop_();
    RTC_SCLK = 1;
    _nop_();
    RTC_IO = 0;
    _nop_();
    RTC_IO = 1;
    _nop_();
}

//==============================================================================
// 函数名称：RTC_ReadByte
// 功能描述：从指定地址读取一个字节（外部调用接口）
//==============================================================================
unsigned char RTC_ReadByte(unsigned char addr)
{
    unsigned char dat;
    
    RTC_RST = 0;
    _nop_();
    RTC_SCLK = 0;
    _nop_();
    RTC_RST = 1;
    _nop_();
    
    RTC_WriteByte_Internal(addr | 0x01);  // 写入读地址
    dat = RTC_ReadByte_Internal();         // 读取数据
    
    RTC_RST = 0;
    _nop_();
    RTC_SCLK = 0;
    _nop_();
    RTC_SCLK = 1;
    _nop_();
    RTC_IO = 0;
    _nop_();
    RTC_IO = 1;
    _nop_();
    
    return dat;
}

//==============================================================================
// 函数名称：RTC_SetTime
// 功能描述：设置RTC时间
//==============================================================================
void RTC_SetTime(RTC_TimeType *time)
{
    unsigned char i;
    unsigned char time_bcd[7];
    
    // 将十进制时间转换为BCD码
    time_bcd[0] = Hex2BCD(time->second);  // 秒
    time_bcd[1] = Hex2BCD(time->minute);  // 分
    time_bcd[2] = Hex2BCD(time->hour);    // 时
    time_bcd[3] = Hex2BCD(time->day);     // 日
    time_bcd[4] = Hex2BCD(time->month);   // 月
    time_bcd[5] = Hex2BCD(time->week);    // 星期
    time_bcd[6] = Hex2BCD(time->year);    // 年
    
    // 关闭写保护
    RTC_WriteByte(RTC_WP, 0x00);
    
    // 写入所有时间数据
    for(i = 0; i < 7; i++)
    {
        RTC_WriteByte(write_address[i], time_bcd[i]);
    }
    
    // 开启写保护
    RTC_WriteByte(RTC_WP, 0x80);
}

//==============================================================================
// 函数名称：RTC_GetTime
// 功能描述：读取RTC时间
//==============================================================================
void RTC_GetTime(RTC_TimeType *time)
{
    unsigned char i;
    unsigned char time_bcd[7];
    
    // 读取所有时间数据（BCD码格式）
    for(i = 0; i < 7; i++)
    {
        time_bcd[i] = RTC_ReadByte(read_address[i]);
    }
    
    // 将BCD码转换为十进制，并存入结构体
    time->second = BCD2Hex(time_bcd[0] & 0x7F);  // 屏蔽时钟暂停位
    time->minute = BCD2Hex(time_bcd[1] & 0x7F);
    time->hour = BCD2Hex(time_bcd[2] & 0x3F);    // 屏蔽12/24小时制标志位
    time->day = BCD2Hex(time_bcd[3] & 0x3F);
    time->month = BCD2Hex(time_bcd[4] & 0x1F);
    time->week = BCD2Hex(time_bcd[5] & 0x07);
    time->year = BCD2Hex(time_bcd[6]);
}

//==============================================================================
// 函数名称：RTC_WriteProtect
// 功能描述：设置写保护状态
//==============================================================================
void RTC_WriteProtect(unsigned char enable)
{
    if(enable)
        RTC_WriteByte(RTC_WP, 0x80);  // 使能写保护
    else
        RTC_WriteByte(RTC_WP, 0x00);  // 禁止写保护
}

//==============================================================================
// 函数名称：RTC_Pause
// 功能描述：暂停/启动RTC时钟
//==============================================================================
void RTC_Pause(unsigned char pause)
{
    unsigned char sec;
    
    sec = RTC_ReadByte(RTC_SEC);
    
    if(pause)
        RTC_WriteByte(RTC_SEC, sec | 0x80);   // 暂停（设置CH位）
    else
        RTC_WriteByte(RTC_SEC, sec & 0x7F);   // 启动（清除CH位）
}

//==============================================================================
// 函数名称：RTC_SetHourMode
// 功能描述：设置12/24小时制
//==============================================================================
void RTC_SetHourMode(unsigned char mode)
{
    unsigned char hour;
    
    hour = RTC_ReadByte(RTC_HOUR);
    
    if(mode)
        hour |= 0x80;   // 12小时制
    else
        hour &= 0x3F;   // 24小时制
    
    RTC_WriteByte(RTC_HOUR, hour);
}