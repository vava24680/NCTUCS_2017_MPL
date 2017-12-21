#include "../inc/lcd_function.h"

void lcd_gpio_init(void)
{
	TM_GPIO_Init(GPIOB, LCD_RS_PIN, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOB, LCD_RW_PIN, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOB, LCD_ENABLE_PIN, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOB, LCD_DATA0, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOB, LCD_DATA1, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOB, LCD_DATA2, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOB, LCD_DATA3, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOB, LCD_DATA4, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOB, LCD_DATA5, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOB, LCD_DATA6, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOB, LCD_DATA7, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	return;
}
uint8_t BusyCheck(void)
{
	uint8_t input_value;
	TM_GPIO_SetPinAsInput(GPIOB, LCD_DATA7);
	TM_GPIO_SetPullResistor(GPIOB, LCD_DATA7, TM_GPIO_PuPd_DOWN);
	TM_GPIO_SetPinLow_ODR(GPIOB, LCD_RS_PIN);
	TM_GPIO_SetPinHigh_ODR(GPIOB, LCD_RW_PIN);
	TM_GPIO_SetPinHigh_ODR(GPIOB, LCD_ENABLE_PIN);
	delay_us(10U);
	input_value = TM_GPIO_GetInputPinValue(GPIOB, LCD_DATA7);
	input_value = TM_GPIO_GetInputPinValue(GPIOB, LCD_DATA7);
	input_value = TM_GPIO_GetInputPinValue(GPIOB, LCD_DATA7);
	TM_GPIO_SetPinLow_ODR(GPIOB, LCD_ENABLE_PIN);
	TM_GPIO_SetPinAsOutput(GPIOB, LCD_DATA7);
	return input_value & 0x01U;
}
void WriteCommand(uint16_t command);
{
	while(BusyCheck());
	TM_GPIO_SetPinLow(GPIOB, LCD_RS_PIN);
	TM_GPIO_SetPinLow(GPIOB, LCD_RW_PIN);
	data &= 0x00FFU;
	TM_GPIO_SetSerialOutput(GPIOB, command);
	TM_GPIO_SetPinHigh_ODR(GPIOB, LCD_ENABLE_PIN);
	delay_ms(1);
	TM_GPIO_SetPinLow_ODR(GPIOB, LCD_ENABLE_PIN);
	delay_ms(1);
}
void WriteData(uint16_t data)
{
	while(BusyCheck());
	TM_GPIO_SetPinHigh_ODR(GPIOB, LCD_RS_PIN);
	TM_GPIO_SetPinLow(GPIOB, LCD_RW_PIN);
	data &= 0x00FFU;
	TM_GPIO_SetSerialOutput(GPIOB, data);
	TM_GPIO_SetPinHigh_ODR(GPIOB, LCD_ENABLE_PIN);
	delay_ms(1);
	TM_GPIO_SetPinLow_ODR(GPIOB, LCD_ENABLE_PIN);
	delay_ms(1);
}
void LCD_ClearScreen(void)
{
	WriteCommand(0x0001U);
	delay_ms(2);
}
void LCD_Show_CursorShow_Blink(uint16_t show, uint16_t cursor_show, uint16_t blink)
{
	uint16_t command = 0x0008U | show | cursor_show | blink;
	WriteCommand(command);
	delay_us(1);
}