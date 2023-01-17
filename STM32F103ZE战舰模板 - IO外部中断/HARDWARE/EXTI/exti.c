#include "stm32f10x.h"                  // Device header
#include "exti.h"
#include "led.h"
#include "key.h"
#include "beep.h"
#include "delay.h"
//#include "usart.h"


void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructureKEY0,EXTI_InitStructureKEY1,EXTI_InitStructureKEY2,EXTI_InitStructureKEYWK;
	NVIC_InitTypeDef NVIC_InitStructureKEY0,NVIC_InitStructureKEY1,NVIC_InitStructureKEY2,NVIC_InitStructureKEYWK;
	
	KEY_Init();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);//PE4-KEY0，IO口与中断线的映射关系
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);//PE3-KEY1
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);//PE2-KEY2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);//PA0-WK_UP
	
	
	EXTI_InitStructureKEY0.EXTI_Line=EXTI_Line4;//指定要配置的中断线
	EXTI_InitStructureKEY0.EXTI_LineCmd=ENABLE;//使能/失能
	EXTI_InitStructureKEY0.EXTI_Mode=EXTI_Mode_Interrupt;//模式：事件/中断
	EXTI_InitStructureKEY0.EXTI_Trigger=EXTI_Trigger_Falling;//触发方式：上升/下降/双沿
	EXTI_Init(&EXTI_InitStructureKEY0);//KEY0中断初始化
	
	EXTI_InitStructureKEY1.EXTI_Line=EXTI_Line3;
	EXTI_InitStructureKEY1.EXTI_LineCmd=ENABLE;
	EXTI_InitStructureKEY1.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructureKEY1.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructureKEY1);//KEY1中断初始化
	
	EXTI_InitStructureKEY2.EXTI_Line=EXTI_Line2;
	EXTI_InitStructureKEY2.EXTI_LineCmd=ENABLE;
	EXTI_InitStructureKEY2.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructureKEY2.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructureKEY2);//KEY2中断初始化
	
	EXTI_InitStructureKEYWK.EXTI_Line=EXTI_Line0;
	EXTI_InitStructureKEYWK.EXTI_LineCmd=ENABLE;
	EXTI_InitStructureKEYWK.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructureKEYWK.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructureKEYWK);//WK_UP中断初始化
	
	NVIC_InitStructureKEY0.NVIC_IRQChannel=EXTI4_IRQn;//中断通道
	NVIC_InitStructureKEY0.NVIC_IRQChannelCmd=ENABLE;//
	NVIC_InitStructureKEY0.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级
	NVIC_InitStructureKEY0.NVIC_IRQChannelSubPriority=0;//响应优先级
	NVIC_Init(&NVIC_InitStructureKEY0);//KEY0优先级
	
	NVIC_InitStructureKEY1.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_InitStructureKEY1.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructureKEY1.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructureKEY1.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructureKEY1);//KEY1优先级
	
	NVIC_InitStructureKEY2.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_InitStructureKEY2.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructureKEY2.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructureKEY2.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructureKEY2);//KEY2优先级
	
	NVIC_InitStructureKEYWK.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructureKEYWK.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructureKEYWK.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructureKEYWK.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStructureKEYWK);//WK_UP优先级
	
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY0==0){
		LED0=!LED0;
		LED1=!LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);//清除中断标志位，以保证此中断下次仍可触发
}

void EXTI3_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY1==0){
		LED0=!LED0;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);//清除中断标志位，以保证此中断下次仍可触发
}

void EXTI2_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY2==0){
		LED1=!LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line2);//清除中断标志位，以保证此中断下次仍可触发
}

void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(WK_UP==1){
		BEEP=!BEEP;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);//清除中断标志位，以保证此中断下次仍可触发
}
