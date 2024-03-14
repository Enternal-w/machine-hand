#include "led.h"
#include "delay.h"


//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//使能时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	 
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PC端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				       //PC13 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					         //根据设定参数初始化GPIOPC13
 GPIO_SetBits(GPIOC,GPIO_Pin_13);						             //PC13输出高

}
 

/**************************************************************************
功能描述：等间隔亮灭1次     亮 -- 灭 
入口参数：无
返回值：无
 *************************************************************************/
void LED_Blink_1()
{   
	  GPIO_SetBits(GPIOC,GPIO_Pin_13);     //LED输出高
		delay_ms(100);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);   //LED输出低
		delay_ms(100);	
	  
	
}


/**************************************************************************
功能描述：等间隔亮灭2次    亮 -- 灭 -- 亮 --灭
入口参数：无
返回值：无
 *************************************************************************/
void LED_Blink_2()
{   
	  GPIO_SetBits(GPIOC,GPIO_Pin_13);     //LED输出高
		delay_ms(200);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);   //LED输出低
		delay_ms(100);	
	  GPIO_SetBits(GPIOC,GPIO_Pin_13);     //LED输出高
		delay_ms(200);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);   //LED输出低
		delay_ms(100);
	 
	
}

/**************************************************************************
功能描述：等间隔亮灭3次   亮 -- 灭 -- 亮 --灭
入口参数：无
返回值：无
 *************************************************************************/
void LED_Blink_3()
{   
	  GPIO_SetBits(GPIOC,GPIO_Pin_13);     //LED输出高
		delay_ms(300);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);   //LED输出低
		delay_ms(100);	
	  GPIO_SetBits(GPIOC,GPIO_Pin_13);     //LED输出高
		delay_ms(300);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);   //LED输出低
		delay_ms(100);
	  GPIO_SetBits(GPIOC,GPIO_Pin_13);     //LED输出高
		delay_ms(300);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);   //LED输出低
		delay_ms(100);
	
}

/**************************************************************************
功能描述：等间隔亮灭3次   亮 -- 灭 -- 亮 --灭-- 亮 --灭
入口参数：无
返回值：无
 *************************************************************************/
void LED_Blink_4()
{   
	  LED_Blink_2();
	  LED_Blink_2();
	
}

void LED_Blink_5()
{   
	  LED_Blink_2();
	  LED_Blink_3();
	
}
/*********************************END FILE********************************************/	
