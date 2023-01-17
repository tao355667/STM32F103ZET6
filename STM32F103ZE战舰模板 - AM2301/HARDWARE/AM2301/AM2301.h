#ifndef __AM2301_H
#define __AM2301_H 
#include "sys.h"   
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
 
//IO��������
#define AM2301_IO_IN()  {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=8<<12;}
#define AM2301_IO_OUT() {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=3<<12;}
////IO��������											   
#define	AM2301_DQ_OUT PGout(11) //���ݶ˿�	PA0 
#define	AM2301_DQ_IN  PGin(11)  //���ݶ˿�	PA0 


u8 AM2301_Init(void);//��ʼ��AM2301
u16 AM2301_Read_Data(u16 *temp,u16 *temp2,u16 *humi,u16 *humi2) ; //��ȡ��ʪ��
u8 AM2301_Read_Byte(void);//����һ���ֽ�
u8 AM2301_Read_Bit(void);//����һ��λ
u8 AM2301_Check(void);//����Ƿ����AM2301
void AM2301_Rst(void);//��λAM2301    
#endif

















