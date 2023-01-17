#include "AM2301.h"
#include "delay.h"

 //////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//AM2301数字温湿度传感器驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/12
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
      
//复位AM2301
void AM2301_Rst(void)	   
{                 
	AM2301_IO_OUT(); 	//SET OUTPUT
    AM2301_DQ_OUT=0; 	//拉低DQ
    delay_us(1000);  delay_us(1000);  	//拉低至少18ms
    AM2301_DQ_OUT=1; 	//DQ=1 
	delay_us(30);     	//主机拉高20~40us
}
//等待AM2301的回应
//返回1:未检测到AM2301的存在
//返回0:存在
u8 AM2301_Check(void) 	   
{   
	u8 retry=0;
	AM2301_IO_IN();//SET INPUT	 
    while (AM2301_DQ_IN&&retry<100)//AM2301会拉低40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!AM2301_DQ_IN&&retry<100)//AM2301拉低后会再次拉高40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
//从AM2301读取一个位
//返回值：1/0
u8 AM2301_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(AM2301_DQ_IN&&retry<100)//等待变为低电平
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!AM2301_DQ_IN&&retry<100)//等待变高电平
	{
		retry++;
		delay_us(1);
	}
	delay_us(30);//等待40us
	if(AM2301_DQ_IN)return 1;
	else return 0;		   
}
//从AM2301读取一个字节
//返回值：读到的数据
u8 AM2301_Read_Byte(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=AM2301_Read_Bit();
    }						    
    return dat;
}
//从AM2301读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
u16 AM2301_Read_Data(u16 *temp,u16 *temp2,u16 *humi,u16 *humi2)      
{
 	u8 buf[5];
	u8 i;
	AM2301_Rst();
	if(AM2301_Check()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=AM2301_Read_Byte();
		}
		if((u8)(buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			
			*humi=(buf[0]*256+buf[1]);
		//	*humi2=buf[1];
			if(buf[2]&0x80)
			*temp=-(buf[2]*256+buf[3]-32768);
			else
			*temp=(buf[2]*256+buf[3]);
		}
	}else return 1;
	return 0;	    
}

//初始化AM2301的IO口 DQ 同时检测AM2301的存在
//返回1:不存在
//返回0:存在    	 
u8 AM2301_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	 //使能PG端口时钟
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 //PG11端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure);				 //初始化IO口
 	GPIO_SetBits(GPIOG,GPIO_Pin_11);						 //PG11 输出高
			    
	AM2301_Rst();  //复位AM2301
	return AM2301_Check();//等待AM2301的回应
} 















