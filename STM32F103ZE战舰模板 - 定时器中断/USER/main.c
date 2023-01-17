#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "beep.h"
#include "delay.h"
#include "key.h"
#include "timer.h"


int main(void)
{
	delay_init();
	LED_Init();
	KEY_Init();
	TIM3_Int_Init(4999,7199);
	
	LED0=0;//LED0低电平触发
	LED1=0;//LED1低电平触发
	
	while(1)
	{
		LED0=!LED0;
		delay_ms(200);
	}
}
