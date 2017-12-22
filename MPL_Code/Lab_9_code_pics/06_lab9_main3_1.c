#include "../inc/gpio.h"
#include "../inc/ref.h"
#include "../inc/lcd_function.h"

void Essential_GPIO_init(void)
{
	RCC->AHB2ENR = RCC->AHB2ENR & (~RCC_AHB2ENR_GPIOBEN_Msk);
	RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOBEN;
	return;
}
int main(void)
{
	uint8_t result;
	Essential_GPIO_init();
	lcd_gpio_init();
	LCD_Function_Set(0x0001U, 0x0001U, 0x0000U);
	LCD_Enter_Mode(0x0001U, 0x0000U);
	LCD_Panel_Switcher(0x0001U, 0x0000U, 0x0000U);
	LCD_ClearScreen();
	LCD_WriteData((uint16_t)'A');
	return 0;
}
