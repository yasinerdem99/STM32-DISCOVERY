#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#define BufferLength 2

uint16_t adc_value[BufferLength]={0,0};

uint16_t adc_value1;
uint16_t adc_value2;

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonStruct;
DMA_InitTypeDef DMA_InitStruct;


void GPIO_Config(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void ADC_Config(){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

	ADC_CommonStruct.ADC_Mode=ADC_Mode_Independent;
	ADC_CommonStruct.ADC_Prescaler=ADC_Prescaler_Div4;
	ADC_CommonStruct.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;
	ADC_CommonStruct.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_20Cycles;

	ADC_CommonInit(&ADC_CommonStruct);

	ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode=ENABLE;
	ADC_InitStruct.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_ExternalTrigConv=0;
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ContinuousConvMode=ENABLE;
	ADC_InitStruct.ADC_NbrOfConversion=BufferLength;

	ADC_Init(ADC1,&ADC_InitStruct);

	ADC_Cmd(ADC1,ENABLE);

	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_3Cycles);

	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);


	ADC_DMACmd(ADC1,ENABLE);


}

void DMA_Config(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

	DMA_InitStruct.DMA_BufferSize=BufferLength;
	DMA_InitStruct.DMA_Channel=DMA_Channel_0;
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralToMemory;
	DMA_InitStruct.DMA_FIFOMode=DMA_FIFOMode_Enable;
	DMA_InitStruct.DMA_FIFOThreshold=DMA_FIFOThreshold_HalfFull;
	DMA_InitStruct.DMA_Memory0BaseAddr=(uint32_t)&adc_value;
	DMA_InitStruct.DMA_MemoryBurst=DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&ADC1->DR;
	DMA_InitStruct.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority=DMA_Priority_VeryHigh;



	DMA_Init(DMA2_Stream0,&DMA_InitStruct);
	DMA_Cmd(DMA2_Stream0,ENABLE);



}

int main(void)
{
	GPIO_Config();
	ADC_Config();
	DMA_Config();

	ADC_SoftwareStartConv(ADC1);
  while (1)
  {
	  adc_value1=adc_value[0];
	  adc_value2=adc_value[1];

  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){

  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){

  return -1;
}
