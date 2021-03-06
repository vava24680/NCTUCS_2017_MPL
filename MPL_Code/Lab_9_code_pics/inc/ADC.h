#ifndef ADC_H_
#define ADC_H_
#include "./gpio.h"
#include "./delay.h"
extern uint32_t ADC_result;
/*
---------------------------------------------
|	UART GPIO Pin Explanation				|
---------------------------------------------
|	GPIO Module	|	Pin	|	Function		|
|	GPIOB		|	1	|	ADC_Analog_In	|
---------------------------------------------
*/
#define ADC_Analog_In 1U
typedef enum GPIO_ADC_switch_control
{
	GPIO_ASCR_DISCONNECT = 0U,
	GPIO_ASCR_CONNECT = 1U
} EN_GPIO_ASCR;
typedef enum ADC_clock_control
{
	ADC_CLOCK_DISABLE = 0U,
	ADC_CLOCK_ENABLE = 1U
} EN_ADC_CLOCK_CONTROL;
typedef enum ADC_peripheral_clock_select
{
	ADC_PERIPHERAL_CLOCK_NO_CLOCK = 0U,
	ADC_PERIPHERAL_CLOCK_PLLSAI1R_CLOCK = 1U,
	ADC_PERIPHERAL_CLOCK_PLLSAI2R_CLOCK = 2U,
	ADC_PERIPHERAL_CLOCK_SYSCLK = 3U
} EN_ADC_PERIPHERAL_CLOCK;
typedef enum ADC_built_in_common_clock_select
{
	ADC_BUILT_IN_COMMON_CLOCK_PERIPHERAL_CLOCK = 0U,
	ADC_BUILT_IN_COMMON_CLOCK_HCLK_DIVED_1 = 1U,
	ADC_BUILT_IN_COMMON_CLOCK_HCLK_DIVED_2 = 2U,
	ADC_BUILT_IN_COMMON_CLOCK_HCLK_DIVED_4 = 3U
} ADC_BUILT_IN_COMMON_CLOCK;
typedef enum ADC_eoc_interrupt_control
{
	ADC_EOC_INTERRUPT_DISABLE = 0U,
	ADC_EOC_INTERRUPT_ENABLE = 1U
} EN_ADC_EOC_INTERRUPT_CONTROL;
typedef enum ADC_CR
{
	ADC_DEEPPWD_DISABLE = 0U,
	ADC_DEEPPWD_ENABLE = 1U,
	ADC_ADVREG_DISABLE = 0U,
	ADC_ADVRED_ENABLE = 1U,
	ADC_ADSTART_DISABLE = 0U,
	ADC_ADSTART_ENABLE = 1U,
	ADC_ADDIS_ENABLE = 1U,
	ADC_ADEN_ENABLE = 1U
} EN_ADC_CR;
typedef enum ADC_input_mode
{
	ADC_SINGLE_ENDED_MODE = 0U,
	ADC_DIFFERENTIAL_MODE = 1U
} EN_ADC_INPUT_MODE;
typedef enum ADC_Conversion_List
{
	ADC_Conversion_SingleMode = 0U,
	ADC_Conversion_ContinuousMode = 1U
} EN_ADC_CONVERSION_MODE;
typedef enum ADC_data_align
{
	ADC_Data_Right_Align = 0U,
	ADC_Data_Left_Align = 1U
} EN_ADC_DATA_ALIGN;
typedef enum ADC_Resoultion_List
{
	ADC_Resolution_12Bit = 0U,
	ADC_Resolution_10Bit = 1U,
	ADC_Resolution_8Bit = 2U,
	ADC_Resolution_6Bit = 3U
} EN_ADC_RESOLUTION;
typedef enum ADC_Regular_SequenceLen
{
	ADC_Lenth_1, ADC_Lenth_2, ADC_Lenth_3, ADC_Lenth_4,
	ADC_Lenth_5, ADC_Lenth_6, ADC_Lenth_7, ADC_Lenth_8,
	ADC_Lenth_9, ADC_Lenth_10, ADC_Lenth_11, ADC_Lenth_12,
	ADC_Lenth_13, ADC_Lenth_14, ADC_Lenth_15, ADC_Lenth_16
} EN_ADC_Regular_Sequence_Length;
typedef enum ADC_SampleTime_List
{
	ADC_Sample_2_5_Cycles = 0U,
	ADC_Sample_6_5_Cycles = 1U,
	ADC_Sample_12_5_Cycles = 2U,
	ADC_Sample_24_5_Cycles = 3U,
	ADC_Sample_47_5_Cycles = 4U,
	ADC_Sample_92_5_Cycles = 5U,
	ADC_Sample_247_5_Cycles = 6U,
	ADC_Sample_640_5_Cycles = 7U
} EN_ADC_SampleTime;
void ADC_GPIO_Init(GPIO_TypeDef* GPIOx);
void ADC_GPIO_ASCR_Control(GPIO_TypeDef* GPIOx, uint32_t Pin, EN_GPIO_ASCR GPIO_ASCR);
void ADC_Clock_Control(EN_ADC_CLOCK_CONTROL ADC_clock_option);
void ADC_Peripheral_Clock_Setting(EN_ADC_PERIPHERAL_CLOCK ADC_Peripheral_Clock);
void ADC_BuiltIn_Common_Clock_Setting(ADC_TypeDef* ADCx, ADC_BUILT_IN_COMMON_CLOCK ADC_BuiltIn_Common_Clock);
void ADC_Init(ADC_TypeDef* ADCx);
uint32_t ADC_Calibration(ADC_TypeDef* ADCx, EN_ADC_INPUT_MODE ADC_Input_Mode);
void ADC_EOC_Interrupt_Control(ADC_TypeDef* ADCx, EN_ADC_EOC_INTERRUPT_CONTROL ADC_EOC_Interrupt_Option);
void ADC_ConvertionMode_Setting(ADC_TypeDef* ADCx, EN_ADC_CONVERSION_MODE ADC_ConversionMode);
void ADC_Data_Align_Setting(ADC_TypeDef* ADCx, EN_ADC_DATA_ALIGN ADC_Data_Align);
void ADC_Resolution_Setting(ADC_TypeDef* ADCx, EN_ADC_RESOLUTION ADC_Resolution);
void ADC_Regular_SequenceLength_Setting(ADC_TypeDef* ADCx, EN_ADC_Regular_Sequence_Length ADC_Regular_SequenceLength,const uint8_t Channel_list[]);
void ADC_SampleTime_Setting(ADC_TypeDef* ADCx,EN_ADC_SampleTime ADC_SampleTime, uint8_t Channel);
void ADC_Enable(ADC_TypeDef* ADCx);
void ADC_Disable(ADC_TypeDef* ADCx);
void ADC_Start_Conversion(ADC_TypeDef* ADCx);
#endif
