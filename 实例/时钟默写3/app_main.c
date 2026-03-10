#include "app_main.h"

#include "drv_rtc.h"
#include "drv_temp.h"

static u8 app_page = 0;
static bit mode = 0;
static u16 d_temp = 213;
static u8 time_s = 35;
static u8 time_m = 50;
static u8 time_h = 20;
static u16 set_temp = 230;
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
    rtc.s=55;
    rtc.m=59;
    rtc.h=22;  
    drv_rtc_set(&rtc); 
}
void seg_display()
{
    switch(app_page)
    {
        case 0:{drv_seg_set_all(25,1,16,16,16,d_temp/100,d_temp%100/10 +32,d_temp%10);}break;
        case 1:{drv_seg_set_all(25,2,16,time_h/10,time_h%10,17,time_m/10,time_m%10);}break;
        case 2:{drv_seg_set_all(25,3,16,16,16,16,set_temp/100,set_temp/10%10);}break;
        case 11:{drv_seg_set_all(25,17,7,16,relay_sw,16,time_s/10,time_s%10);}break;
    }
}
void key_ctrl()
{
    if(drv_key_is(13)){mode ^= 1;}
    switch(app_page)
    {
        case 0:{if(drv_key_is(12)){app_page = 1;}}break;
        case 1:{if(drv_key_is(12)){app_page = 2;}if(drv_key_is(17)){app_page = 11;}}break;
        case 2:{if(drv_key_is(12)){app_page = 0;}if(drv_key_is(17)&&set_temp > 100){set_temp-=10;}if(drv_key_is(16)&&set_temp < 990){set_temp+=10;}}break;
        case 11:{if(drv_key_is(17)){app_page = 1;}if(drv_key_is(16)){debug_time();}}break;
    }
}
void relay_ctrl()
{
    static bit led2;
    if(relay_sw)
    {
        drv_relay_set(1);
        drv_led_set(2,led2);
        led2 ^= 1;
    }else
    {
        drv_relay_set(0);
        drv_led_set(2,0);        
    }

}
void led0_run()
{
    if(time_m == 0 && time_s == 0){drv_led_set(0,1);}
    if(time_s > 4){drv_led_set(0,0);}
}
void mode_run()
{
    drv_led_set(1,~mode);
    if(mode)
    {
        if(time_m == 0 && time_s == 0){relay_sw = 1;}
        if(time_s > 4){relay_sw = 0;}        
    }else
    {
        if(d_temp > set_temp){relay_sw = 1;}
        else{relay_sw = 0;}
    }
}

void app_task_100ms()
{
    app_init();
    seg_display();
    key_ctrl();
    relay_ctrl();
    led0_run();
    mode_run();
}
void app_task_500ms()
{
    drv_rtc_get(&rtc);
    time_s = rtc.s;
    time_m = rtc.m;
    time_h = rtc.h;    
    d_temp = drv_temp_get();
}