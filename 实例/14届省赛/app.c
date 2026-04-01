#include "app.h"

#include "rtc.h"
#include "ne555.h"
#include "i2c.h"
#include "temp.h"


u8 page = 0;
u8 page_last = 0;

u8 time_h =23;
u8 time_m =45;
u8 time_s =55;

bit fsw = 0;

u16 temp_max = 0;
u16 temp_avg = 0;
u16 temp_set = 300;
u16 temp_now = 0;
u16 temp_last = 65535;

xdata u16  temp_his[10] = {0,0,0,0,0,0,0,0,0,0};


u16 hum_max = 0;
u16 hum_avg = 0;
u16 hum_now = 0;
u16 hum_last = 65535;

xdata u16  hum_his[10] = {0,0,0,0,0,0,0,0,0,0};

static u8  f_times = 0;
u8 f_h = 12;
u8 f_m = 48;

u16 fr = 0;
u16 fr_out = 0;

u8 adc = 0;

rtc_type rtc;


Timer0_Isr(void) interrupt 1
{
	fr++;

}


void init()
{
    static bit initok = 0;
    if(initok == 0)
    {
        initok = 1;
        rtc_init();
		ne555_init();

		temp_init();
			temp_now = temp_get();

    }
}

void seg_display()
{
	switch(page)
	{
		case 0:
		{
			seg_set(time_h/10,time_h%10,17,time_m/10,time_m%10,17,time_s/10,time_s%10);
		}break;
		case 10:
		{
			if(f_times!= 0)
			{seg_set(12,16,temp_max/100,temp_max%100/10,17,temp_avg/100,(temp_avg%100/10)+32,temp_avg%10);}
			else{seg_set(12,16,16,16,16,16,16,16);}
		}break;
		case 11:
			{
				if(f_times!= 0)
				{seg_set(18,16,hum_max/100,hum_max%100/10,17,hum_avg/100,(hum_avg%100/10)+32,hum_avg%10);}
				else{seg_set(18,16,16,16,16,16,16,16);}
		}break;
		case 12:
		{
			if(f_times!= 0)
			{seg_set(15,f_times/10,f_times%10,f_h/10,f_h%10,17,f_m/10,f_m%10);}
			else{seg_set(15,f_times/10,f_times%10,16,16,16,16,16);}
		}break;
		case 2:
		{
			seg_set(24,16,16,16,16,16,temp_set/100,temp_set%100/10);
		}break;
		case 9:
		{
			if(hum_now != 60000)
			{
				seg_set(14,16,16,temp_now/100,temp_now%100/10,17,hum_now/100,hum_now%100/10);
				led_set(4,0);
			}else
			{
				seg_set(14,16,16,temp_now/100,temp_now%100/10,17,10,10);
				//seg_set(14,16,16,fr/10000,fr%10000/1000,fr%1000/100,fr%100/10,fr%10);
				led_set(4,1);
			}
			}break;
	}

}



void led_ctrl()
{
	if(page == 0)
	{
		led_set(0,1);
	}else
	{
		led_set(0,0);
	}
	if(page == 10 || page == 11 ||page == 12)
	{
		led_set(1,1);
	}else
	{
		led_set(1,0);
	}
	if(page == 9)
	{
		led_set(2,1);
	}else
	{
		led_set(2,0);
	}
	if(f_times >=2 && temp_now > temp_last && hum_now > hum_last)
	{
		led_set(5,1);
	}else
	{
		led_set(5,0);
	}

}

void key_ctrl()
{
	if(page != 9)
	{
		u8 key_v = key_scan();
		if(key_v != 99)
		{	
			switch(page)
			{
				case 0:
				{
					if(key_v == 4){page = 10;}
				}break;
				case 10:
				{
					if(key_v == 4){page = 2;}
					if(key_v == 5){page = 11;}
				}break;
				case 11:
				{
					if(key_v == 4){page = 2;}
					if(key_v == 5){page = 12;}
				}break;
				case 12:
				{
					if(key_v == 4){page = 2;}
					if(key_v == 5){page = 10;}
					if(key_v == 29){f_times = 0;f_h = 0;f_m = 0;hum_avg = 0;hum_max = 0;temp_avg= 0;temp_max = 0;}
				}break;
				case 2:
				{
					if(key_v == 4){page = 0;}
					if(key_v == 8 && temp_set<990){temp_set += 10;}
					if(key_v == 9 && temp_set>0){temp_set -= 10;}
				}break;
			}
		}
	}
}

void hum_get()
{
	if(fr_out >=200 && fr_out<= 2000)
	{
		//hum_now = fr_out*44/100+100;
		hum_now = 100 + (fr_out - 200) * 20 / 45;
	}else
	{
		hum_now = 60000;
	}
}


void l4_run()
{
	static bit l4sw = 0;
	if(temp_now >temp_set)
	{
		led_set(3,l4sw);
		l4sw ^= 1;
	}else
	{
		led_set(3,0);
	}
}
void rtc_run()
{
	rtc_get(&rtc);
    time_s = rtc.s;
    time_m = rtc.m;
    time_h = rtc.h; 
}

void adc_run()
{
	adc = adc_get();
}

void avg_jishuan()
{
	static u8 avg_tick = 0;
	static u8 avg_ticktotle = 1;

	temp_his[avg_tick] = temp_now;
	hum_his[avg_tick] = hum_now;

	avg_tick++;if(avg_tick == 10){avg_tick = 0;}


	temp_avg = (temp_his[0]+temp_his[1]+temp_his[2]+temp_his[3]+temp_his[4]+temp_his[5]+temp_his[6]+temp_his[7]+temp_his[8]+temp_his[9])/avg_ticktotle;
	hum_avg = (hum_his[0]+hum_his[1]+hum_his[2]+hum_his[3]+hum_his[4]+hum_his[5]+hum_his[6]+hum_his[7]+hum_his[8]+hum_his[9])/avg_ticktotle;
	if(avg_ticktotle !=10){avg_ticktotle++;}

}

void ffff()
{
	static u8 fff_step = 0;
	static u8 fff_time = 0;

	switch(fff_step)
	{
	case 0:
	{
		if(fsw == 1)
		{
			temp_now = temp_get();
			hum_get();
			page_last = page;
			page = 9;
			fff_step =1;
			if(hum_now != 60000)
			{
				f_h = time_h;
				f_m = time_m;
				f_times++;
				if(temp_now>temp_max)
				{
					temp_max = temp_now;
				}
				if(hum_now>hum_max)
				{
					hum_max = hum_now;
				}
				avg_jishuan();
			}			
		}
	}break;
	case 1:
	{
		fff_time++;
		if(fff_time >=29)
		{
			fff_step =2;
		}
	}break;
	case 2:
	{
		fff_step = 0;
		fff_time = 0;
		page = page_last;
		fsw = 0;
	}break;
	}
}

void adc_f_run()
{
	static bit liang = 0;
	if(fsw != 1)
	{
		if(adc >= 50){liang = 1;}
		if(liang ==1 && adc <20)
		{
			liang = 0;
			fsw = 1;
		}
	}
}

void app_task_1000ms()
{
	fr_out= fr;
	fr = 0;
}

void app_task_100ms()
{
	init();
    seg_display();
	adc_run();
	
	led_ctrl();
	l4_run();
	adc_f_run();
	ffff();
	
}
void app_task_500ms()
{
	rtc_run();
	
	
	
}

void app_task_10ms()
{
    key_ctrl();

}

	