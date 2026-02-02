#include "drv_ultrasonic.h"
#include <intrins.h>
#include "drv_led.h"    // 确保能调用 drv_led_set

/* ====== 调试计数器 ====== */
volatile uint16 pca_int_cnt = 0;  // 在头文件中用 extern 声明

/* ====== 硬件定义 ====== */
sbit ULTRASONIC_TRIG = P1^0;   // Trig 输出
#define ULTRASONIC_ECHO   P11   // Echo -> PCA CCP0

/* ====== 状态机 ====== */
typedef enum
{
    US_IDLE = 0,
    US_WAIT_RISE,
    US_WAIT_FALL,
    US_DONE
} ultrasonic_state_t;

static volatile ultrasonic_state_t us_state = US_IDLE;

/* ====== 捕获时间 ====== */
static volatile uint16 t_start = 0;
static volatile uint16 t_end   = 0;

/* ====== 初始化 ====== */
void drv_ultrasonic_init(void)
{
    /* Trig 输出 */
    ULTRASONIC_TRIG = 0;

    /* PCA 时钟：Fosc/12 */
    CMOD = 0x00;

    /* 清 PCA */
    CL = 0;
    CH = 0;

    /* CCP0：输入捕获，双边沿（CAPN + CAPP + ECCF）*/
    CCAPM0 = 0x31;

    /* 清中断标志 */
    CCF0 = 0;

    /* 启动 PCA */
    CR = 1;

    /* 允许中断 */
    EA = 1;
}

/* ====== 重置状态机 ====== */
void drv_ultrasonic_reset(void)
{
    us_state = US_IDLE;
    t_start = 0;
    t_end = 0;
    CCF0 = 0;
    CL = 0;
    CH = 0;
}  // ← 修正：补充了缺失的右大括号

/* ====== 触发超声波 ====== */
void drv_ultrasonic_trigger(void)
{
    unsigned char i;  // ← 修正：C51 变量必须在代码块开头定义
    
    drv_led_set(0, 1);  // 调试：进入函数
    
    // 如果不是 IDLE，强制重置而不是直接退出
    if(us_state != US_IDLE) {
        drv_led_set(1, 1);  // 调试：显示状态被重置过
        drv_ultrasonic_reset();
    }
    
    // 确保从低电平开始
    ULTRASONIC_TRIG = 0;
    
    drv_led_set(2, 1);  // 调试：准备发 Trig
    
    // 发 20us 高电平（12MHz 12T 模式）
    ULTRASONIC_TRIG = 1;
    i = 60;
    while(i--);
    ULTRASONIC_TRIG = 0;
    
    drv_led_set(2, 0);  // 调试：Trig 发送完成
    us_state = US_WAIT_RISE;
}

/* ====== PCA 中断 ====== */
void pca_isr(void) interrupt 7
{
    uint16 cap;  // ← 修正：C51 变量必须在代码块开头定义
    
    // 每次进中断计数（用于调试）
    pca_int_cnt++;
    if(pca_int_cnt > 9999) pca_int_cnt = 0;
    
    if (CCF0)
    {
        CCF0 = 0;
        cap = (CCAP0H << 8) | CCAP0L;
        
        if (us_state == US_WAIT_RISE)
        {
            t_start = cap;
            us_state = US_WAIT_FALL;
        }
        else if (us_state == US_WAIT_FALL)
        {
            t_end = cap;
            us_state = US_DONE;
        }
    }
}

/* ====== 是否完成 ====== */
bit drv_ultrasonic_is_done(void)
{
    return (us_state == US_DONE);
}

/* ====== 获取时间（us） ====== */
uint16 drv_ultrasonic_get_time_us(void)
{
    uint16 dt;

    EA = 0;
    if (t_end >= t_start)
        dt = t_end - t_start;
    else
        dt = (0xFFFF - t_start) + t_end + 1;
    EA = 1;

    return dt;
}

/* ====== 距离（mm） ====== */
uint16 drv_ultrasonic_get_distance_mm(void)
{
    uint16 time_us = drv_ultrasonic_get_time_us();
    return (uint16)(((unsigned long)time_us * 170) / 1000);
}