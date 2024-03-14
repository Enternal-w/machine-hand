


#include "pwm3.h"

//TIM4 PWM²¿·Ö³õÊ¼»
//PWMÊä³ö³õÊ¼»¯
//arr:×Ô¶¯ÖØ×°ÔØÖµ        psc:Ê±ÖÓÔ¤·ÖÆµÊı
void TIM3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;   					 				//³õÊ¼»¯TIM1ÉèÖÃARR,PSC¿ØÖÆÊä³öPWMµÄÖÜÆÚ
	TIM_OCInitTypeDef  TIM_OCInitStructure;                         //PWMÍ¨µÀÉèÖÃ
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);     			  //Ê¹ÄÜ¶¨Ê±Æ÷4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);      				//AFIO¸´ÓÃ¹¦ÄÜÊ±ÖÓÊ¹ÄÜ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB ,ENABLE);   				//GPIOA¡¢BÊ¹ÄÜ
	
	
	//ÉèÖÃ¸ÃÒı½ÅÎª¸´ÓÃÊä³ö¹¦ÄÜ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	       //TIM1_CH1/CH2
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                                     //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);                                               //³õÊ¼»¯GPIO
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	       //TIM3_CH3/CH4
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                                     //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);                                               //³õÊ¼»¯GPIO
	
	
	//³õÊ¼»¯TIM1,ÉèÖÃTIM4µÄARRºÍPSC
	TIM_TimeBaseStruct.TIM_Period = arr;                   					 //ÉèÖÃ×Ô¶¯ÖØ×°ÔØÖÜÆÚÖµ   //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	 
	TIM_TimeBaseStruct.TIM_Prescaler = psc;                					 //ÉèÖÃÔ¤·ÖÆµÖµ           //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ  ²»·ÖÆµ
	TIM_TimeBaseStruct.TIM_ClockDivision = 0;               				 //ÉèÖÃÊ±ÖÓ·Ö¸îTDTS = Tck_tim	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;         //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);                      //¸ù¾İÖ¸¶¨²ÎÊı³õÊ¼»¯TIMx  //¸ù¾İTIM_TimeBaseInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
	


	
	//³õÊ¼»¯³öÊä³ö±È½Ï²ÎÊı
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                  //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;          //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);                            //¸ù¾İTIMXµÄ²ÎÊıÉè¶¨³õÊ¼»¯ÍâÉè TIM1 ch1 ch2 ch3 ch4	
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
  TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);                   //Ê¹ÄÜÔ¤×°ÔØ¼Ä´æÆ÷
  TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);                                 //Ê¹ÄÜTIMxÔÚARRÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷	
	
	TIM_CtrlPWMOutputs(TIM3,ENABLE);//TIM1Êä³öÊ¹ÄÜ   ¸ß¼¶¶¨Ê±Æ÷¾ø¶ÔµÃ¼ÓÉÏÒòÎªÕâ¾ä»°ÎÒ¸ãÁËÒ»¸öÍíÉÏ£¬ºóÈË½äÖ®É÷Ö®
	
	TIM_Cmd(TIM3,ENABLE);     //Ê¹ÄÜTIM1
	
	
	//²ÎÊıÉèÖÃº¯Êı
	//×÷ÓÃ£ºÔÚËÄ¸öÍ¨µÀÖĞÑ¡ÔñÒ»¸ö£¬ÉèÖÃ±È½ÏÖµ¡£Í¨³£ÔÚ³õÊ¼»¯º¯ÊıÖĞÒÑ¾­ÉèÖÃÁË±È½ÏÖµ£¬´Ëº¯ÊıÓÃÓÚ³ı³õÊ¼»¯Ö®ÍâµÄĞŞ¸Ä
  //TIM_SetCompare1(TIM3,1850);
	//TIM_SetCompare2(TIM3,1850);
	//TIM_SetCompare3(TIM3,1850);
	//TIM_SetCompare4(TIM3,1850);
	
	

}



