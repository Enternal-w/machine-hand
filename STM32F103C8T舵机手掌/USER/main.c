/******************************************************************************************************************************************

							TIM1_ETR     PA12            
							TIM1_CH1     PA8            TIM2_CH1_ETR PA0            TIM3_CH1     PA6            TIM4_CH1     PB6 
							TIM1_CH2     PA9            TIM2_CH2     PA1            TIM3_CH2     PA7            TIM4_CH2     PB7
							TIM1_CH3     PA10           TIM2_CH3     PA2            TIM3_CH3     PB0            TIM4_CH3     PB8 
							TIM1_CH4     PA11           TIM2_CH4     PA3            TIM3_CH4     PB1            TIM4_CH4     PB9  
							

                
							高电平时间T1为 1.5ms     舵机转动90°    相对位置为     0°    参数为1850  
								
								           相对而言：高电平时间T1为 0.5ms     舵机转动0°     相对位置为   -90°    参数为1945  
                                     高电平时间T1为   1ms     舵机转动45°    相对位置为   -45°    参数为1900  
																		 高电平时间T1为 1.5ms     舵机转动90°    相对位置为     0°    参数为1850  
                                     高电平时间T1为   2ms     舵机转动135°   相对位置为   +45°    参数为1800  
																		 高电平时间T1为 2.5ms     舵机转动180°   相对位置为   +90°    参数为1750  
																		 
																		 
		//-90°
		//TIM_SetCompare1(TIM4,1945);//占空比(2000-1945)/2000*20ms=0.5ms 
		
		//-45°
		//TIM_SetCompare1(TIM4,1900);//占空比(2000-1900)/2000*20ms=1ms
		
		//0°
		//TIM_SetCompare1(TIM4,1850);//占空比(2000-1850)/2000*20ms=1.5ms
		
		//+45°
		//TIM_SetCompare1(TIM4,1800);//占空比(2000-1800)/2000*20ms=2ms
		
		//+90°
		//TIM_SetCompare1(TIM4,1750);//占空比(2000-1750)/2000*20ms=2.5ms

*****************************************************************************************************************************************************************************/
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "pwm.h"
#include "pwm1.h"
#include "pwm2.h"
#include "pwm3.h"
#include "usart.h"	
#include "oled.h"

 int main(void)
 {	
//	u8 t=0;	  
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	 	//初始化与LED连接的硬件接口
	KEY_Init();          	//初始化与按键连接的硬件接口
	uart_init(115200);
	 NVIC_Configuration();	 
	OLED_Init();
  TIM2_PWM_Init(1999,719);     //PWM频率=72000000/（719+1）/（1999+1）=50hz=20ms	
  TIM3_PWM_Init(1999,719); 
   
	 
	LED0=0;					//点亮LED
	while(1)
	{

	}		 
}

