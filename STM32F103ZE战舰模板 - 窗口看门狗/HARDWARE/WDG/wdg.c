#include "wdg.h"
#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

//����WWDG������������ֵ,Ĭ��Ϊ���. 
u8 WWDG_CNT=0x7f; 
//��ʼ�����ڿ��Ź� 	
//tr   :T[6:0],������ֵ 
//wr   :W[6:0],����ֵ 
//fprer:��Ƶϵ����WDGTB��,�����2λ��Ч 
//Fwwdg=PCLK1/(4096*2^fprer). 

void WWDG_Init(u8 tr,u8 wr,u32 fprer)
{ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);  //   WWDGʱ��ʹ��

	WWDG_CNT=tr&WWDG_CNT;   //��ʼ��WWDG_CNT.   
	WWDG_SetPrescaler(fprer);//����IWDGԤ��Ƶֵ
	WWDG_SetWindowValue(wr);//���ô���ֵ
	WWDG_Enable(WWDG_CNT);	 //ʹ�ܿ��Ź������ü�������ֵ                 
	WWDG_ClearFlag();//�����ǰ�����жϱ�־λ 
	WWDG_NVIC_Init();//��ʼ�����ڿ��Ź� NVIC
	WWDG_EnableIT(); //�������ڿ��Ź��ж�
} 
//������WWDG��������ֵ
void WWDG_Set_Counter(u8 cnt)
{
    WWDG_Enable(cnt);//ʹ�ܿ��Ź� ,	���� counter .	 
}
//���ڿ��Ź��жϷ������
void WWDG_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;    //WWDG�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //��ռ2�������ȼ�3����2	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	 //��ռ2�������ȼ�3����2	
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; 
	NVIC_Init(&NVIC_InitStructure);//NVIC��ʼ��
}

void WWDG_IRQHandler(void)
{

	WWDG_SetCounter(WWDG_CNT);	  //�������˾��,���ڿ��Ź���������λ
    LED1=!LED1;
	//delay_ms(500);
	WWDG_ClearFlag();	  //�����ǰ�����жϱ�־λ
}

