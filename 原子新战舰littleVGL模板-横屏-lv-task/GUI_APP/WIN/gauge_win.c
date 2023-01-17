#include "gauge_win.h"
#include "gui_app.h"
#include <stdio.h>

static lv_obj_t * gauge1;
static lv_obj_t * label1;
static lv_obj_t * lmeter1;
static int16_t speed_val = 0;
lv_color_t needle_colors[2];//ÿһ��ָ�����ɫ
static lv_task_t * task = NULL;

//�¼��ص�����
static void event_handler(lv_obj_t * obj,lv_event_t event)
{
	if(event==USER_EVENT_BACK)//���巵���¼�,������Ͻǵ�"< Back"��ť�ᴥ�����¼�
	{
		if(task)//ɾ��������
		{
			lv_task_del(task);
			task = NULL;
		}
	}
}

//����ص�����
void task_cb(lv_task_t * task)
{
	static uint8_t is_add_dir = 1;//�Ƿ����ٶ����ӵķ���
	char buff[40];

	if(is_add_dir)
	{
			speed_val += 5;
			if(speed_val>=100)
				is_add_dir = 0;
	}else
	{
			speed_val -= 5;
			if(speed_val<=0)
				is_add_dir = 1;
	}
	//����ָ�����ֵ
	lv_gauge_set_value(gauge1,0,speed_val);
	//�Ѵ��ٶ���ʾ�ڱ�ǩ��,Ȼ����ݲ�ͬ����ֵ��ʾ����ͬ����ɫ
	//��ɫ����ȫ,��ɫ������,��ɫ����Σ��  
	sprintf(buff,"#%s %d km/h#",speed_val<60?"00FF00":(speed_val<90?"FFFF00":"FF0000"),speed_val); 
	lv_label_set_text(label1,buff);
	//���ÿ̶�ָʾ������ֵ
	lv_lmeter_set_value(lmeter1,speed_val);
}

//��������
void gauge_win_create(lv_obj_t * parent)
{
	lv_obj_t * win;
	win = general_win_create(parent,"Gauge");
	lv_obj_set_event_cb(win,event_handler);//�����¼��ص�����
	
	//�����Ǳ���
	gauge1 = lv_gauge_create(win, NULL);
	lv_obj_set_size(gauge1,200,200);//���ô�С
	lv_gauge_set_range(gauge1,0,100);//�����Ǳ��̵ķ�Χ
	needle_colors[0] = LV_COLOR_BLUE;
	needle_colors[1] = LV_COLOR_PURPLE;
	lv_gauge_set_needle_count(gauge1,sizeof(needle_colors)/sizeof(needle_colors[0]),needle_colors);
	lv_gauge_set_value(gauge1,0,speed_val);//����ָ��1ָ�����ֵ,���ǰ�ָ��1�����ٶ�ָ��
	lv_gauge_set_value(gauge1,1,90);//����ָ��2ָ�����ֵ,������ָ��ؼ���ֵ��
	lv_gauge_set_critical_value(gauge1,90);//���ùؼ���ֵ��
	lv_gauge_set_scale(gauge1,240,31,6);//���ýǶ�,�̶��ߵ�����,��ֵ��ǩ������
	lv_obj_align(gauge1,NULL,LV_ALIGN_IN_TOP_MID,0,40);//���ö��뷽ʽ
	
	//����һ����ǩ,������ʾ�Ǳ�����ָ��1����ֵ
	label1 = lv_label_create(win,NULL);
	lv_label_set_long_mode(label1,LV_LABEL_LONG_BREAK);//���ó��ı�ģʽ
	lv_obj_set_width(label1,80);//���ÿ��
	lv_label_set_align(label1,LV_LABEL_ALIGN_CENTER);//�����ı����ж���
	lv_label_set_body_draw(label1,true);//ʹ�ܱ����ػ�
	lv_obj_align(label1,gauge1,LV_ALIGN_CENTER,0,60);//���ö��뷽ʽ
	lv_label_set_text(label1,"0 km/h");//�����ı�
	lv_label_set_recolor(label1,true);//ʹ���ı��ػ�ɫ
	
	//����һ���̶�ָʾ��
	lmeter1 = lv_lmeter_create(win,NULL);
	lv_obj_set_size(lmeter1,150,150);//���ô�С
	lv_obj_align(lmeter1,gauge1,LV_ALIGN_OUT_BOTTOM_MID,0,10);//���ö��뷽ʽ
	lv_lmeter_set_range(lmeter1,0,100);//���÷�Χ
	lv_lmeter_set_value(lmeter1,speed_val);//���õ�ǰ��ֵ
	lv_lmeter_set_scale(lmeter1,240,31);//���ýǶȺͿ̶��ߵ�����
	
	
	//����һ��������ģ���ٶ�ָ��ı仯 
	if(task==NULL)
		task = lv_task_create(task_cb,600,LV_TASK_PRIO_MID,NULL);
}













