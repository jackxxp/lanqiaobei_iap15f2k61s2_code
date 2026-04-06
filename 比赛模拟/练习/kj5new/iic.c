#include "iic.h"

#define DELAY_TIME	10

//
static void I2C_Delay(unsigned char n)
{
    do
    {
        _nop_();_nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();_nop_();		
    }
    while(n--);      	
}

//
void I2CStart(void)
{
    sda = 1;
    scl = 1;
	I2C_Delay(DELAY_TIME);
    sda = 0;
	I2C_Delay(DELAY_TIME);
    scl = 0;    
}

//
void I2CStop(void)
{
    sda = 0;
    scl = 1;
	I2C_Delay(DELAY_TIME);
    sda = 1;
	I2C_Delay(DELAY_TIME);
}

//
void I2CSendByte(unsigned char byt)
{
    unsigned char i;
	
    for(i=0; i<8; i++){
        scl = 0;
		I2C_Delay(DELAY_TIME);
        if(byt & 0x80){
            sda = 1;
        }
        else{
            sda = 0;
        }
		I2C_Delay(DELAY_TIME);
        scl = 1;
        byt <<= 1;
		I2C_Delay(DELAY_TIME);
    }
	
    scl = 0;  
}

//
unsigned char I2CReceiveByte(void)
{
	unsigned char da;
	unsigned char i;
	for(i=0;i<8;i++){   
		scl = 1;
		I2C_Delay(DELAY_TIME);
		da <<= 1;
		if(sda) 
			da |= 0x01;
		scl = 0;
		I2C_Delay(DELAY_TIME);
	}
	return da;    
}

//
unsigned char I2CWaitAck(void)
{
	unsigned char ackbit;
	
    scl = 1;
	I2C_Delay(DELAY_TIME);
    ackbit = sda; 
    scl = 0;
	I2C_Delay(DELAY_TIME);
	
	return ackbit;
}

//
void I2CSendAck(unsigned char ackbit)
{
    scl = 0;
    sda = ackbit; 
	I2C_Delay(DELAY_TIME);
    scl = 1;
	I2C_Delay(DELAY_TIME);
    scl = 0; 
	sda = 1;
	I2C_Delay(DELAY_TIME);
}

void Delay5ms(void)	//@12.000MHz
{
	unsigned char data i, j;

	i = 59;
	j = 90;
	do
	{
		while (--j);
	} while (--i);
}


u8 eeprom_r(u8 addr)
{
    u8 Data;

    I2CStart();
    I2CSendByte(0xA0);      // 先发设备地址（写）
    I2CWaitAck();           // AT24C02 应答
    I2CSendByte(addr);   // 再发存储地址
    I2CWaitAck();           // AT24C02 应答

    I2CStart();
    I2CSendByte(0xA1);      // 设备地址（读）
    I2CWaitAck();
    Data = I2CReceiveByte();
    I2CSendAck(1);
    I2CStop();
    
    return Data;
}

void eeprom_w(u8 addr, u8 dat)
{
    I2CStart();
    I2CSendByte(0xA0);      // 设备写地址
    I2CWaitAck();
    I2CSendByte(addr);      // 存储地址
    I2CWaitAck();
    I2CSendByte(dat);       // 写入数据
    I2CWaitAck();
    I2CStop();
    
    Delay5ms();              // 等待内部写入完成
}

u8 adc(u8 add)
{

// add: 0x40(AIN0a/d排针), 0x41(AIN1光敏), 0x42(AIN2差分), 0x43(AIN3电位器)
    u8 value;

    // 启动转换
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(add);
    I2CWaitAck();
    I2CStop();
    
    // 读取结果
    I2CStart();
    I2CSendByte(0x91);
    I2CWaitAck();
    value = I2CReceiveByte();
    I2CSendAck(1);
    I2CStop();
    
    return value;
}

void dac(u8 v)
{
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x43);  // DAC使能
    I2CWaitAck();
    I2CSendByte(v);
    I2CWaitAck();
    I2CStop();
}