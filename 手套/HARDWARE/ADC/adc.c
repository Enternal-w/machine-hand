 #include "adc.h"
 #include "delay.h"

	   
//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3		
volatile uint16_t ADC_ConvertedValue[5]={0,0,0,0,0};
u16 Total1;
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1|	RCC_APB2Periph_GPIOC, ENABLE );	  //使能ADC1通道时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	DMA_DeInit(DMA1_Channel1);   //将DMA的通道1寄存器重设为1缺省值

	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;  //DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //数据传输方向，从外设读取发送到内存
	DMA_InitStructure.DMA_BufferSize = 5;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器增量
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //工作在循环模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有高优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
	
	DMA_Cmd(DMA1_Channel1, ENABLE);	//使能DMA通道 
	
	ADC_DeInit(ADC1);  //复位ADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//模数转换工作在连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 5;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);//配置ADC1通道0为55.5个采样周期 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 2, ADC_SampleTime_55Cycles5);//配置ADC1通道0为55.5个采样周期 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 3, ADC_SampleTime_55Cycles5);//配置ADC1通道0为55.5个采样周期 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 4, ADC_SampleTime_55Cycles5);//配置ADC1通道0为55.5个采样周期 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 5, ADC_SampleTime_55Cycles5);//配置ADC1通道0为55.5个采样周期 
	
  ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  
//获得ADC值
//ch:通道值 0~3
/*u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 	 */
u16 Get_Adc(u8 ch)   
{
  if(ch==1)return ADC_ConvertedValue[0];
	else if(ch==10)return ADC_ConvertedValue[1];
	else if(ch==11)return ADC_ConvertedValue[2];
	else if(ch==12)return ADC_ConvertedValue[3];
	else if(ch==13)return ADC_ConvertedValue[4];
	else return 0;
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
//	u32 temp_val=0;
	u8 i,j;
	u32 temp_t,temp_buf[25],temp_sum=0;
	for(i=0;i<times;i++)
	{
		temp_buf[i]=Get_Adc(ch);
		delay_ms(5);
	}
	for(i=0;i<times-1;i++)
		for(j=0;j<times-1;j++)
		{
			temp_t=temp_buf[j];
			temp_buf[j]=temp_buf[j+1];
			temp_buf[j+1]=temp_t;
		}
	for(i=5;i<times-5;i++)temp_sum+=temp_buf[i];
	return temp_sum/(times-10);
}



























