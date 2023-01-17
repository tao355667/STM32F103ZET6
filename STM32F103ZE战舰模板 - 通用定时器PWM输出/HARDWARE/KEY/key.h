#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"
#include "sys.h"

#define KEY0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define KEY2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define WK_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)

#define KEY0_PRES 1  //按键0按下
#define KEY1_PRES 2  //按键1按下
#define KEY2_PRES 3  //按键2按下
#define WKUP_PRES 4  //按键WK_UP按下


void KEY_Init(void);
u8 KEY_Scan(u8);



#endif

