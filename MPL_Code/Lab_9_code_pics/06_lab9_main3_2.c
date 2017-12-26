#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_
#include "../inc/UART.h"
#endif
#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_
#include "../inc/ADC.h"
#endif
#ifndef INCLUDE_GPIO_H_
#define INCLUDE_GPIO_H_
#include "../inc/gpio.h"
#endif
#ifndef INCLUDE_BUTTON_H_
#define INCLUDE_BUTTON_H_
#include "../inc/button.h"
#endif
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
/*void SystemClock_Config(void)
{
	while( !( (RCC->CR >> RCC_CR_MSIRDY_Pos) & 0x01) );
	RCC->CFGR &= (~RCC_CFGR_SW_Msk);
	RCC->CFGR |= (0x00 << RCC_CFGR_SW_Pos);

	RCC->CR = RCC->CR & (~RCC_CR_PLLON_Msk);
	while( (RCC->CR >> RCC_CR_PLLRDY_Pos) & 0x01);
	RCC->PLLCFGR &= (~RCC_PLLCFGR_PLLSRC_MSI_Msk);
	RCC->PLLCFGR &= (~RCC_PLLCFGR_PLLN_Msk);
	RCC->PLLCFGR &= (~RCC_PLLCFGR_PLLM_Msk);
	RCC->PLLCFGR &= (~RCC_PLLCFGR_PLLR_Msk);
	RCC->PLLCFGR = RCC->PLLCFGR | (1 << RCC_PLLCFGR_PLLSRC_MSI_Pos) | (40U << RCC_PLLCFGR_PLLN_Pos) | (0U << RCC_PLLCFGR_PLLM_Pos) | (0U << RCC_PLLCFGR_PLLR_Pos);
	RCC->CR &= (~RCC_CR_PLLON_Msk);
	RCC->CR |= (1 << RCC_CR_PLLON_Pos);

	RCC->PLLCFGR &= (~RCC_PLLCFGR_PLLREN_Msk);
	RCC->PLLCFGR &= (~RCC_PLLCFGR_PLLPEN_Msk);
	RCC->PLLCFGR &= (~RCC_PLLCFGR_PLLQEN_Msk);
	RCC->PLLCFGR = RCC->PLLCFGR | (1 << RCC_PLLCFGR_PLLREN_Pos) | (1 << RCC_PLLCFGR_PLLPEN_Pos) | (1 << RCC_PLLCFGR_PLLQEN_Pos);

	while( !( (RCC->CR >> RCC_CR_PLLRDY_Pos) & 0x01) );

	RCC->CFGR &= (~RCC_CFGR_SW_Msk);
	RCC->CFGR |= (0x03 << RCC_CFGR_SW_Pos);
}*/
void ADC_Combination_Configure()
{
	ADC_GPIO_Init(GPIOB);
	ADC_GPIO_ASCR_Control(GPIOB, 5U, GPIO_ASCR_CONNECT);
	ADC_Clock_Control(ADC_CLOCK_ENABLE);
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
