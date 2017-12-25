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
	delay_ms(30);
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
	delay_us(10);
	TM_GPIO_SetPinAsOutput(GPIOB, LCD_DATA7);
	return input_value & 0x01U;
}
void LCD_WriteCommand(uint16_t command)
{
	while(BusyCheck());
	TM_GPIO_SetPinLow(GPIOB, LCD_RS_PIN);
	TM_GPIO_SetPinLow(GPIOB, LCD_RW_PIN);
	command &= 0x00FFU;
	TM_GPIO_SetSerialOutput(GPIOB, command << LCD_DATA0);
	TM_GPIO_SetPinHigh_ODR(GPIOB, LCD_ENABLE_PIN);
	delay_us(20);
	TM_GPIO_SetPinLow_ODR(GPIOB, LCD_ENABLE_PIN);
	delay_us(20);
}
void LCD_WriteCommand_4bit(uint16_t command)
{
	while(BusyCheck());
	TM_GPIO_SetPinLow(GPIOB, LCD_RS_PIN);
	TM_GPIO_SetPinLow(GPIOB, LCD_RW_PIN);
	TM_GPIO_SetSerialOutput(GPIOB, command << 12U);
	TM_GPIO_SetPinHigh_ODR(GPIOB, LCD_ENABLE_PIN);
	delay_us(6);
	TM_GPIO_SetPinLow_ODR(GPIOB, LCD_ENABLE_PIN);
	delay_us(6);
}
void LCD_WriteData(uint16_t data)
{
	while(BusyCheck());
	TM_GPIO_SetPinHigh_ODR(GPIOB, LCD_RS_PIN);
	TM_GPIO_SetPinLow(GPIOB, LCD_RW_PIN);
	data &= 0x00FFU;
	TM_GPIO_SetSerialOutput(GPIOB, data << LCD_DATA0);
	TM_GPIO_SetPinHigh_ODR(GPIOB, LCD_ENABLE_PIN);
	delay_us(20);
	TM_GPIO_SetPinLow_ODR(GPIOB, LCD_ENABLE_PIN);
	delay_us(5);
	TM_GPIO_SetPinLow(GPIOB, LCD_RS_PIN);
	delay_us(20);
}
void LCD_WriteData_4bit(uint16_t data)
{
	while(BusyCheck());
	TM_GPIO_SetPinLow(GPIOB, LCD_RS_PIN);
	TM_GPIO_SetPinLow(GPIOB, LCD_RW_PIN);
	TM_GPIO_SetSerialOutput(GPIOB, data << 12U);
	TM_GPIO_SetPinHigh_ODR(GPIOB, LCD_ENABLE_PIN);
	delay_us(6);
	TM_GPIO_SetPinLow_ODR(GPIOB, LCD_ENABLE_PIN);
	delay_us(6);
}
void LCD_ClearScreen(void)
{
	//while(BusyCheck());
	LCD_WriteCommand(0x0001U);
	//LCD_WriteCommand_4bit(0U);
	//LCD_WriteCommand_4bit(1U);
	delay_ms(2);
}
void LCD_Cursor_Reset(void)
{
	//while(BusyCheck());
	LCD_WriteCommand(0x0002U);
	//LCD_WriteCommand_4bit(0U);
	//LCD_WriteCommand_4bit(2U);
	delay_ms(2);
}
void LCD_Enter_Mode(uint16_t Incre_Decre, uint16_t Shift_screen)
{
	uint16_t command = 0x0004U | (Incre_Decre << 1U) | Shift_screen;
	//while(BusyCheck());
	LCD_WriteCommand(command);
	//LCD_WriteCommand_4bit(command >> 4U);
	//LCD_WriteCommand_4bit(command);
}
void LCD_Panel_Switcher(uint16_t screen_switch, uint16_t cursor_show, uint16_t cursor_blink)
{
	uint16_t command = 0x0008U | (screen_switch << 2U) | (cursor_show << 1U) | cursor_blink;
	LCD_WriteCommand(command);
}
void LCD_Cursor_Shift_Set(uint16_t object, uint16_t direction)
{
	uint16_t command = 0x0010U | (object << 3U) | (direction << 2U);
	LCD_WriteCommand(command);
}
void LCD_Function_Set(uint16_t DL, uint16_t N, uint16_t F)
{
	uint16_t command = 0x0020U | (DL << 4U) | (N << 3U) | (F << 2U);
	LCD_WriteCommand(command);
}
void LCD_Set_CRGRAM_Address(uint16_t five_bit_address)
{
	uint16_t command = 0x0040U | five_bit_address;
	LCD_WriteCommand(command);
}
void LCD_Set_DDRAM_Address(uint16_t six_bit_address)
{
	uint16_t command = 0x0080U | six_bit_address;
	LCD_WriteCommand(command);
}
void LCD_Function_Set_4bit(uint16_t DL, uint16_t N, uint16_t F)
{
	uint16_t command = 0x0020U | (DL << 4U) | (N << 3U) | (F << 2U);
	LCD_WriteCommand_4bit(command >> 8U);
	LCD_WriteCommand_4bit(command);
	delay_us(50);//Doesn't know why
}