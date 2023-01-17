#include "stm32f10x.h"                  // Device header
#include "beep.h"
#include "delay.h"

int main(void)
{
	delay_init();
	BEEP_Init();
	
	while(1)
	{
		
		GPIO_SetBits(GPIOB,GPIO_Pin_8);
		delay_ms(1000);
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		delay_ms(1000);
	}
}
