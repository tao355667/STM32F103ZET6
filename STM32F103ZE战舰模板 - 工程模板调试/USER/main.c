#include "delay.h"
#include "usart.h"




int main(void)
{
	u8 t=0;
	delay_init(); //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	uart_init(115200); //串口初始化为115200
while(1)
{ 
	printf("t:%d\n",t);
	 delay_ms(500); 
	t++;
}
}
