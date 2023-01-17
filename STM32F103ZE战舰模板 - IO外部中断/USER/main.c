#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "beep.h"
#include "delay.h"
#include "key.h"
#include "exti.h"
//#include "usart.h"

int main(void)
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2：2位抢占优先级，2位响应优先级
	//uart_init(115200);
	LED_Init();
	BEEP_Init();
	EXTIX_Init();
	
	LED0=0;//LED0初始状态
	LED1=0;//LED1初始状态
	BEEP=0;//BEEP初始状态
	
	while(1)
	{
		//printf("OK\r\n");
		//delay_ms(10);
	}
	
}
