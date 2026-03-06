#include "drv_temp.h"

void Delay_OneWire(unsigned int t)  
{
	unsigned char i;
	while(t--){
		for(i=0;i<12;i++);
	}
}

//
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

//
unsigned char Read_DS18B20(void)
{
	unsigned char i;
	unsigned char dat;
  
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

//
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
  
  	return initflag;
}

void drv_temp_init()
{
	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0x4e);
	Write_DS18B20(0x00);
	Write_DS18B20(0x00);
	Write_DS18B20(0x5f);
	Delay_OneWire(20);
}	

uint16 drv_temp_get()
{
	uint8 high , low;
	uint16 raw_temp , result;
	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0x44);
	Delay_OneWire(100);
	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0xbe);
	low = Read_DS18B20();
	high = Read_DS18B20();	
	raw_temp = (high << 8) | low;	
	result = raw_temp *10 /16;
	return result;
}