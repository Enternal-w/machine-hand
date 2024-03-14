//#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "adc.h"
 
/************************************************
PA0   PC0 1 2 3
************************************************/
extern __IO uint16_t ADC_ConvertedValue; 
float ADC_ConvertedValueLocal1,ADC_ConvertedValueLocal2,ADC_ConvertedValueLocal3,ADC_ConvertedValueLocal4,ADC_ConvertedValueLocal5; 
 
 int main(void)
 {
	u16 adcx1,adcx2,adcx3,adcx4,adcx5;	
  u8 flag;	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200	 	
 	Adc_Init();		  		//ADC��ʼ��

	 
	while(1)
	{
		adcx1=Get_Adc_Average(1,25);//��ʾADC��ֵ
		ADC_ConvertedValueLocal1 =(float)adcx1*(3.3/4095);//��ʾ��ѹֵ

		
		adcx2=Get_Adc_Average(10,25);
		ADC_ConvertedValueLocal2 =(float)adcx2*(3.3/4095);

		
		adcx3=Get_Adc_Average(11,25);
		ADC_ConvertedValueLocal3 =(float)adcx3*(3.3/4095);

		
		adcx4=Get_Adc_Average(12,25);
		ADC_ConvertedValueLocal4 =(float)adcx4*(3.3/4095);
		
		adcx5=Get_Adc_Average(13,25);
		ADC_ConvertedValueLocal5 =(float)adcx5*(3.3/4095);
	
//	  printf("���AD1ֵΪ��%d\r\n",adcx1);
//	  printf("���AD2ֵΪ��%d\r\n",adcx2);
//	  printf("���AD3ֵΪ��%d\r\n",adcx3);
//	  printf("���AD4ֵΪ��%d\r\n",adcx4);
//	  printf("���AD5ֵΪ��%d\r\n",adcx5);	
		if(adcx1<1500)
    {
		 printf("a\r\n");
		 flag=1;
		}
		else if((flag==1)&&(adcx1>1900))
    {
		 printf("A\r\n");
		 flag=0;
		}
		
		if(adcx2<1500)
    {
		 printf("b\r\n");
		 flag=2;
		}
		else if((flag==2)&&(adcx2>1900))
    {
		 printf("B\r\n");
		 flag=0;
		}	
		
		if(adcx3<1500)
    {
		 printf("c\r\n");
		 flag=3;
		}
		else if((flag==3)&&(adcx3>1900))
    {
		printf("C\r\n");
		flag=0;
		}
		
		if(adcx4<1500)
    {
		 printf("d\r\n");
		 flag=4;
		}
		else if((flag==4)&&(adcx4>1900))
    {
		printf("D\r\n");
		flag=0;
		}
		
		if(adcx5<1500) 
    {
		 printf("e\r\n");
		 flag=5;
		}
		else if((flag==5)&&(adcx5>1900))
    {
		printf("E\r\n");
		flag=0;
		}		


	}
 }


 



 