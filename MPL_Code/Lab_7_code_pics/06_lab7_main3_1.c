#include"../inc/lab7_header.h"
extern int Delay();
extern void STACK_INIT();

const int PLLN_ARR[5] = {8, 12, 20, 8, 40};
const int PLLM_ARR[5] = {3, 3, 3, 0, 1};//PLLM, 0 means 1.
const int PLLR_ARR[5] = {3, 0, 0, 0, 0};//PLLR, 0->PLLR=2
int current_state = 0;
int debounce_array = 0xFFFFFFFF;

void GPIO_init()
{
	/**/
	RCC->AHB2ENR = RCC->AHB2ENR & (~RCC_AHB2ENR_GPIOBEN_Msk);
	RCC->AHB2ENR = RCC->AHB2ENR & (!RCC_AHB2ENR_GPIOCEN_Msk);
	RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN;
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE3_Msk);
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE3_0;
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED3_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED3_1;
	GPIOC->MODER = GPIOC->MODER & (~GPIO_MODER_MODE13_Msk);
	/**/
}

void SystemClock_Config(int turn)
{
	int RCC_CR;
	int RCC_PLLCFGR;
	int RCC_CFGR;
	int PLL_PLLN = PLLN_ARR[turn];
	int PLL_PLLM = PLLM_ARR[turn];
	int PLL_PLLR = PLLR_ARR[turn];
	/**/
	do
	{
		RCC_CR = RCC->CR;
		RCC_CR = (RCC_CR >> RCC_CR_MSIRDY_Pos);
	} while(!(RCC_CR & 0x01));
	RCC_CFGR = RCC->CFGR;
	RCC_CFGR = RCC_CFGR & (~RCC_CFGR_SW_Msk);
	RCC_CFGR = RCC_CFGR | (0x00 << RCC_CFGR_SW_Pos);
	RCC->CFGR = RCC_CFGR;

	RCC->CR = RCC->CR & (~RCC_CR_PLLON_Msk);
	do
	{
		RCC_CR = RCC->CR;
		RCC_CR = RCC_CR >> RCC_CR_PLLRDY_Pos;
	} while(RCC_CR & 0x01);
	RCC_PLLCFGR = RCC->PLLCFGR;
	RCC_PLLCFGR = RCC_PLLCFGR & (~RCC_PLLCFGR_PLLSRC_MSI_Msk);
	RCC_PLLCFGR = RCC_PLLCFGR & (~RCC_PLLCFGR_PLLN_Msk);
	RCC_PLLCFGR = RCC_PLLCFGR & (~RCC_PLLCFGR_PLLM_Msk);
	RCC_PLLCFGR = RCC_PLLCFGR & (~RCC_PLLCFGR_PLLR_Msk);
	RCC_PLLCFGR = RCC_PLLCFGR | (1 << RCC_PLLCFGR_PLLSRC_MSI_Pos) | (PLL_PLLN << RCC_PLLCFGR_PLLN_Pos) | (PLL_PLLM << RCC_PLLCFGR_PLLM_Pos) | (PLL_PLLR << RCC_PLLCFGR_PLLR_Pos);
	RCC->PLLCFGR = RCC_PLLCFGR;
	RCC->CR = RCC->CR & (~RCC_CR_PLLON_Msk);
	RCC->CR = RCC->CR | (1 << RCC_CR_PLLON_Pos);
	RCC_PLLCFGR = RCC->PLLCFGR;

	RCC_PLLCFGR = RCC_PLLCFGR & (~RCC_PLLCFGR_PLLREN_Msk);
	RCC_PLLCFGR = RCC_PLLCFGR & (~RCC_PLLCFGR_PLLPEN_Msk);
	RCC_PLLCFGR = RCC_PLLCFGR & (~RCC_PLLCFGR_PLLQEN_Msk);
	RCC->PLLCFGR = RCC_PLLCFGR | (1 << RCC_PLLCFGR_PLLREN_Pos) | (1 << RCC_PLLCFGR_PLLPEN_Pos) | (1 << RCC_PLLCFGR_PLLQEN_Pos);

	do
	{
		RCC_CR = RCC->CR;
		RCC_CR = (RCC_CR >> RCC_CR_PLLRDY_Pos);
	} while(!(RCC_CR & 0x01));

	RCC_CFGR = RCC->CFGR;
	RCC_CFGR = RCC_CFGR & (~RCC_CFGR_SW_Msk);
	RCC_CFGR = RCC_CFGR | (0x03 << RCC_CFGR_SW_Pos);
	RCC->CFGR = RCC_CFGR;
}

int user_press_button(void)
{
	int GPIOC_IDR_13 = ( (GPIOC->IDR >> 13U) & 0x01);
	if(GPIOC_IDR_13 == 0)
	{
		current_state = 1;
	}
	else
	{
		if(current_state==1)
		{
			current_state = 0;
			return 1;
		}
	}
	return 0;
	/*if(current_state == 1)
	{
		current_state += GPIOC_ODR_13;
	}
	if(current_state == 2)
	{
		current_state = 0;
		debounce_array = 0xFFFFFFFF;
		return 1;
	}
	debounce_array = (debounce_array << 1) | GPIOC_ODR_13;
	current_state = debounce_array==0xFFFF0000 ? 1 : 0;*/
	return 0;
}

int main(void)
{
	int turn = 0;
	int result;
	GPIO_init();
	SystemClock_Config(0);
	STACK_INIT();
	while(1)
	{
		/*if(user_press_button())
		{
			turn++;
			SystemClock_Config(turn);
		}*/
		GPIOB->BSRR = GPIOB->BSRR & (~GPIO_BSRR_BS3_Msk);
		GPIOB->BRR = GPIOB->BRR | GPIO_BRR_BR3;
		//WaitOneSecond();
		result = Delay();
		if(result)
		{
			turn++;
			SystemClock_Config(turn);
		}
		GPIOB->BRR = GPIOB->BRR & (~GPIO_BRR_BR3_Msk);
		GPIOB->BSRR = GPIOB->BSRR | GPIO_BSRR_BS3;
		//WaitOneSecond();
		if(Delay())
		{
			turn++;
			SystemClock_Config(turn);
		}
	}
	return 0;
}
