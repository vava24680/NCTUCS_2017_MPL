#include "../inc/gpio.h"
#include "../inc/ref.h"
#include "../inc/lcd_function.h"

void Essential_GPIO_init(void)
{
	RCC->AHB2ENR = RCC->AHB2ENR & (~RCC_AHB2ENR_GPIOBEN_Msk);
	RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOBEN;
	return;
}
void SystemClock_Config(void)
{
	uint32_t PLLN = 40U;
	uint32_t PLLM = 0U;
	uint32_t PLLR = 0U;
	/**/
	while(!((RCC->CR >> 1U) & 0x01U));
	RCC->CFGR = RCC->CFGR & (~RCC_CFGR_SW_Msk);
	RCC->CFGR = RCC->CFGR | (0U << RCC_CFGR_SW_Pos);

	RCC->CR = RCC->CR & (~RCC_CR_PLLON_Msk);//Turn of PLL clock
	while((RCC->CR >> 25U) & 1U);

	RCC->PLLCFGR = RCC->PLLCFGR & (~RCC_PLLCFGR_PLLSRC_MSI_Msk) & (~RCC_PLLCFGR_PLLN_Msk) & (~RCC_PLLCFGR_PLLM_Msk) & (~RCC_PLLCFGR_PLLR_Msk);
	RCC->PLLCFGR = RCC->PLLCFGR | (1 << RCC_PLLCFGR_PLLSRC_MSI_Pos) | (PLLN << RCC_PLLCFGR_PLLN_Pos) | (PLLM << RCC_PLLCFGR_PLLM_Pos) | (PLLR << RCC_PLLCFGR_PLLR_Pos);
	RCC->CR = RCC->CR & (~RCC_CR_PLLON_Msk);
	RCC->CR = RCC->CR | (1 << RCC_CR_PLLON_Pos);

	RCC->PLLCFGR = RCC->PLLCFGR & (~RCC_PLLCFGR_PLLREN_Msk) & (~RCC_PLLCFGR_PLLPEN_Msk) & (~RCC_PLLCFGR_PLLQEN_Msk);
	RCC->PLLCFGR = RCC->PLLCFGR | (1 << RCC_PLLCFGR_PLLREN_Pos) | (1 << RCC_PLLCFGR_PLLPEN_Pos) | (1 << RCC_PLLCFGR_PLLQEN_Pos);

	while(!((RCC->CR >> 25U) & 1U))
	RCC->CFGR = RCC->CFGR & (~RCC_CFGR_SW_Msk);
	RCC->CFGR = RCC->CFGR | (0x03 << RCC_CFGR_SW_Pos);
}
int main(void)
{
	Essential_GPIO_init();
	//SystemClock_Config();
	lcd_gpio_init();
	LCD_Function_Set(0x0001U, 0x0001U, 0x0000U);
	//LCD_Function_Set_4bit(0x0000U, 0x0001U, 0x0000U);
	LCD_Enter_Mode(0x0001U, 0x0000U);
	LCD_Panel_Switcher(0x0001U, 0x0000U, 0x0000U);
	LCD_ClearScreen();
	LCD_Set_DDRAM_Address(0x0000U);
	LCD_WriteData((uint16_t)'A');
	return 0;
}
