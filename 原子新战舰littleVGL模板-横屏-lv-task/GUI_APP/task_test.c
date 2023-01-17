#include "task_test.h"
#include "lvgl.h"
#include "key.h"
#include "beep.h"
#include "usart.h"
#include "delay.h"

typedef struct{
	char name[20];
	u8 age;
}USER_DATA;//定义用户数据类型

lv_task_t *task1 = NULL;//任务句柄指针
//符合c99标准的写法，不用对不想赋值的变量进行赋值
USER_DATA maoxiaomi_data = { //maoxiaomi_data为用户自定义参数,数据结构一般为结构体
	.name = {"mao xiao mi"},
	.age = 100
};

//任务回调函数
void task1_cb(lv_task_t* task)
{
	USER_DATA* dat = (USER_DATA*)(task->user_data);//获取用户的自定义参数
	
	//打印tick时间(一个tick为1ms)和用户自定义参数
	printf("task1_cb_tick:%d,name:%s,age:%d\r\n",lv_tick_get(),dat->name,dat->age);
	
	//蜂鸣器鸣叫20ms进行提示
	BEEP = 1;
	delay_ms(30);
	BEEP = 0;
}

//例程入口函数
void task_test_start()
{
	//创建task1任务
	task1 = lv_task_create(task1_cb,5000,LV_TASK_PRIO_MID,&maoxiaomi_data);
}


//按键处理
void key_handler()
{
	u8 key = KEY_Scan(0);
	
	if(task1==NULL)
		return;
	if(key==KEY0_PRES)
	{
		//使任务复位,如果你以固定的时间间隔不断的重复按下KEY0键(间隔时间要小于5000ms的回调周期),
		//你会发现task1_cb回调函数再也得不到运行了,因为task1任务在被重复性的复位,
		//每一次复位将会导致重新等待一个完整的回调周期
		lv_task_reset(task1);
		printf("task_reset_tick:%d\r\n",lv_tick_get());
	}else if(key==KEY1_PRES)
	{
		//使任务立即准备就绪,当你按下KEY1键时,你会发现task1_cb回调函数会在下一个lv_task_handler调用时被立即运行,
		//通过串口打印,你会发现task_ready_tick的值比task1_cb_tick的值只小几个数
		lv_task_ready(task1);
		printf("task_ready_tick:%d\r\n",lv_tick_get());
	}else if(key==KEY2_PRES)//删除任务
	{
		//删除任务,当你按下KEY2键后,你会发现task1_cb回调函数将永远不会再被执行了
		lv_task_del(task1);
		task1 = NULL;
		printf("task_del_tick:%d\r\n",lv_tick_get());
	}
}











