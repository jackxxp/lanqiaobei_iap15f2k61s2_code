#include "seg.h"


u8 code seg_code[]= {                       //标准字库
//   0    1    2    3    4    5    6    7    8    9    A10  B11  C12  D13  E14  F15
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//16black  -17 H18  J19  K20  L21  N22  o23  P24  U25  t26 G27  Q28  r29   M30  y31
    0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
    0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};    
    //0.   1.   2.   3.   4.   5.   6.   7.   8.   9.   -1
//   32   33    34    35  36   37  38   39    40   41   42
u8 seg_ram[8] = {16,16,16,16,16,16,16,16};

void seg_run()
{
  static u8 seg_tick = 0;

  P0 = 0xFF;
  sys_decoder(7);
  sys_decoder(0);

  P0 = 0x01 << seg_tick;
  sys_decoder(6);
  sys_decoder(0);

  P0 = ~ seg_code[seg_ram[seg_tick++]];
  sys_decoder(7);
  sys_decoder(0);

  if (seg_tick >= 8) {seg_tick = 0;}

}

void seg_set(u8 s0,s1,s2,s3,s4,s5,s6,s7)
{
	seg_ram[0]=s0;seg_ram[1]=s1;seg_ram[2]=s2;seg_ram[3]=s3;seg_ram[4]=s4;seg_ram[5]=s5;seg_ram[6]=s6;seg_ram[7]=s7;
}