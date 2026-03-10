#include "drv_key.h"

static u8 key_ram = 200;


void drv_key_run()
{  
    static u8 key_step = 0;
    static u8 key_save = 200;
    u8 key_temp = 0x0f;

    P3 = 0x0f;P42 = 0;P44 = 0;P36 = P42;P37 = P44;
    key_temp = P3;
    switch(key_step)
    {
        case 0:
        {
            if(key_temp != 0x0f){key_step = 1;}
        }break;
        case 1:
        {
            if(key_temp == 0x0f){key_step = 0;}
            else
            {
                P3 = key_temp | 0xf0;P42 = 1;P44 = 1;P36 = P42;P37 = P44;
                key_temp = P3;
                switch(key_temp)
                {
                    case 0xd7:key_save = 12;break;
                    case 0xdb:key_save = 13;break;
                    case 0xe7:key_save = 16;break;
                    case 0xeb:key_save = 17;break;
                }
                if(key_save == 200)
                {
                    key_step = 0;
                }else
                {
                    key_step = 2;
                }
            }
        }break;
        case 2:
        {
            if(key_temp == 0x0f)
            {
                key_ram = key_save;
                key_save = 200;
                key_step = 0;
            }
        }break;
    }
}
bit drv_key_is(u8 keyv)
{
    bit keyok = 0;
    if(keyv == key_ram)
    {
        key_ram = 200;
        keyok = 1;
    }
    return keyok;
}