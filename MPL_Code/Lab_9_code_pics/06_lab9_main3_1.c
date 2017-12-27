#ifndef LAB9_MAIN_3_1_
#define LAB9_MAIN_3_1_
#include "../inc/gpio.h"
#include "../inc/lcd_function.h"
#include "../inc/delay.h"
#include "../inc/ADC.h"
#include "../inc/UART.h"
#define USART_InUse USART3
char buffer[32];
void Essential_GPIO_init(void)
{
	RCC->AHB2ENR = RCC->AHB2ENR & (~RCC_AHB2ENR_GPIOBEN_Msk) & (~RCC_AHB2ENR_GPIOCEN_Msk);
	RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN;
	return;
}
void usart_init(void)
{
	USART_Module_Init();
	USART_GPIO_Init();
	USART_Init(USART_InUse, USART_DATAWORD_8_BITS, USART_EVEN_PARITY, USART_PARITY_CONTROL_DISABLE, USART_OVERSAMPLING_16);
	USART_Stop_Bits_Selection(USART_InUse, USART_STOP_1_BIT);
	USART_Baud_Rate_Setting(USART_InUse, 9600U, USART_OVERSAMPLING_16);
	USART_Sample_Bits_Selection(USART_InUse, USART_THREE_SAMPLE_BIT);
	//USART_Tx_Interrupt_Control(USART_InUse, USART_TX_INTERRUPT_ENABLE);
	USART_Rx_Interrupt_Control(USART_InUse, USART_RX_INTERRUPT_ENABLE);
	USART_Hardware_Flow_Control(USART_InUse, USART_CTS_DISABLE, USART_RTS_DISABLE);
	USART_Asy_Mode_Setting(USART_InUse);
	USART_Rx_Control(USART_InUse, USART_RX_CONTROL_ENABLE);
}
void NVIC_USART3_ENABLE(void)
{
	NVIC_EnableIRQ(USART3_IRQn);
	NVIC_SetPriority(USART3_IRQn, 46);
	return;
}
int main(void)
{
	Essential_GPIO_init();
	lcd_gpio_init();
	NVIC_USART3_ENABLE();
	usart_init();
	LCD_Function_Set(1U, 1U, 0U);
	LCD_Enter_Mode(1U, 0U);
	LCD_Panel_Switcher(1U, 0U, 0U);
	LCD_ClearScreen();
	LCD_Cursor_Reset();
	LCD_Set_DDRAM_Address(0U);
	while(1);
	return 0;
}
#endif