#include "main_win.h"
#include "gui_app.h"
#include "login_win.h"
#include "calendar_win.h"
#include "progress_win.h"
#include "chart_win.h"
#include "gauge_win.h"

//����ͼƬ
LV_IMG_DECLARE(logo_img);
LV_IMG_DECLARE(date_img);
LV_IMG_DECLARE(chart_img);
LV_IMG_DECLARE(gauge_img);
LV_IMG_DECLARE(progress_img);
//��������
LV_FONT_DECLARE(my_font);//����������ֻ������ԭ���ĸ�����

//��������
#define TABLE_COL_CNT   		3   //��������
#define TABLE_ROW_CNT   		3   //���Ŀ��
#define SPLIT_LINE_WIDTH		200 //ˮƽ�ָ��ߵĿ��
const lv_point_t SPLIT_LINE_POINTS[2] = {{0,0},{SPLIT_LINE_WIDTH,0}};
const char * const BTNM_MAP[] = {
	"    "LV_SYMBOL_AUDIO"\nAUDIO","  "LV_SYMBOL_BELL"\nBELL","\n",
	"   "LV_SYMBOL_CALL"\nCALL","  "LV_SYMBOL_GPS"\nGPS",
	""
};
const char * const BTNM_TITLE[] = {"audio btn","bell btn","call btn","gps btn"};
const char * const MBOX_MAP[] ={"Yes","No",""};
//������ÿһ�е�����
const char * const TABLE_CELL_VALUE[TABLE_ROW_CNT][TABLE_COL_CNT] = {
  {"Name","Sex","Age"},//��һ��,��Ϊ������
  {"fish","man","25"},
  {"xjy","woman","26"}
};

lv_obj_t *  main_win;
static lv_obj_t * quit_btn;
static lv_obj_t * btnm;
static lv_obj_t * quit_mbox = NULL;
static lv_obj_t * calendar_item_btn,* progress_item_btn,* chart_item_btn,* gauge_item_btn;


//��������
void quit_mbox_create(lv_obj_t * parent);

//�¼��ص�����
static void event_handler(lv_obj_t * obj,lv_event_t event)
{
	uint16_t btn_id;
	if(obj==quit_btn)
	{
		if(event==LV_EVENT_RELEASED)
		{
			quit_mbox_create(lv_obj_get_parent(obj));//�Ƿ��˳�?
		}
	}else if(obj==btnm)
	{
		if(event==LV_EVENT_VALUE_CHANGED)
		{
			btn_id = *((uint16_t*)lv_event_get_data());//��ȡ����ť�еİ�ťid
			toast(BTNM_TITLE[btn_id],1000);
		}
	}else if(obj==quit_mbox)
	{
		if(event==LV_EVENT_VALUE_CHANGED)
		{
			lv_obj_del(quit_mbox);//�ر��˳��Ի���
			quit_mbox = NULL;
			btn_id = *((uint16_t*)lv_event_get_data());//��ȡ�˳��Ի����еİ�ťid
			if(btn_id==0)//�����Yes��ť
			{
				lv_obj_del(main_win);//ɾ��������
				login_win_create(lv_scr_act());//���ص���¼����
			}
		}
	}else if(obj==calendar_item_btn)
	{
		//���б���ֹ���ʱ,��LV_EVENT_CLICKED�����������¼����LV_EVENT_RELEASED��һЩ,
		//��Ϊ�����б�ʱ,LV_EVENT_CLICKED�¼���������󴥷�,��LV_EVENT_RELEASED���󴥷�
		if(event==LV_EVENT_CLICKED) 
			calendar_win_create(lv_scr_act());//��ת��calendar����
	}else if(obj==progress_item_btn)
	{
		if(event==LV_EVENT_CLICKED)
			progress_win_create(lv_scr_act());//��ת��progress����
	}else if(obj==chart_item_btn)
	{
		if(event==LV_EVENT_CLICKED)
			chart_win_create(lv_scr_act());//��ת��chart����
	}else if(obj==gauge_item_btn)
	{
		if(event==LV_EVENT_CLICKED)
			gauge_win_create(lv_scr_act());//��ת��gauge����
	}
}

//�����˳�ȷ�ϵ���Ϣ�Ի���
void quit_mbox_create(lv_obj_t * parent)
{
	if(quit_mbox)//��Ҫ�ظ�����
		return;
	quit_mbox = lv_mbox_create(parent,NULL);
	lv_obj_set_size(quit_mbox,lv_obj_get_width(parent)*0.7f,lv_obj_get_height(parent)/2);
	lv_mbox_set_text(quit_mbox,"Tip\nAre you to quit?");
	lv_mbox_add_btns(quit_mbox,(const char**)MBOX_MAP);
	lv_obj_set_drag(quit_mbox,true);//���öԻ�����Ա���ק
	lv_obj_align(quit_mbox,NULL,LV_ALIGN_CENTER,0,0);
	lv_obj_set_event_cb(quit_mbox,event_handler);
}

