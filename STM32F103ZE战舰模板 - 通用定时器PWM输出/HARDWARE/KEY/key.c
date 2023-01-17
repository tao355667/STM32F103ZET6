#include "key.h"
#include "sys.h"
#include "delay.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//PE2,3,4上拉输入
	GPIO_Init(GPIOE,&GPIO_InitStructure);//初始化GPIOE2,3,4
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//下拉输入
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//PA0下拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIOA.0
	
}

//按键处理函数，mode0:点按，mode1:长按
u8 KEY_Scan(u8 mode)
{
	static u8 key_up=1;//按键松开为1
	if(mode)key_up=1;
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||WK_UP==1))
	{
		delay_ms(10);
		key_up=0;
		
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(WK_UP==1)return WKUP_PRES;
		
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&WK_UP==0) key_up=1;
	return 0;//无按键按下
	
}


