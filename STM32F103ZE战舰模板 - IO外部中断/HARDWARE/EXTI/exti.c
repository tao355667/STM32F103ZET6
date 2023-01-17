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
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);//PE4-KEY0��IO�����ж��ߵ�ӳ���ϵ
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);//PE3-KEY1
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);//PE2-KEY2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);//PA0-WK_UP
	
	
	EXTI_InitStructureKEY0.EXTI_Line=EXTI_Line4;//ָ��Ҫ���õ��ж���
	EXTI_InitStructureKEY0.EXTI_LineCmd=ENABLE;//ʹ��/ʧ��
	EXTI_InitStructureKEY0.EXTI_Mode=EXTI_Mode_Interrupt;//ģʽ���¼�/�ж�
	EXTI_InitStructureKEY0.EXTI_Trigger=EXTI_Trigger_Falling;//������ʽ������/�½�/˫��
	EXTI_Init(&EXTI_InitStructureKEY0);//KEY0�жϳ�ʼ��
	
	EXTI_InitStructureKEY1.EXTI_Line=EXTI_Line3;
	EXTI_InitStructureKEY1.EXTI_LineCmd=ENABLE;
	EXTI_InitStructureKEY1.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructureKEY1.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructureKEY1);//KEY1�жϳ�ʼ��
	
	EXTI_InitStructureKEY2.EXTI_Line=EXTI_Line2;
	EXTI_InitStructureKEY2.EXTI_LineCmd=ENABLE;
	EXTI_InitStructureKEY2.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructureKEY2.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructureKEY2);//KEY2�жϳ�ʼ��
	
	EXTI_InitStructureKEYWK.EXTI_Line=EXTI_Line0;
	EXTI_InitStructureKEYWK.EXTI_LineCmd=ENABLE;
	EXTI_InitStructureKEYWK.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructureKEYWK.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructureKEYWK);//WK_UP�жϳ�ʼ��
	
	NVIC_InitStructureKEY0.NVIC_IRQChannel=EXTI4_IRQn;//�ж�ͨ��
	NVIC_InitStructureKEY0.NVIC_IRQChannelCmd=ENABLE;//
	NVIC_InitStructureKEY0.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�
	NVIC_InitStructureKEY0.NVIC_IRQChannelSubPriority=0;//��Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStructureKEY0);//KEY0���ȼ�
	
	NVIC_InitStructureKEY1.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_InitStructureKEY1.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructureKEY1.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructureKEY1.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructureKEY1);//KEY1���ȼ�
	
	NVIC_InitStructureKEY2.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_InitStructureKEY2.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructureKEY2.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructureKEY2.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructureKEY2);//KEY2���ȼ�
	
	NVIC_InitStructureKEYWK.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructureKEYWK.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructureKEYWK.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructureKEYWK.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStructureKEYWK);//WK_UP���ȼ�
	
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY0==0){
		LED0=!LED0;
		LED1=!LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);//����жϱ�־λ���Ա�֤���ж��´��Կɴ���
}

void EXTI3_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY1==0){
		LED0=!LED0;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);//����жϱ�־λ���Ա�֤���ж��´��Կɴ���
}

void EXTI2_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY2==0){
		LED1=!LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line2);//����жϱ�־λ���Ա�֤���ж��´��Կɴ���
}

void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(WK_UP==1){
		BEEP=!BEEP;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);//����жϱ�־λ���Ա�֤���ж��´��Կɴ���
}
