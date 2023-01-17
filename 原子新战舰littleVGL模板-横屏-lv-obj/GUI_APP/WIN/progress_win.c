#include "progress_win.h"
#include "gui_app.h"
#include <stdio.h>

static lv_obj_t * arc1;
static lv_obj_t * progress_label;
static lv_obj_t * bar1;
static lv_task_t * task = NULL;
uint8_t progress_val;

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

//���ý���ֵ
//val:��ΧΪ[0,100]
static void progress_set_val(uint8_t val)
{
	char buff[10];
	//����arc�Ľ���
	lv_arc_set_angles(arc1,0,(uint16_t)(3.6f*val));
	//����bar�Ľ���
	lv_bar_set_value(bar1,val,LV_ANIM_OFF);
	//������ʾ����ֵ�ı�ǩ
	sprintf(buff,"%d%%",val);
	lv_label_set_text(progress_label,buff);
	lv_obj_realign(progress_label);
}

//����ص�����
static void progress_task(lv_task_t * t)
{
	progress_val++;
	if(progress_val>100)
		 progress_val = 0;
	progress_set_val(progress_val);
}

//��������
void progress_win_create(lv_obj_t * parent)
{
	lv_obj_t * win = general_win_create(parent,"Progress");
	lv_obj_set_event_cb(win,event_handler);//�����¼��ص�����
	
	//����Ԥ���ض���
  lv_obj_t * preload1 = lv_preload_create(win,NULL);
  lv_obj_set_size(preload1,100,100);//���ô�С
  lv_obj_align(preload1,NULL,LV_ALIGN_IN_TOP_MID,0,40);//���ö��뷽ʽ
  lv_preload_set_arc_length(preload1,45);//����СԲ����Ӧ�ĽǶ�
  lv_preload_set_dir(preload1,LV_PRELOAD_DIR_BACKWARD);//����Ϊ��ʱ��
  lv_preload_set_type(preload1,LV_PRELOAD_TYPE_FILLSPIN_ARC);//������ת�����ķ�ʽ
  lv_preload_set_spin_time(preload1,2000);//������ת���ٶ�,תһȦ����Ҫ��ʱ��
	
	//��������
	arc1 = lv_arc_create(win, NULL);
	lv_arc_set_angles(arc1, 180, 90);//���ýǶ�
	lv_obj_set_size(arc1, 100, 100);//���ô�С,���õĿ�Ⱥ͸߶ȱ������,���ΰ뾶���ڿ�ȵ�һ��
	lv_obj_align(arc1,preload1,LV_ALIGN_OUT_BOTTOM_MID,0,15);
	//����һ��������ʾ���ν��ȵı�ǩ
	progress_label = lv_label_create(win,NULL);
  lv_obj_align(progress_label,arc1,LV_ALIGN_CENTER,0,0);
	
	//����һ��ˮƽ������
	bar1 = lv_bar_create(win, NULL);
	lv_obj_set_size(bar1,180,10);//���ô�С,�����ȱȸ߶�С,�Ǿ��Ǵ�ֱ��������
	lv_obj_align(bar1,arc1,LV_ALIGN_OUT_BOTTOM_MID,0,15);
	
	//����Ĭ�Ͻ���
	progress_val = 0;
	progress_set_val(progress_val);
	//����һ��������ģ����ȵļ��ع���
	if(task==NULL)
		task = lv_task_create(progress_task,400,LV_TASK_PRIO_MID,NULL);
}

















