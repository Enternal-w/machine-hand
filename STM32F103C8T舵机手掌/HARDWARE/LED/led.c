#include "led.h"
#include "delay.h"


//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//ʹ��ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	 
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				       //PC13 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					         //�����趨������ʼ��GPIOPC13
 GPIO_SetBits(GPIOC,GPIO_Pin_13);						             //PC13�����

}
 

/**************************************************************************
�����������ȼ������1��     �� -- �� 
��ڲ�������
����ֵ����
 *************************************************************************/
void LED_Blink_1()
{   
	  GPIO_SetBits(GPIOC,GPIO_Pin_13);     //LED�����
		delay_ms(100);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);   //LED�����
		delay_ms(100);	
	  
	
}


/**************************************************************************
�����������ȼ������2��    �� -- �� -- �� --��
��ڲ�������
����ֵ����
 *************************************************************************/
void LED_Blink_2()
{   
	  GPIO_SetBits(GPIOC,GPIO_Pin_13);     //LED�����
		delay_ms(200);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);   //LED�����
		delay_ms(100);	
	  GPIO_SetBits(GPIOC,GPIO_Pin_13);     //LED�����
		delay_ms(200);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);   //LED�����
		delay_ms(100);
	 
	
}

/**************************************************************************
�����������ȼ������3��   �� -- �� -- �� --��
��ڲ�������
����ֵ����
 *************************************************************************/
void LED_Blink_3()
{   
	  GPIO_SetBits(GPIOC,GPIO_Pin_13);     //LED�����
		delay_ms(300);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);   //LED�����
		delay_ms(100);	
	  GPIO_SetBits(GPIOC,GPIO_Pin_13);     //LED�����
		delay_ms(300);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);   //LED�����
		delay_ms(100);
	  GPIO_SetBits(GPIOC,GPIO_Pin_13);     //LED�����
		delay_ms(300);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);   //LED�����
		delay_ms(100);
	
}

/**************************************************************************
�����������ȼ������3��   �� -- �� -- �� --��-- �� --��
��ڲ�������
����ֵ����
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
