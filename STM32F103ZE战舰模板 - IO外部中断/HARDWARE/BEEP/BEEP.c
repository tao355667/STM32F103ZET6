#include "beep.h"
#include "stm32f10x.h"                  // Device header


void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//GPIOB时钟

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;//8引脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//50MHz
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//GPIO_SetBits(GPIOB,GPIO_Pin_8);
	//GPIO_ResetBits(GPIOB,GPIO_Pin_8);
}

