/*****************************************************************************************************************************************************														

	A8  A9  A10  A11
*******************************************************************************/

#include "pwm1.h"

//TIM4 PWM���ֳ�ʼ�
//PWM�����ʼ��
//arr:�Զ���װ��ֵ        psc:ʱ��Ԥ��Ƶ��


void TIM1_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;   					 				//��ʼ��TIM1����ARR,PSC�������PWM������
	TIM_OCInitTypeDef  TIM_OCInitStructure;                         //PWMͨ������
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);     			  //ʹ�ܶ�ʱ��4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);      				//AFIO���ù���ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  ,ENABLE);   				//GPIOAʹ��
	
	
	//���ø�����Ϊ�����������    GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;                                       //�˴�ֻ��PA11���ţ���TIM1_CH4 ͨ��
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                                     //�����������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);                                               //��ʼ��GPIO
	
	
	//��ʼ��TIM1,����TIM4��ARR��PSC
	TIM_TimeBaseStruct.TIM_Period = arr;                   					 //�����Զ���װ������ֵ   //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 
	TIM_TimeBaseStruct.TIM_Prescaler = psc;                					 //����Ԥ��Ƶֵ           //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStruct.TIM_ClockDivision = 0;               				 //����ʱ�ӷָ�TDTS = Tck_tim	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;         //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStruct);                      //����ָ��������ʼ��TIMx  //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	


	
	//��ʼ��������Ƚϲ���
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                  //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;          //�������:TIM����Ƚϼ��Ը�
	
  TIM_OC1Init(TIM1,&TIM_OCInitStructure);                          //����TIMX�Ĳ����趨��ʼ������ TIM1 ch1 ch2 ch3 ch4	
  TIM_OC2Init(TIM1,&TIM_OCInitStructure);
  TIM_OC3Init(TIM1,&TIM_OCInitStructure);
  TIM_OC4Init(TIM1,&TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);                 //ʹ��Ԥװ�ؼĴ���
  TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM1, ENABLE);                                //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���	
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);                                   //TIM1���ʹ��   �߼���ʱ�����Եü�����Ϊ��仰�Ҹ���һ�����ϣ����˽�֮��֮
	
	TIM_Cmd(TIM1,ENABLE);     //ʹ��TIM1
	
	
	//�������ú���
	//���ã����ĸ�ͨ����ѡ��һ�������ñȽ�ֵ��ͨ���ڳ�ʼ���������Ѿ������˱Ƚ�ֵ���˺������ڳ���ʼ��֮����޸�
  //TIM_SetCompare1(TIM1,1850);
	//TIM_SetCompare2(TIM1,1850);
	//TIM_SetCompare3(TIM1,1850);
	//TIM_SetCompare4(TIM1,1850);
	
	

}



