#include "task_test.h"
#include "lvgl.h"
#include "key.h"
#include "beep.h"
#include "usart.h"
#include "delay.h"

typedef struct{
	char name[20];
	u8 age;
}USER_DATA;//�����û���������

lv_task_t *task1 = NULL;//������ָ��
//����c99��׼��д�������öԲ��븳ֵ�ı������и�ֵ
USER_DATA maoxiaomi_data = { //maoxiaomi_dataΪ�û��Զ������,���ݽṹһ��Ϊ�ṹ��
	.name = {"mao xiao mi"},
	.age = 100
};

//����ص�����
void task1_cb(lv_task_t* task)
{
	USER_DATA* dat = (USER_DATA*)(task->user_data);//��ȡ�û����Զ������
	
	//��ӡtickʱ��(һ��tickΪ1ms)���û��Զ������
	printf("task1_cb_tick:%d,name:%s,age:%d\r\n",lv_tick_get(),dat->name,dat->age);
	
	//����������20ms������ʾ
	BEEP = 1;
	delay_ms(30);
	BEEP = 0;
}

//������ں���
void task_test_start()
{
	//����task1����
	task1 = lv_task_create(task1_cb,5000,LV_TASK_PRIO_MID,&maoxiaomi_data);
}


//��������
void key_handler()
{
	u8 key = KEY_Scan(0);
	
	if(task1==NULL)
		return;
	if(key==KEY0_PRES)
	{
		//ʹ����λ,������Թ̶���ʱ�������ϵ��ظ�����KEY0��(���ʱ��ҪС��5000ms�Ļص�����),
		//��ᷢ��task1_cb�ص�������Ҳ�ò���������,��Ϊtask1�����ڱ��ظ��Եĸ�λ,
		//ÿһ�θ�λ���ᵼ�����µȴ�һ�������Ļص�����
		lv_task_reset(task1);
		printf("task_reset_tick:%d\r\n",lv_tick_get());
	}else if(key==KEY1_PRES)
	{
		//ʹ��������׼������,���㰴��KEY1��ʱ,��ᷢ��task1_cb�ص�����������һ��lv_task_handler����ʱ����������,
		//ͨ�����ڴ�ӡ,��ᷢ��task_ready_tick��ֵ��task1_cb_tick��ֵֻС������
		lv_task_ready(task1);
		printf("task_ready_tick:%d\r\n",lv_tick_get());
	}else if(key==KEY2_PRES)//ɾ������
	{
		//ɾ������,���㰴��KEY2����,��ᷢ��task1_cb�ص���������Զ�����ٱ�ִ����
		lv_task_del(task1);
		task1 = NULL;
		printf("task_del_tick:%d\r\n",lv_tick_get());
	}
}











