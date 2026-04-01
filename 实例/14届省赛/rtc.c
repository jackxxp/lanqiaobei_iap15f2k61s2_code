#include "rtc.h"

void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK = 0;
		SDA = temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

//
void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

//
unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}


u8 hex_to_bcd(hex)
{
    return (hex/10*16)+(hex%10);
}
u8 bcd_to_hex(bcd)
{
    return (bcd/16*10)+(bcd%16);
}
void rtc_init()
{
    RST=0;SCK=0;SDA=0;
    Write_Ds1302_Byte(0x8e,0x00);
    Write_Ds1302_Byte(0x80,hex_to_bcd(10)&0x7f);
}
void rtc_set(rtc_type *time)
{
    Write_Ds1302_Byte(0x80,hex_to_bcd(time->s));
    Write_Ds1302_Byte(0x82,hex_to_bcd(time->m));
    Write_Ds1302_Byte(0x84,hex_to_bcd(time->h));
}
void rtc_get(rtc_type *time)
{
    time->s = bcd_to_hex(Read_Ds1302_Byte(0x81)&0x7f);
    time->m = bcd_to_hex(Read_Ds1302_Byte(0x83)&0x7f);
    time->h = bcd_to_hex(Read_Ds1302_Byte(0x85)&0x3f);
}