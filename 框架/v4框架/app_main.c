#include "app_main.h"

#include "drv_rtc.h"
#include "drv_temp.h"


static bit mode = 0;
static u8 page = 0;
static u16 d_t = 213;
static u8 t_s = 55;
static u8 t_m = 56;
static u8 t_h = 21;
static u16 s_t = 230;
static bit relay_sw = 0;

rtc_type rtc;

void app_init()
{
    static bit initok = 0;
    if(initok == 0)
    {
        initok = 1;
        drv_rtc_init();
        drv_temp_init();
    }
}
void debug_time()
{
    rtc.s = 55;
    rtc.m = 59;
    rtc.h = 22;
    drv_rtc_set(&rtc);
}
void seg_display()
{
    switch(page)
    {
        case 0 :{drv_seg_set_all(25,1,16,16,16,d_t/100,d_t%100/10+32,d_t%10);}break;
        case 1 :{drv_seg_set_all(25,2,16,t_h/10,t_h%10,17,t_m/10,t_m%10);}break;
        case 2 :{drv_seg_set_all(25,3,16,16,16,16,s_t/100,s_t%100/10);}break;
        case 11 :{drv_seg_set_all(relay_sw,16,16,16,16,16,t_s/10,t_s%10);}break;
    }
}
void key_ctrl()
{
    if(drv_key_is(13)){mode ^= 1;}
    switch(page)
    {
        case 0 :{
                    if(drv_key_is(12)){page = 1;}
                }break;
        case 1 :{
                    if(drv_key_is(12)){page = 2;}
                    if(drv_key_is(17)){page = 11;}
                }break;
        case 2 :{
                    if(drv_key_is(12)){page = 0;}
                    if(drv_key_is(17) && s_t > 100){s_t -= 10;}
                    if(drv_key_is(16) && s_t < 990){s_t += 10;}
                }break;
        case 11 :{
                    if(drv_key_is(17)){page = 1;}
                    if(drv_key_is(16)){debug_time();}
                }break;
    }
}
void relay_run()
{
    static bit led_2 = 0;
    if(relay_sw)
    {
        drv_relay_set(1);
        drv_led_set(2,led_2);
        led_2 ^= 1;
    }else
    {
        drv_relay_set(0);
        drv_led_set(2,0);        
    }
}
void led_0()
{
    if(t_m == 0 && t_s == 0){drv_led_set(0,1);}
    if(t_s > 4){drv_led_set(0,0);}
}
void mode_run()
{
    drv_led_set(1,~mode);
    if(mode)
    {
        if(t_m == 0 && t_s == 0){relay_sw = 1;}
        if(t_s > 4){relay_sw = 0;}        
    }else
    {
        if(d_t > s_t){relay_sw = 1;}
        else{relay_sw = 0;}
    }
}

void app_task_100ms()
{  
    app_init();
    seg_display();
    key_ctrl();
    relay_run();
    led_0();
    mode_run();
}
void app_task_500ms()
{
    drv_rtc_get(&rtc);
    t_s = rtc.s;
    t_m = rtc.m;
    t_h = rtc.h;
    d_t = drv_temp_get();
}