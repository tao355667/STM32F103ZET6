#include "AM2301.h"
#include "delay.h"

 //////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//AM2301������ʪ�ȴ�������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/12
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
      
//��λAM2301
void AM2301_Rst(void)	   
{                 
	AM2301_IO_OUT(); 	//SET OUTPUT
    AM2301_DQ_OUT=0; 	//����DQ
    delay_us(1000);  delay_us(1000);  	//��������18ms
    AM2301_DQ_OUT=1; 	//DQ=1 
	delay_us(30);     	//��������20~40us
}
//�ȴ�AM2301�Ļ�Ӧ
//����1:δ��⵽AM2301�Ĵ���
//����0:����
u8 AM2301_Check(void) 	   
{   
	u8 retry=0;
	AM2301_IO_IN();//SET INPUT	 
    while (AM2301_DQ_IN&&retry<100)//AM2301������40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!AM2301_DQ_IN&&retry<100)//AM2301���ͺ���ٴ�����40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
//��AM2301��ȡһ��λ
//����ֵ��1/0
u8 AM2301_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(AM2301_DQ_IN&&retry<100)//�ȴ���Ϊ�͵�ƽ
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!AM2301_DQ_IN&&retry<100)//�ȴ���ߵ�ƽ
	{
		retry++;
		delay_us(1);
	}
	delay_us(30);//�ȴ�40us
	if(AM2301_DQ_IN)return 1;
	else return 0;		   
}
//��AM2301��ȡһ���ֽ�
//����ֵ������������
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
//��AM2301��ȡһ������
//temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��
u16 AM2301_Read_Data(u16 *temp,u16 *temp2,u16 *humi,u16 *humi2)      
{
 	u8 buf[5];
	u8 i;
	AM2301_Rst();
	if(AM2301_Check()==0)
	{
		for(i=0;i<5;i++)//��ȡ40λ����
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

//��ʼ��AM2301��IO�� DQ ͬʱ���AM2301�Ĵ���
//����1:������
//����0:����    	 
u8 AM2301_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	 //ʹ��PG�˿�ʱ��
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 //PG11�˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure);				 //��ʼ��IO��
 	GPIO_SetBits(GPIOG,GPIO_Pin_11);						 //PG11 �����
			    
	AM2301_Rst();  //��λAM2301
	return AM2301_Check();//�ȴ�AM2301�Ļ�Ӧ
} 















