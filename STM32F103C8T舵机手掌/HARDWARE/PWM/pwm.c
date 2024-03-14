#include "pwm.h"

//TIM4 PWM���ֳ�ʼ�
//PWM�����ʼ��
//arr:�Զ���װ��ֵ        psc:ʱ��Ԥ��Ƶ��


/******************************************************************************

					
//TIM3������ӳ��
	
	*�鿴�����ֲᣬ���ŵĶ�ʱ��ͨ������ȫӳ�䣬���ǲ���ӳ��
	*���ߵ��ò�������ͬ
	*��ȫӳ�� ��GPIO_FullRemap_TIM4
	*����ӳ�� ��GPIO_PartialRemap_TIM4
	*
   
	//����TIM4_CH1��ӳ�䵽PB6��
  //GPIO_PinRemapConfig(GPIO_PartialRemap_TIM4,ENABLE);
*******************************************************************************/


void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;   					 				//��ʼ��TIM4����ARR,PSC�������PWM������
	TIM_OCInitTypeDef  TIM_OCInitStructure;                         //PWMͨ������
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);     			  //ʹ�ܶ�ʱ��4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);      				//AFIO���ù���ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE);   				//GPIOBʹ��
	
	
	//���ø�����Ϊ�����������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;	       //TIM4_CH1/CH2/CH3/CH4
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                                   //�����������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);                                             //��ʼ��GPIO
	
	
	//��ʼ��TIM4,����TIM4��ARR��PSC
	TIM_TimeBaseStruct.TIM_Period = arr;                   					 //�����Զ���װ������ֵ   //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 
	TIM_TimeBaseStruct.TIM_Prescaler = psc;                					 //����Ԥ��Ƶֵ           //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStruct.TIM_ClockDivision = 0;               				 //����ʱ�ӷָ�TDTS = Tck_tim	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;         //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);                      //����ָ��������ʼ��TIMx  //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	
	
	
	//�����ʼ��������ѡ���ĸ�ͨ������ʼ��PWM���ģʽ���Ƚ�������ԡ� �Ƚ����ʹ�ܡ� �Ƚ�ֵCCRx��ֵ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                  //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0;                                 //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;          //�������:TIM����Ƚϼ��Ը�
	
	TIM_OC1Init(TIM4,&TIM_OCInitStructure);                            //����TIMX�Ĳ����趨��ʼ������ TIM1 ch1 ch2 ch3 ch4	
	TIM_OC2Init(TIM4,&TIM_OCInitStructure);
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
  TIM_OC4Init(TIM4,&TIM_OCInitStructure);

	
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);  //ʹ��Ԥװ�ؼĴ���
  TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���	
	
	TIM_Cmd(TIM4,ENABLE);     //ʹ��TIM4
	
	
	//�������ú���
	//���ã����ĸ�ͨ����ѡ��һ�������ñȽ�ֵ��ͨ���ڳ�ʼ���������Ѿ������˱Ƚ�ֵ���˺������ڳ���ʼ��֮����޸�
	//TIM_SetCompare1(TIM4,1850);
	//TIM_SetCompare2(TIM4,1850);
	//TIM_SetCompare3(TIM4,1850);
	//TIM_SetCompare4(TIM4,1850);
	
	

}








