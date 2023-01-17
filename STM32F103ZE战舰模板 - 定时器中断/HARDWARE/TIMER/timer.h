#ifndef __TIMER_H
#define __TIMER_H
#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "led.h"

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void);


#endif