//��ҳѡ���ʼ��
void home_tab_init(lv_obj_t * parent)
{
	//��������
	static lv_style_t title_style;
	lv_obj_t * title_label = lv_label_create(parent,NULL);
	lv_style_copy(&title_style,lv_obj_get_style(title_label));//���Ʊ�ǩ֮ǰ��������ʽ
	title_style.text.font = &my_font;//�ı�����
	lv_label_set_style(title_label,LV_LABEL_STYLE_MAIN,&title_style);//�����µ���ʽ
	lv_label_set_text(title_label,"\xE6\xAD\xA3\xE7\x82\xB9\xE5\x8E\x9F\xE5\xAD\x90");//����"����ԭ��"��UTF-8����
	lv_obj_align(title_label,NULL,LV_ALIGN_IN_TOP_MID,0,10);
	
	//�����б�
	lv_obj_t * list = lv_list_create(parent,NULL);
  lv_obj_set_size(list,lv_obj_get_width(parent)*0.9f,lv_obj_get_height(parent)-60);
	lv_obj_align(list,title_label,LV_ALIGN_OUT_BOTTOM_MID,0,10);
	lv_list_set_sb_mode(list,LV_SB_MODE_AUTO);
	//����б���1,��2��
  calendar_item_btn = lv_list_add_btn(list,&date_img,"#FFFFFF Calendar#\n#666666 This is the date#");
	lv_obj_t * item_label = lv_list_get_btn_label(calendar_item_btn);
	lv_label_set_recolor(item_label,true);
	lv_obj_set_event_cb(calendar_item_btn,event_handler);//�����¼��ص�����
	//����б���2
  progress_item_btn = lv_list_add_btn(list,&progress_img,"Progress");
	lv_obj_set_event_cb(progress_item_btn,event_handler);//�����¼��ص�����
	//����б���3
  chart_item_btn = lv_list_add_btn(list,&chart_img,"Chart");
	lv_obj_set_event_cb(chart_item_btn,event_handler);//�����¼��ص�����
	//����б���4
  gauge_item_btn = lv_list_add_btn(list,&gauge_img,"Gauge");
	lv_obj_set_event_cb(gauge_item_btn,event_handler);//�����¼��ص�����
	
}


//����ѡ���ʼ��
void setting_tab_init(lv_obj_t * parent)
{
	uint16_t parent_width = lv_obj_get_width(parent);//��ȡ������Ŀ��
	
  //����ͷ��
	lv_obj_t * head_img = lv_img_create(parent,NULL);
	lv_img_set_src(head_img,&logo_img);
	lv_obj_set_pos(head_img,20,20);
	//�����û�����id
	lv_obj_t * name_id_label = lv_label_create(parent,NULL);
	lv_label_set_recolor(name_id_label,true);
	lv_label_set_text(name_id_label,"#FFFFFF Xiong jia yu#\n#BBBBBB ID:15727652280#");
	lv_obj_align(name_id_label,head_img,LV_ALIGN_OUT_RIGHT_MID,20,0);
	//����һ��ˮƽ�ָ����
	lv_obj_t * split_line = lv_line_create(parent,NULL);
	lv_obj_set_size(split_line,SPLIT_LINE_WIDTH,2);
	lv_line_set_points(split_line,SPLIT_LINE_POINTS,2);
	lv_obj_align(split_line,NULL,LV_ALIGN_IN_TOP_MID,0,100);
	//��������ť
	btnm = lv_btnm_create(parent,NULL);
	lv_obj_set_size(btnm,parent_width*0.8f,100);
	lv_obj_align(btnm,split_line,LV_ALIGN_OUT_BOTTOM_MID,0,10);
	lv_btnm_set_map(btnm,(const char**)BTNM_MAP);
	lv_obj_set_event_cb(btnm,event_handler);
	//����һ�����
	lv_obj_t * table = lv_table_create(parent,NULL);
	lv_table_set_col_cnt(table,TABLE_COL_CNT);//��������
	lv_table_set_row_cnt(table,TABLE_ROW_CNT);//��������
	uint8_t row,col;
	for(col=0;col<TABLE_COL_CNT;col++)
	{
		lv_table_set_col_width(table,col,parent_width*(0.8f/TABLE_COL_CNT));//�����еĿ��
		lv_table_set_cell_align(table,0,col,LV_LABEL_ALIGN_CENTER);//�����е��ı����ж���
	}
	for(row=0;row<TABLE_ROW_CNT;row++)
	{
		for(col=0;col<TABLE_COL_CNT;col++)
			lv_table_set_cell_value(table,row,col,(const char*)TABLE_CELL_VALUE[row][col]);//����ÿһ����Ԫ����ı�����
	}
	lv_obj_align(table,btnm,LV_ALIGN_OUT_BOTTOM_MID,0,10);//���ñ��Ķ��뷽ʽ
	
	//����һ���˳���ť
	quit_btn = lv_btn_create(parent,NULL);
	lv_obj_set_width(quit_btn,parent_width/2);
	lv_obj_align(quit_btn,table,LV_ALIGN_OUT_BOTTOM_MID,0,30);
	lv_obj_t * quit_label = lv_label_create(quit_btn,NULL);
	lv_label_set_recolor(quit_label,true);
	lv_label_set_text(quit_label,"#FF0000 Quit#");
	lv_obj_set_event_cb(quit_btn,event_handler);
	
}


//����������
void main_win_create(lv_obj_t * parent)
{
	//Ϊ�˼��ٸ�����,���������ֱ�Ӱ�tabview��Ϊmain_win������
	main_win = lv_tabview_create(parent,NULL);
	lv_tabview_set_btns_pos(main_win,LV_TABVIEW_BTNS_POS_BOTTOM);//ѡ���ťλ�ڵײ�
	//���tab1ѡ�
  lv_obj_t * home_tab = lv_tabview_add_tab(main_win,LV_SYMBOL_HOME" Home");
  home_tab_init(home_tab);
  //���tab1ѡ�
  lv_obj_t * setting_tab = lv_tabview_add_tab(main_win,LV_SYMBOL_SETTINGS" Setting");
  setting_tab_init(setting_tab);
}










