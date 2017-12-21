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
	result = BusyCheck();
	return 0;
}
