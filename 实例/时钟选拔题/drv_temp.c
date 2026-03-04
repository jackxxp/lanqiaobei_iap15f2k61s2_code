//drv_temp.c
#include "drv_temp.h"
#include <intrins.h>


void Delay_OneWire(unsigned int t)  
{
    unsigned char i;
    while(t--){
        for(i=0;i<12;i++);
    }
}

void Write_DS18B20(unsigned char dat)
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        DQ = 0;
        DQ = dat&0x01;
        Delay_OneWire(5);
        DQ = 1;
        dat >>= 1;
    }
    Delay_OneWire(5);
}

unsigned char Read_DS18B20(void)
{
    unsigned char i;
    unsigned char dat = 0;  // 初始化dat
  
    for(i=0;i<8;i++)
    {
        DQ = 0;
        dat >>= 1;
        DQ = 1;
        if(DQ)
        {
            dat |= 0x80;
        }       
        Delay_OneWire(5);
    }
    return dat;
}

bit init_ds18b20(void)
{
    bit initflag = 0;
    
    DQ = 1;
    Delay_OneWire(12);
    DQ = 0;
    Delay_OneWire(80);
    DQ = 1;
    Delay_OneWire(10); 
    initflag = DQ;     
    Delay_OneWire(5);
    
    return initflag;  // 返回0表示成功
}

//==============================================================================
// 新增：设置DS18B20分辨率
//==============================================================================
void set_resolution(unsigned char res)
{
    init_ds18b20();
    Write_DS18B20(0xCC);  // 跳过ROM
    Write_DS18B20(0x4E);  // 写暂存器
    Write_DS18B20(0x00);  // TH寄存器
    Write_DS18B20(0x00);  // TL寄存器
    Write_DS18B20(res);   // 配置寄存器
    Delay_OneWire(20);     // 等待写入完成
}

//==============================================================================
// 新增：DS18B20初始化并设置11位分辨率
//==============================================================================
bit Temp_Init(void)
{
    // 复位检测
    if(init_ds18b20() != 0)
    {
        return 1;  // 初始化失败
    }
    
    // 设置为11位分辨率 (0x5F)
    // 0x1F = 9位 (93.75ms)
    // 0x3F = 10位 (187.5ms)
    // 0x5F = 11位 (375ms)
    // 0x7F = 12位 (750ms)
    set_resolution(0x5F);
    
    return 0;  // 初始化成功
}

//==============================================================================
// 读取温度值（返回*10格式）
//==============================================================================
int read_temp_int(void)
{
    unsigned char high, low;
    int raw_temp;
    int result;
    
    // 启动温度转换
    init_ds18b20();
    Write_DS18B20(0xCC);  // 跳过ROM
    Write_DS18B20(0x44);  // 启动转换
    
    // 等待转换完成（11位分辨率需要375ms）
    // 200 * 12 * 12 ≈ 750ms 是12位的时间
    // 11位分辨率需要375ms，所以用100
    Delay_OneWire(100);    // 100 * 12 * 12 ≈ 375ms
    
    // 读取温度值
    init_ds18b20();
    Write_DS18B20(0xCC);  // 跳过ROM
    Write_DS18B20(0xBE);  // 读取暂存器
    
    low = Read_DS18B20();   // 读低字节
    high = Read_DS18B20();  // 读高字节
    
    raw_temp = (high << 8) | low;
    
    // 转换为*10格式
    if(raw_temp & 0x8000)  // 负温度
    {
        raw_temp = ~raw_temp + 1;
        result = - (raw_temp * 10 / 16);
    }
    else  // 正温度
    {
        result = raw_temp * 10 / 16;
    }
    
    return result;  // 返回*10格式
}