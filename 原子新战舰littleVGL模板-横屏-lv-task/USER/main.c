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

//#define TEST_NUM 3 //1,2,3,4 �ֱ��Ӧ��ʾ����


int main(void)
{	 		    
	delay_init();	    	 		//��ʱ������ʼ��	  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 		//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     		//LED�˿ڳ�ʼ��
	KEY_Init();	 						//������ʼ��
	BEEP_Init();						//��������ʼ��
	TIM3_Int_Init(999,71);	//��ʱ����ʼ��(1ms�ж�),���ڸ�lvgl�ṩ1ms����������
	FSMC_SRAM_Init();				//�ⲿ1MB��sram��ʼ��
	LCD_Init();							//LCD��ʼ��			
 	tp_dev.init();					//��������ʼ��
	
	lv_init();							//lvglϵͳ��ʼ��
	lv_port_disp_init();		//lvgl��ʾ�ӿڳ�ʼ��
	lv_port_indev_init();		//lvgl����ӿڳ�ʼ��
	
	
//	#if(TEST_NUM==1)
//		demo_create();
//	#elif(TEST_NUM==2)
//		lv_test_theme_1(lv_theme_night_init(210, NULL));
//	#elif(TEST_NUM==3)
//		lv_test_theme_2();
//	#else
//		gui_app_start(); 	//��������
//	#endif

	task_test_start();
	
	while(1)
	{
		tp_dev.scan(0);
		lv_task_handler();
		
		key_handler();
	}
}


