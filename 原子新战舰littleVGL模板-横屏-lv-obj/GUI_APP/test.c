#include "test.h"

lv_obj_t* scr;
lv_obj_t* obj1,*obj2;
lv_obj_t* btn1;
lv_obj_t* child1;

//按钮回调函数
void btn1_event_cb(lv_obj_t* obj,lv_event_t event)
{

    if(obj==btn1)
    {
        if(event==LV_EVENT_RELEASED)
        {
            lv_obj_set_parent(child1,scr);
            lv_obj_move_foreground(obj1);

        }
    }else if(obj==obj1)
    {
        lv_obj_set_pos(obj1,10,10);
    }


}

void test_start(void)
{
    ////////////////样式1
    static lv_style_t style1;
    lv_style_copy(&style1,&lv_style_plain_color);
    style1.body.main_color=LV_COLOR_RED;
    style1.body.grad_color=LV_COLOR_RED;
    //scr////////////////
    scr=lv_scr_act();
    //obj1/////////
    obj1=lv_obj_create(scr,NULL);
    lv_obj_set_pos(obj1,50,50);
    lv_obj_set_click(obj1,true);
    lv_obj_set_event_cb(obj1,btn1_event_cb);
    //obj2//////////////
    obj2=lv_obj_create(scr,obj1);
    lv_obj_set_style(obj2,&style1);
    lv_obj_set_size(obj2,50,50);
    lv_obj_align(obj2,obj1,LV_ALIGN_OUT_BOTTOM_MID,0,-20);
    lv_obj_set_drag(obj2,true);
    //child1///////////
    child1=lv_obj_create(obj1,NULL);
    lv_obj_set_size(child1,20,20);
    lv_obj_set_style(child1,&style1);


    //按钮
    btn1=lv_btn_create(scr,NULL);
    lv_obj_set_pos(btn1,200,50);
    lv_obj_set_event_cb(btn1,btn1_event_cb);
}
