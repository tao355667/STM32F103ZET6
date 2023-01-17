#ifndef __GUI_APP_H__
#define __GUI_APP_H__
#include "sys.h"
#include "lvgl.h"

//���巵���¼�,���������Լ������һ���¼�,�������ֵֻҪ����littleVGL�Դ����¼�ֵ��ͻ����
//LV_EVENT_DELETE����littleVGL����������һ���¼�,��10��Ϊ����������
#define USER_EVENT_BACK		(LV_EVENT_DELETE+10)  

//��������
void gui_app_start(void);
void toast(const char * msg,uint16_t time);
lv_obj_t * general_win_create(lv_obj_t * parent,const char * title);


#endif
