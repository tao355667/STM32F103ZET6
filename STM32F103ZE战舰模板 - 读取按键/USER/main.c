#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "beep.h"
#include "delay.h"
#include "key.h"

u8 key;

int main(void)
{
	delay_init();
	LED_Init();
	BEEP_Init();
	KEY_Init();
	BEEP=0;//BEEP高电平触发
	LED0=0;//LED0低电平触发
	LED1=0;//LED1低电平触发
	while(1)
	{
		key=KEY_Scan(0);
		if(key)
		{
			//u8 t=key;
			switch(key)
			{
				case WKUP_PRES:
					BEEP=!BEEP;break;
				case KEY2_PRES:
					LED0=!LED0;break;
				case KEY1_PRES:
					LED1=!LED1;break;
				case KEY0_PRES:
					LED0=!LED0;
					LED1=!LED1;break;
			}
		}else delay_ms(10);


	}
}
