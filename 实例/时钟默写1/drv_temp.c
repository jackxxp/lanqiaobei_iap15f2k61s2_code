#include "drv_temp.h"

void Delay_OneWire(unsigned int t)  
{
	u8 i;
	while(t--){
		for(i=0;i<12;i++);
	}
}

//
void Write_DS18B20(u8 dat)
{
	u8 i;
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
u8 Read_DS18B20(void)
{
	u8 i;
	u8 dat;
  
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


//--------------------
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
unsigned int drv_temp_get()
{
	u8 l , h;
	u16 raw;
	
	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0x44);
	Delay_OneWire(100);	
	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0xbe);
	l = Read_DS18B20();
	h = Read_DS18B20();
	raw = l | (h << 8);
	return raw *10 /16;
}