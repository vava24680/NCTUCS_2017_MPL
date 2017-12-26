#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_
#include "../inc/ADC.h"
#endif
/*
---------------------------------------------
|	UART GPIO Pin Explanation				|
---------------------------------------------
|	GPIO Module	|	Pin	|	Function		|
|	GPIOB		|	1	|	ADC_Analog_In	|
---------------------------------------------
*/
void ADC_GPIO_Init(GPIO_TypeDef* GPIOx)
{
	TM_GPIO_Init(GPIOx, ADC_Analog_In, TM_GPIO_Mode_AN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
	/*Connect this port to ADC*/
	ADC_GPIO_ASCR_Control(GPIOx, ADC_Analog_In, GPIO_ASCR_CONNECT);
}
void ADC_GPIO_ASCR_Control(GPIO_TypeDef* GPIOx, uint32_t Pin, EN_GPIO_ASCR GPIO_ASCR)
{
	GPIOx->ASCR = GPIOx->ASCR & (~(1U << Pin));
	GPIOx->ASCR = GPIOx->ASCR | (GPIO_ASCR_CONNECT << Pin);
}
void ADC_Clock_Control(EN_ADC_CLOCK_CONTROL ADC_CLOCK_CONTROL)
{
	RCC->AHB2ENR = RCC->AHB2ENR & (~RCC_AHB2ENR_ADCEN_Msk);
	RCC->AHB2ENR |= (ADC_CLOCK_CONTROL << RCC_AHB2ENR_ADCEN_Pos);
	ADC123_COMMON->CCR |= ADC_CCR_CKMODE_0;
}
void ADC_Init(ADC_TypeDef* ADCx)
{
	ADCx->CR &= (~ADC_CR_DEEPPWD_Msk);//Exit Deep-Power-Mode
	ADCx->CR |= (ADC_DEEPPWD_DISABLE << ADC_CR_DEEPPWD_Pos);
	ADCx->CR &= (~ADC_CR_ADVREGEN_Msk);
	ADCx->CR |= (ADC_ADVRED_ENABLE << ADC_CR_ADVREGEN_Pos);
	delay_us(1000);
}
void ADC_EOC_Interrupt_Control(ADC_TypeDef* ADCx, EN_ADC_EOC_INTERRUPT_CONTROL ADC_EOC_Interrupt_Option)
{
	ADCx->IER &= (~ADC_IER_EOCIE_Msk);
	ADCx->IER |= (ADC_EOC_Interrupt_Option << ADC_IER_EOCIE_Pos);
}
uint32_t ADC_Calibration(ADC_TypeDef* ADCx, EN_ADC_INPUT_MODE ADC_Input_Mode)
{
	ADCx->CR &= (~ADC_CR_ADCALDIF_Msk);
	if(ADC_Input_Mode == ADC_DIFFERENTIAL_MODE)
		ADCx->CR |= (ADC_DIFFERENTIAL_MODE << ADC_CR_ADCALDIF_Pos);
	ADCx->CR &= (~ADC_CR_ADCAL_Msk);
	ADCx->CR |= (1U << ADC_CR_ADCAL_Pos);
	while(ADCx->CR & 0x80000000U);
	return (ADCx->CALFACT & 0x7FU);
}
void ADC_ConvertionMode_Setting(ADC_TypeDef* ADCx, EN_ADC_CONVERSION_MODE ADC_ConversionMode)
{
	ADCx->CFGR &= (~ADC_CFGR_CONT_Msk);
	ADCx->CFGR |= (ADC_ConversionMode << ADC_CFGR_CONT_Pos);
}
void ADC_Data_Align_Setting(ADC_TypeDef* ADCx, EN_ADC_DATA_ALIGN ADC_Data_Align)
{
	ADCx->CFGR &= (~ADC_CFGR_ALIGN_Msk);
	ADCx->CFGR |= (ADC_Data_Align << ADC_CFGR_ALIGN_Pos);
}
void ADC_Resolution_Setting(ADC_TypeDef* ADCx, EN_ADC_RESOLUTION ADC_Resolution)
{
	ADCx->CFGR &= (~ADC_CFGR_RES_Msk);
	ADCx->CFGR |= (ADC_Resolution << ADC_CFGR_RES_Pos);
}
void ADC_Regular_SequenceLength_Setting(ADC_TypeDef* ADCx, EN_ADC_Regular_Sequence_Length ADC_Regular_SequenceLength,const uint8_t Channel_list[])
{
	ADCx->SQR1 &= (~ADC_SQR1_L_Msk);
	ADCx->SQR1 |= (ADC_Regular_SequenceLength << ADC_SQR1_L_Pos);
	ADCx->SQR1 &= (~(0xFFFFFFF0U));
	ADCx->SQR2 &= (~(0xFFFFFFFFU));
	ADCx->SQR3 &= (~(0xFFFFFFFFU));
	ADCx->SQR4 &= (~(0xFFFFFFFFU));
	volatile uint8_t offset = 6;
	for(uint8_t i = 0; i < 4 && i < ADC_Regular_SequenceLength; i++)
	{
		ADCx->SQR1 |= ((Channel_list[i] & 0x1FU) << offset);
		offset+=6;
	}
	offset = 0;
	for(uint8_t i = 4; i < 9 && i < ADC_Regular_SequenceLength; i++)
	{
		ADCx->SQR2 |= ((Channel_list[i] & 0x1Fu) << offset);
		offset+=6;
	}
	offset = 0;
	for(uint8_t i = 9; i < 14 && i < ADC_Regular_SequenceLength; i++)
	{
		ADCx->SQR3 |= ((Channel_list[i] & 0x1FU) << offset);
		offset+=6;
	}
	offset = 0;
	for(uint8_t i = 14; i < 16 && i < ADC_Regular_SequenceLength; i++)
	{
		ADCx->SQR4 |= ((Channel_list[i] & 0x1FU) << offset);
		offset+=6;
	}
}
void ADC_SampleTime_Setting(ADC_TypeDef* ADCx,EN_ADC_SampleTime ADC_SampleTime, uint8_t Channel)
{
	if(Channel >= 10)
	{
		ADCx->SMPR2 &= ( ~( (7U) << (Channel % 10 * 3) ) );
		ADCx->SMPR2 |= ( (ADC_SampleTime & 7U) << (Channel % 10 * 3));
	}
	else
	{
		ADCx->SMPR1 &= ( ~( (7U) << (Channel * 3) ) );
		ADCx->SMPR1 |= ( (ADC_SampleTime & 7U) << (Channel % 10 * 3));
	}
}
void ADC_Enable(ADC_TypeDef* ADCx)
{
	ADCx->ISR |= 1U;
	ADCx->CR &= (~ADC_CR_ADEN_Msk);
	ADCx->CR |= (ADC_ADEN_ENABLE << ADC_CR_ADEN_Pos);
	while( !( (ADCx->ISR >> ADC_ISR_ADRDY_Pos) & 1U ) );
	while( ( (ADCx->CR >> ADC_CR_ADSTART_Pos) & 1U ) );
}
void ADC_Disable(ADC_TypeDef* ADCx)
{
	ADCx->CR &= (~ADC_CR_ADDIS_Msk);
	ADCx->CR |= (ADC_ADDIS_ENABLE << ADC_CR_ADDIS_Pos);
	while( (ADCx->CR >> ADC_CR_ADDIS_Pos) & 1U );
}
void ADC_Start_Conversion(ADC_TypeDef* ADCx)
{
	ADCx->CR |= (ADC_ADSTART_ENABLE << ADC_CR_ADSTART_Pos);
}
