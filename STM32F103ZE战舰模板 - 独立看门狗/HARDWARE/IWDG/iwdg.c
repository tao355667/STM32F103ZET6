#include "iwdg.h"


//初始化独立看门狗
void IWDG_Init(u8 prer,u16 rlr)//传入参数prer和rlr
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//取消写保护
	IWDG_SetPrescaler(prer);//预分频系数
	IWDG_SetReload(rlr);//设置重装载寄存器的值
	IWDG_ReloadCounter();//喂狗，将重装载寄存器的值放入计数器
	IWDG_Enable();//使能看门狗
	
}
// 喂狗
void IWDG_Feed(void)
{
    // 把重装载寄存器的值放到计数器中，喂狗，防止IWDG复位
    // 当计数器的值减到0的时候会产生系统复位
    IWDG_ReloadCounter();
}
