#include "app.h"

#include "key.h"
#include "rtc.h"
#include "dis.h"
#include "temp.h"
#include "iic.h"
#include "pwm.h"
#include "uart.h"

static u8 aaa = 0;
static u8 bbb = 0;

void app_init()
{
    static bit initok = 0;
    if(initok != 1)
    {
        initok = 1;
			dis_init();
    }
}

void ui_display()
{
	aaa = dis_get();
	seg_set(aaa/100,aaa%100/10,aaa%10,16,16,16,16,16);
	
}


void app_100ms_task()
{  

	app_init();

	
    ui_display();

	
	



}
void app_10ms_task()
{
    u8 key_now =key_get();
	if(key_now != 255)
	{
        switch(key_now)
        {

        }
	}
	
     
}
void app_500ms_task()
{

}