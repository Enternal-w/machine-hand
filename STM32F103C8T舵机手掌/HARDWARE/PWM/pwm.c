#include "pwm.h"

//TIM4 PWM²¿·Ö³õÊ¼»
//PWMÊä³ö³õÊ¼»¯
//arr:×Ô¶¯ÖØ×°ÔØÖµ        psc:Ê±ÖÓÔ¤·ÖÆµÊı


/******************************************************************************

					
//TIM3²¿·ÖÖØÓ³Éä
	
	*²é¿´Êı¾İÊÖ²á£¬Òı½ÅµÄ¶¨Ê±Æ÷Í¨µÀÊÇÍêÈ«Ó³Éä£¬»¹ÊÇ²¿·ÖÓ³Éä
	*¶şÕßµ÷ÓÃ²ÎÊı²»ÏàÍ¬
	*ÍêÈ«Ó³Éä £ºGPIO_FullRemap_TIM4
	*²¿·ÖÓ³Éä £ºGPIO_PartialRemap_TIM4
	*
   
	//ÉèÖÃTIM4_CH1ÖØÓ³Éäµ½PB6ÉÏ
  //GPIO_PinRemapConfig(GPIO_PartialRemap_TIM4,ENABLE);
*******************************************************************************/


void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;   					 				//³õÊ¼»¯TIM4ÉèÖÃARR,PSC¿ØÖÆÊä³öPWMµÄÖÜÆÚ
	TIM_OCInitTypeDef  TIM_OCInitStructure;                         //PWMÍ¨µÀÉèÖÃ
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);     			  //Ê¹ÄÜ¶¨Ê±Æ÷4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);      				//AFIO¸´ÓÃ¹¦ÄÜÊ±ÖÓÊ¹ÄÜ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE);   				//GPIOBÊ¹ÄÜ
	
	
	//ÉèÖÃ¸ÃÒı½ÅÎª¸´ÓÃÊä³ö¹¦ÄÜ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;	       //TIM4_CH1/CH2/CH3/CH4
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                                   //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);                                             //³õÊ¼»¯GPIO
	
	
	//³õÊ¼»¯TIM4,ÉèÖÃTIM4µÄARRºÍPSC
	TIM_TimeBaseStruct.TIM_Period = arr;                   					 //ÉèÖÃ×Ô¶¯ÖØ×°ÔØÖÜÆÚÖµ   //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	 
	TIM_TimeBaseStruct.TIM_Prescaler = psc;                					 //ÉèÖÃÔ¤·ÖÆµÖµ           //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ  ²»·ÖÆµ
	TIM_TimeBaseStruct.TIM_ClockDivision = 0;               				 //ÉèÖÃÊ±ÖÓ·Ö¸îTDTS = Tck_tim	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;         //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);                      //¸ù¾İÖ¸¶¨²ÎÊı³õÊ¼»¯TIMx  //¸ù¾İTIM_TimeBaseInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
	
	
	
	
	//Êä³ö³õÊ¼»¯º¯Êı£¬Ñ¡ÔñËÄ¸öÍ¨µÀ£¬³õÊ¼»¯PWMÊä³öÄ£Ê½¡¢±È½ÏÊä³ö¼«ĞÔ¡¢ ±È½ÏÊä³öÊ¹ÄÜ¡¢ ±È½ÏÖµCCRxµÄÖµ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                  //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_Pulse = 0;                                 //ÉèÖÃ´ı×°Èë²¶»ñ±È½Ï¼Ä´æÆ÷µÄÂö³åÖµ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;          //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	
	TIM_OC1Init(TIM4,&TIM_OCInitStructure);                            //¸ù¾İTIMXµÄ²ÎÊıÉè¶¨³õÊ¼»¯ÍâÉè TIM1 ch1 ch2 ch3 ch4	
	TIM_OC2Init(TIM4,&TIM_OCInitStructure);
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
  TIM_OC4Init(TIM4,&TIM_OCInitStructure);

	
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);  //Ê¹ÄÜÔ¤×°ÔØ¼Ä´æÆ÷
  TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //Ê¹ÄÜTIMxÔÚARRÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷	
	
	TIM_Cmd(TIM4,ENABLE);     //Ê¹ÄÜTIM4
	
	
	//²ÎÊıÉèÖÃº¯Êı
	//×÷ÓÃ£ºÔÚËÄ¸öÍ¨µÀÖĞÑ¡ÔñÒ»¸ö£¬ÉèÖÃ±È½ÏÖµ¡£Í¨³£ÔÚ³õÊ¼»¯º¯ÊıÖĞÒÑ¾­ÉèÖÃÁË±È½ÏÖµ£¬´Ëº¯ÊıÓÃÓÚ³ı³õÊ¼»¯Ö®ÍâµÄĞŞ¸Ä
	//TIM_SetCompare1(TIM4,1850);
	//TIM_SetCompare2(TIM4,1850);
	//TIM_SetCompare3(TIM4,1850);
	//TIM_SetCompare4(TIM4,1850);
	
	

}








