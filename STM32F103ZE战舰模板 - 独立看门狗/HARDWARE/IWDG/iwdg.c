#include "iwdg.h"


//��ʼ���������Ź�
void IWDG_Init(u8 prer,u16 rlr)//�������prer��rlr
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//ȡ��д����
	IWDG_SetPrescaler(prer);//Ԥ��Ƶϵ��
	IWDG_SetReload(rlr);//������װ�ؼĴ�����ֵ
	IWDG_ReloadCounter();//ι��������װ�ؼĴ�����ֵ���������
	IWDG_Enable();//ʹ�ܿ��Ź�
	
}
// ι��
void IWDG_Feed(void)
{
    // ����װ�ؼĴ�����ֵ�ŵ��������У�ι������ֹIWDG��λ
    // ����������ֵ����0��ʱ������ϵͳ��λ
    IWDG_ReloadCounter();
}
