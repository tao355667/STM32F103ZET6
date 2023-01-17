#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "beep.h"
#include "delay.h"
#include "key.h"
#include "iwdg.h"

u8 key;

int main(void)
{
	delay_init();
	LED_Init();
	BEEP_Init();
	KEY_Init();
	
	//BEEP=0;//BEEP高电平触发
	//LED0=0;//LED0低电平触发
	//LED1=0;//LED1低电平触发
	
	delay_ms(200);
	LED0=0;//LED0低电平触发
	//IWDG_Init(4,625);//prer为4，rlr为625，记数时间为1s
	IWDG_Init(4,1250);//prer为4，rlr为625，记数时间为2s
	while(1)
	{
		if(KEY_Scan(0)==WKUP_PRES){
			IWDG_Feed();//喂狗
			
		}
	}
}
