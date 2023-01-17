#include "led.h"
#include "delay.h"
#include "key.h"
#include "beep.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "touch.h"
#include "timer.h"
#include "sram.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_apps\demo\demo.h" 
#include "lv_tests\lv_test_theme\lv_test_theme_1.h" 
#include "lv_tests\lv_test_theme\lv_test_theme_2.h"
#include "gui_app.h"
#include "task_test.h"

//#define TEST_NUM 3 //1,2,3,4 分别对应演示例程


int main(void)
{	 		    
	delay_init();	    	 		//延时函数初始化	  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 		//串口初始化为115200
 	LED_Init();			     		//LED端口初始化
	KEY_Init();	 						//按键初始化
	BEEP_Init();						//蜂鸣器初始化
	TIM3_Int_Init(999,71);	//定时器初始化(1ms中断),用于给lvgl提供1ms的心跳节拍
	FSMC_SRAM_Init();				//外部1MB的sram初始化
	LCD_Init();							//LCD初始化			
 	tp_dev.init();					//触摸屏初始化
	
	lv_init();							//lvgl系统初始化
	lv_port_disp_init();		//lvgl显示接口初始化
	lv_port_indev_init();		//lvgl输入接口初始化
	
	
//	#if(TEST_NUM==1)
//		demo_create();
//	#elif(TEST_NUM==2)
//		lv_test_theme_1(lv_theme_night_init(210, NULL));
//	#elif(TEST_NUM==3)
//		lv_test_theme_2();
//	#else
//		gui_app_start(); 	//运行例程
//	#endif

	task_test_start();
	
	while(1)
	{
		tp_dev.scan(0);
		lv_task_handler();
		
		key_handler();
	}
}


