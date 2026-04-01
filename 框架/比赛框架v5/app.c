#include "app.h"


void init()
{
    static bit initok = 0;
    if(initok == 0)
    {
        initok = 1;
		//初始化
    }
}



void app_task_1000ms()
{

}

void app_task_100ms()
{
	init();
}
void app_task_500ms()
{
	
}

void app_task_10ms()
{

}

	