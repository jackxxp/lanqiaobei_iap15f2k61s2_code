#include "app_task1.h"

/* ====== 硬件定义 ====== */
sbit ULTRASONIC_TRIG = P1^0;   // Trig -> P1.0 (输出)
sbit ULTRASONIC_ECHO = P1^1;   // Echo -> P1.1 (输入，接 P1 口中断)

/* ====== 测量数据（中断与主程序共享） ====== */
static volatile uint16 echo_start = 0;    // 上升沿时间戳
static volatile uint16 echo_end = 0;      // 下降沿时间戳  
static volatile uint8 echo_flag = 0;      // 0:未开始, 1:已上升, 2:已下降

/* ====== P1 口中断服务程序（捕获 Echo 边沿） ====== */
void P1_port_isr(void) interrupt 19
{
    // 检查是否是 P1.1 触发的中断
    if(P1INTF & 0x02)
    {
        P1INTF &= ~0x02;  // 清中断标志
        
        if(echo_flag == 0 && ULTRASONIC_ECHO == 1)
        {
            // 上升沿：记录开始时间
            echo_start = (T2H << 8) | T2L;
            echo_flag = 1;
        }
        else if(echo_flag == 1 && ULTRASONIC_ECHO == 0)
        {
            // 下降沿：记录结束时间
            echo_end = (T2H << 8) | T2L;
            echo_flag = 2;  // 测量完成标记
        }
    }
}

/* ====== 主任务函数（每 100ms 调用一次） ====== */
void app_task1_run()
{
	            unsigned char i = 20; 
    static uint8 run_step = 0;
    static uint16 distance_mm = 0;
    static uint8 timeout_cnt = 0;
    uint16 pulse_width;
    
    switch(run_step)
    {
        case 0:  // 初始化
        {
            // 1. 配置 Timer 2：12T 模式，1us 计数，自由运行
            AUXR &= ~0x04;      // T2x12=0 (12分频，12MHz->1us/tick)
            AUXR &= ~0x08;      // T2_C/T=0 (定时器模式，非计数器)
            AUXR |= 0x10;       // T2R=1 (启动定时器2)
            T2H = 0;            // 计数器清零
            T2L = 0;
            
            
            // P1 口中断配置：P1.1 双边沿触发
            P1IM0 |= 0x02;      // 中断模式控制
            P1IM1 |= 0x02;      // 11 = 双边沿触发 (上升沿+下降沿)
            P1INTE |= 0x02;     // 使能 P1.1 中断
            P1INTF &= ~0x02;    // 清标志
            
            EA = 1;             // 开总中断
            
            // 显示初始化
            drv_seg_set(0, 0);
            drv_seg_set(3, 0); drv_seg_set(4, 0);
            drv_seg_set(5, 0); drv_seg_set(6, 0);
            drv_seg_set(7, 0);
            
            run_step = 1;
        }
        break;
        
        case 1:  // 触发测距
        {
            drv_seg_set(0, 1);
            
            // 重置测量标记
            echo_flag = 0;
            timeout_cnt = 0;
            
            // 发送 15us 高电平脉冲（保险值）
            ULTRASONIC_TRIG = 1;
 // 约 15-20us @12MHz
            while(i--);
            ULTRASONIC_TRIG = 0;
            
            run_step = 2;
        }
        break;
        
        case 2:  // 等待测量结果
        {
            drv_seg_set(0, 2);
            
            if(echo_flag == 2)
            {
                // 测量完成，计算脉宽（处理 16 位溢出）
                if(echo_end >= echo_start)
                    pulse_width = echo_end - echo_start;
                else
                    pulse_width = (0xFFFF - echo_start) + echo_end + 1;
                
                // 计算距离：time(us) * 0.17 mm/us = time * 17 / 100
                // 有效范围：150us(2.5cm) ~ 25000us(4.25m)
                if(pulse_width > 150 && pulse_width < 25000)
                {
                    distance_mm = (unsigned long)pulse_width * 17 / 100;
                    
                    // 显示距离（格式：XXXX mm）
                    drv_seg_set(3, distance_mm / 1000);
                    drv_seg_set(4, (distance_mm % 1000) / 100);
                    drv_seg_set(5, (distance_mm % 100) / 10);
                    drv_seg_set(6, distance_mm % 10);
                    drv_seg_set(7, 16);  // 熄灭最后一位
                }
                else
                {
                    // 超量程显示 "----"
                    drv_seg_set(3, 17); drv_seg_set(4, 17);
                    drv_seg_set(5, 17); drv_seg_set(6, 17);
                }
                
                run_step = 1;  // 完成后立即开始下一次测量
            }
            else
            {
                // 超时检查：100ms 周期 * 5 = 500ms 无响应
                if(++timeout_cnt > 5)
                {
                    // 超时显示 "Err"
                    drv_seg_set(3, 14);  // E
                    drv_seg_set(4, 17);  // -
                    drv_seg_set(5, 17);  // -
                    drv_seg_set(6, 13);  // r (如果有) 或 17
                    
                    run_step = 1;  // 强制重新开始
                }
            }
        }
        break;
        
        default:
            run_step = 0;
            break;
    }
}