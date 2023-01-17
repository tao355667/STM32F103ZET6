#include "stm32f10x.h"                  // Device header
//#include "led.h"
//#include "beep.h"
//#include "delay.h"
//#include "key.h"

void My_USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//GPIO初始化结构体
	USART_InitTypeDef USART_InitStructure;//USART结构体
	NVIC_InitTypeDef NVIC_InitStructure;//中断结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化9引脚，输出

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮动输入
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化10引脚，输入
	
	USART_InitStructure.USART_BaudRate=115200;//波特率
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//硬件流，这里不使用
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//模式：输入/输出
	USART_InitStructure.USART_Parity=USART_Parity_No;//奇偶校验
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//字长
	USART_Init(USART1,&USART_InitStructure);//初始化串口1
	USART_Cmd(USART1, ENABLE);//串口使能
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开始接收中断
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;//使能按键外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//使能外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//子优先级 2
	NVIC_Init(&NVIC_InitStructure);//初始化中断
}
void USART1_IRQHandler(void)//中断服务函数，名字在startup_stm32f10x_hd.s文件里
{
	u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)){
		res=USART_ReceiveData(USART1);
		USART_SendData(USART1,res);
	}
}
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	My_USART1_Init();
	while(1)
	{
		
	}
	
}
