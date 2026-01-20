//seg.c
#include "seg.h"

void seg_init()
{
	decoder_set(6); 
	P0 = 0x0f;
  decoder_set(7);
  P0 = 0xf0;
  decoder_set(0);

}