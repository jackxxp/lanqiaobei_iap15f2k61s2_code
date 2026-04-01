//drv_key.c
#include "drv_key.h"

static uint8 key_ram = 200;

static uint8 key_now_press = 200;

void drv_key_run()
{
    static uint8 key_step = 0;
    static uint8 key_ptime = 0;
    static uint8 key_save = 0; // 👈 新增：保存原始键值（4～19）

    uint8 key_now = 0xFF;
    uint8 key_temp = 200; // 默认无效

    // 行扫描：拉低所有行
    P3 = 0x0F;
    P42 = 0;
    P44 = 0;
    P36 = P42;
    P37 = P44;
    key_now = P3 & 0x0F;

    switch(key_step)
    {
        case 0: // 空闲态
            if (key_now != 0x0F) {
                key_step = 1;
								
            }else
						{
							key_now_press = 200;
						}
            break;

        case 1: // 检测到有键按下，开始列扫描
            if (key_now == 0x0F) {
                key_step = 0; // 抖动，回到空闲
            } else {
                // 切换到列输出模式
                P3 = key_now | 0xF0;
                P42 = 1;
                P44 = 1;
                P36 = P42;
                P37 = P44;
                key_now = P3; // 读取完整键值

                // 识别键值
                switch (key_now) 
                {
									case 0xF7: key_save = 4; break;   //独立按键   只用独立按键矩阵按键部分可不写
									case 0xFB: key_save = 5; break;   //独立按键     只用矩阵键盘独立键盘可不
                    case 0xFD: key_save = 6; break;   //独立按键   如果都写则都可以使用
                    case 0xFE: key_save = 7; break;   //独立按键
									
                    case 0x77: key_save = 4; break;   //矩阵按键
                    case 0x7B: key_save = 5; break;   //矩阵按键
                    case 0x7D: key_save = 6; break;//矩阵按键
                    case 0x7E: key_save = 7; break;//矩阵按键

                    case 0xB7: key_save = 8; break;//矩阵按键
                    case 0xBB: key_save = 9; break;//矩阵按键
                    case 0xBD: key_save = 10; break;//矩阵按键
                    case 0xBE: key_save = 11; break;//矩阵按键

                    case 0xD7: key_save = 12; break;//矩阵按键
                    case 0xDB: key_save = 13; break;//矩阵按键
                    case 0xDD: key_save = 14; break;//矩阵按键
                    case 0xDE: key_save = 15; break;//矩阵按键

                    case 0xE7: key_save = 16; break;//矩阵按键
                    case 0xEB: key_save = 17; break;//矩阵按键
                    case 0xED: key_save = 18; break;//矩阵按键
                    case 0xEE: key_save = 19; break;//矩阵按键
                    default:
                        key_step = 0;
                        key_save = 201;
                        return; // 退出，不更新 key_ram
                }
								key_now_press = key_save;
                key_step = 2;
            }
            break;

        case 2: // 等待释放（短按）或进入长按
            // 重新读取行状态
            P3 = 0x0F;
            P42 = 0;
            P44 = 0;
            P36 = P42;
            P37 = P44;
            key_now = P3 & 0x0F;

            if (key_now != 0x0F) {
                // 按键仍按下，计时
                key_ptime++;
                if (key_ptime > 70) { // 长按阈值
                    key_ptime = 0;
                    key_step = 3;
                    // 注意：长按结果在松手时才上报
                }
            } else {
                // 短按：松手了
                key_ptime = 0;
                key_step = 0;
                key_temp = key_save; // 👈 使用保存的键值
            }
            break;

        case 3: // 长按等待松手
            P3 = 0x0F;
            P42 = 0;
            P44 = 0;
            P36 = P42;
            P37 = P44;
            key_now = P3 & 0x0F;

            if (key_now == 0x0F) {
                // 松手，上报长按
                key_step = 0;
                key_temp = key_save + 100; // 👈 正确：原始键值+100
            }
            break;
    }
		if (key_temp != 201)
    {key_ram = key_temp;}
}

uint8 drv_key_get()
{
    uint8 temp = key_ram;
    key_ram = 201; // 清除，避免重复上报
    return temp;
}
uint8 drv_key_get_now()
{
    return key_now_press;
}

bit drv_key_is(keyv)
{
	uint8 temp = key_ram;
	bit is = 0;
	
	if(keyv == temp)
	{
		is = 1;
		key_ram = 201;		
	}
	return is;
}


