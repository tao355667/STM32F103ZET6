#include "test1.h"

void test_start(void)
{
    //获取当前的屏幕对象
    lv_obj_t * scr = lv_disp_get_scr_act(NULL);

    //在屏幕上创建一个label控件
    lv_obj_t * label1 =  lv_label_create(scr, NULL);

    //设置label的文本内容
    lv_label_set_text(label1, "I am iron man  !!!");

    //设置文本和父控件(在这里就是屏幕)居中对齐
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);


}
