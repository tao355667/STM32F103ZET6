#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "beep.h"
#include "delay.h"
#include "key.h"
#include "wdg.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置 NVIC 中断分组 2
	delay_init();
	LED_Init();
	//BEEP_Init();
	KEY_Init();
	//BEEP=0;//BEEP高电平触发
	LED0=0;//LED0低电平触发
	//LED1=0;//LED1低电平触发
	delay_ms(500);
    WWDG_Init(0X7F,0X5F,WWDG_Prescaler_8);//计数器值为 7f,窗口寄存器为 5f,
    //分频数为 8
	while(1)
	{
		LED0=1;
	}
}


