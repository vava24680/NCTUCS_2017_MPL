#ifndef LAB9_MAIN_3_2_
#define LAB9_MAIN_3_2_
#include "../inc/UART.h"
#include "../inc/ADC.h"
#include "../inc/gpio.h"
#include "../inc/button.h"
#include "stdio.h"
#define ADC_InUse ADC1
extern void STACK_INIT(void);
extern int user_press_button(void);
extern void FPU_ENABLE(void);
const uint8_t channel_list[] = {16};
uint32_t ADC_result;
char number2transmit[70];
void Essential_GPIO_init(void)
{
	RCC->AHB2ENR = RCC->AHB2ENR & (~RCC_AHB2ENR_GPIOBEN_Msk);
	RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOBEN;
	return;
}
void ADC_Combination_Configure()
{
	ADC_GPIO_Init(GPIOB);
	ADC_GPIO_ASCR_Control(GPIOB, 5U, GPIO_ASCR_CONNECT);
	ADC_Clock_Control(ADC_CLOCK_ENABLE);
	ADC_Peripheral_Clock_Setting(ADC_PERIPHERAL_CLOCK_SYSCLK);
	ADC_BuiltIn_Common_Clock_Setting(ADC_InUse, ADC_BUILT_IN_COMMON_CLOCK_PERIPHERAL_CLOCK);
	ADC_Init(ADC_InUse);
	ADC_Calibration(ADC_InUse, ADC_SINGLE_ENDED_MODE);
	ADC_ConvertionMode_Setting(ADC_InUse, ADC_Conversion_SingleMode);
	ADC_Data_Align_Setting(ADC_InUse, ADC_Data_Right_Align);
	ADC_Resolution_Setting(ADC_InUse, ADC_Resolution_12Bit);
	ADC_Regular_SequenceLength_Setting(ADC_InUse, ADC_Lenth_1, channel_list);
	ADC_SampleTime_Setting(ADC_InUse, ADC_Sample_6_5_Cycles, 16);
	ADC_EOC_Interrupt_Control(ADC_InUse, ADC_EOC_INTERRUPT_ENABLE);
	ADC_Enable(ADC_InUse);
}
void USART_Combination_Configure(void)
{
	USART_Module_Init();
	USART_GPIO_Init();
	USART_Init(USART3, USART_DATAWORD_8_BITS, USART_EVEN_PARITY, USART_PARITY_CONTROL_DISABLE, USART_OVERSAMPLING_16);
	USART_Stop_Bits_Selection(USART3, USART_STOP_1_BIT);
	USART_Baud_Rate_Setting(USART3, 9600U, USART_OVERSAMPLING_16);
	USART_Sample_Bits_Selection(USART3, USART_THREE_SAMPLE_BIT);
	USART_Hardware_Flow_Control(USART3, USART_CTS_DISABLE, USART_RTS_DISABLE);
	USART_Asy_Mode_Setting(USART3);
}
void int2string(void)
{
	sprintf(number2transmit, "%lu", ADC_result);
	unsigned int len = strlen(number2transmit);
	number2transmit[len] = '\n';
	number2transmit[len + 1] = '\r';
	number2transmit[len + 2] = '\0';
}
void ADC1_2_IRQHandler(void)
{
	ADC_result = ADC1->DR;
	int2string();
	USART_Transmit(USART3, number2transmit);
	NVIC_ClearPendingIRQ(ADC1_2_IRQn);
}
int main(void)
{
	FPU_ENABLE();
	Essential_GPIO_init();
	STACK_INIT();
	Button_Init();
	USART_Combination_Configure();
	NVIC_EnableIRQ(ADC1_2_IRQn);
	NVIC_SetPriority(ADC1_2_IRQn, 25);
	ADC_Combination_Configure();
	while(1)
	{
		if(user_press_button())
		{
			ADC_Start_Conversion(ADC_InUse);
		}
	}
	return 0;
}
#endif