#ifndef __WDG_H
#define __WDG_H
#include "stm32f10x.h"

void WWDG_Init(u8 tr,u8 wr,u32 fprer);
void WWDG_Set_Counter(u8 cnt);
void WWDG_NVIC_Init(void);
void WWDG_IRQHandler(void);




#endif
