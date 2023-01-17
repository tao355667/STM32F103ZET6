#ifndef __AM2301_H
#define __AM2301_H 
#include "sys.h"   
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
 
//IO方向设置
#define AM2301_IO_IN()  {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=8<<12;}
#define AM2301_IO_OUT() {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=3<<12;}
////IO操作函数											   
#define	AM2301_DQ_OUT PGout(11) //数据端口	PA0 
#define	AM2301_DQ_IN  PGin(11)  //数据端口	PA0 


u8 AM2301_Init(void);//初始化AM2301
u16 AM2301_Read_Data(u16 *temp,u16 *temp2,u16 *humi,u16 *humi2) ; //读取温湿度
u8 AM2301_Read_Byte(void);//读出一个字节
u8 AM2301_Read_Bit(void);//读出一个位
u8 AM2301_Check(void);//检测是否存在AM2301
void AM2301_Rst(void);//复位AM2301    
#endif

















