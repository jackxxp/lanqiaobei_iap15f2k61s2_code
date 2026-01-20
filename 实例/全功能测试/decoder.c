//decoder.h
#include "decoder.h"

void decoder_init()
{
	P2 = P2 & 0x1F;
}

void decoder_set(uint8 pin)
{
    pin &= 0x07;// 限制 pin 范围 0～7   
    P2 = (P2 & 0x1F) | ((pin << 5) & 0xE0);// 读取当前 P2 值，保留低5位（P2.0～P2.4），替换高3位（P2.5～P2.7）
}