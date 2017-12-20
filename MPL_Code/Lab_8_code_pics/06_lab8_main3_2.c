#include "../inc/core_cm4.h"
#include "../inc/stm32l476xx.h"
#include "../inc/system_stm32l4xx.h"
//#include "./inc/lab8_header.h"
#define base 8
#define GPIO_Pin_8 8
#define GPIO_Pin_9 9
#define GPIO_Pin_10 10
#define GPIO_Pin_11 11
int current_col = 3;
char key_value = 0;
unsigned int input_value;
unsigned int x_pin[4] = {GPIO_Pin_8, GPIO_Pin_9, GPIO_Pin_10, GPIO_Pin_11};
extern void MAX7219Send(unsigned char address, unsigned char data);
const int match_matrix[4][4]={
	{1,2,3,10},
	{4,5,6,11},
	{7,8,9,12},
	{15,0,14,13}
};
const unsigned int output_array[4]={0x100, 0x200, 0x400, 0x800};
void Essential_GPIO_init()
{
	/**/
	RCC->AHB2ENR = RCC->AHB2ENR & (~RCC_AHB2ENR_GPIOBEN_Msk);
	RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOBEN;
	/**/
}
void seven_segment_blank(int num_digts)
{
	for(unsigned int i=0 ; i<num_digts; i++)
	{
		MAX7219Send(i+1,0x0FU);
	}
}
void GPIO_init()
{
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE3_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE4_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE5_Msk);
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE3_0;
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE4_0;
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE5_0;
	/*Ports 3,4,5 as output high speed mode*/
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED3_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED4_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED5_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED3_1;
	GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED4_1;
	GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED5_1;

	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE8_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE9_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE10_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE11_Msk);
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE8_0;
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE9_0;
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE10_0;
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE11_0;
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED8_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED9_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED10_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED11_Msk);

	/*PA2, PB2, PC2, PD2 as input mode*/
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE12_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE13_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE14_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE15_Msk);
	/**/
	GPIOB->PUPDR = GPIOB->PUPDR & (~GPIO_MODER_MODE12_Msk);
	GPIOB->PUPDR = GPIOB->PUPDR & (~GPIO_MODER_MODE13_Msk);
	GPIOB->PUPDR = GPIOB->PUPDR & (~GPIO_MODER_MODE14_Msk);
	GPIOB->PUPDR = GPIOB->PUPDR & (~GPIO_MODER_MODE15_Msk);
	GPIOB->PUPDR = GPIOB->PUPDR | GPIO_PUPDR_PUPD12_1;
	GPIOB->PUPDR = GPIOB->PUPDR | GPIO_PUPDR_PUPD13_1;
	GPIOB->PUPDR = GPIOB->PUPDR | GPIO_PUPDR_PUPD14_1;
	GPIOB->PUPDR = GPIOB->PUPDR | GPIO_PUPDR_PUPD15_1;
	MAX7219Send(0x0CU,0x01U);//Shutdown register, 1=>Normal operation
	MAX7219Send(0x0FU,0x00U);//Display Test, 1=>Normal Operation
	MAX7219Send(0x09U,0xFFU);//Decode Mode, FF=>All bits use CodeB Format
	MAX7219Send(0x0BU,0x01U);//Scan-Limit Register, 1=>For bit0 and bit1
	MAX7219Send(0x0AU,0x05U);//Intensity Register
	seven_segment_blank(8);
	MAX7219Send(1, 8);//MAX7219 test
}
void display(char value, int digit)
{
	int address = 1;
	seven_segment_blank(8);
	do
	{
		MAX7219Send(address, value%10);
		value /= 10;
		address++;
	}
	while(value);
	return;
}
void SystemClock_Config()
{
	//TODO: Setup system clock and SysTick timer interrupt
	/*
	*MSI(4Mhz) be the clock source
	**/
	//Enable SYSCFG
	RCC->APB2ENR = RCC->APB2ENR & 0xFFFFFFFE;
	RCC->APB2ENR = RCC->APB2ENR | 0x00000001U;
	/*SysTick config*/
	SysTick->CTRL = SysTick->CTRL & (~SysTick_CTRL_ENABLE_Msk);
	SysTick->CTRL = SysTick->CTRL & (~SysTick_CTRL_TICKINT_Msk);
	SysTick->CTRL = SysTick->CTRL & (~SysTick_CTRL_CLKSOURCE_Msk);
	SysTick->CTRL = SysTick->CTRL | (0x01U << SysTick_CTRL_ENABLE_Pos);		//Enable SysTick timer
	SysTick->CTRL = SysTick->CTRL | (0x01U << SysTick_CTRL_TICKINT_Pos);		//Count to 0, assert SysTick exception request
	SysTick->CTRL = SysTick->CTRL | (0x00U << SysTick_CTRL_CLKSOURCE_Msk);	//Choose processor clock as clock source
	SysTick->LOAD = SysTick->LOAD & (~SysTick_VAL_CURRENT_Msk);
	SysTick->LOAD = SysTick->LOAD | (49999U << SysTick_VAL_CURRENT_Pos);
	SysTick->VAL = SysTick->VAL & (~SysTick_LOAD_RELOAD_Msk);
}
void SysTick_Handler(void) {
	//TODO: Scan the keypad column
	//Clear the specific bit using BRR
	/*GPIOB->BSRR = GPIOB->BSRR & ~((0x01U << (current_col + 8)));
	GPIOB->BRR = GPIOB->BRR | (0x01U << (current_col + 8));*/
	current_col++;
	current_col %= 4;
	GPIOB->ODR = output_array[current_col];
	//Set the next bit BSRR
	/*GPIOB->BRR = GPIOB->BRR & (~(0x01U << (current_col + 8)));
	GPIOB->BSRR = GPIOB->BSRR | (0x01U << (current_col + 8));*/
}
void EXTI_Setup()
{
	//TODO: Setup EXTI interrupt
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_SetPriority(EXTI15_10_IRQn, 47);
	/*Connect GPIO to EXTI*/
	SYSCFG->EXTICR[3] = SYSCFG->EXTICR[3] & (~SYSCFG_EXTICR4_EXTI12_Msk);
	SYSCFG->EXTICR[3] = SYSCFG->EXTICR[3] & (~SYSCFG_EXTICR4_EXTI13_Msk);
	SYSCFG->EXTICR[3] = SYSCFG->EXTICR[3] & (~SYSCFG_EXTICR4_EXTI14_Msk);
	SYSCFG->EXTICR[3] = SYSCFG->EXTICR[3] & (~SYSCFG_EXTICR4_EXTI15_Msk);
	SYSCFG->EXTICR[3] = SYSCFG->EXTICR[3] | (SYSCFG_EXTICR4_EXTI12_PB);
	SYSCFG->EXTICR[3] = SYSCFG->EXTICR[3] | (SYSCFG_EXTICR4_EXTI13_PB);
	SYSCFG->EXTICR[3] = SYSCFG->EXTICR[3] | (SYSCFG_EXTICR4_EXTI14_PB);
	SYSCFG->EXTICR[3] = SYSCFG->EXTICR[3] | (SYSCFG_EXTICR4_EXTI15_PB);
	/*Set to rising edge*/
	EXTI->RTSR1 = EXTI->RTSR1 & (~EXTI_RTSR1_RT12_Msk);
	EXTI->RTSR1 = EXTI->RTSR1 & (~EXTI_RTSR1_RT13_Msk);
	EXTI->RTSR1 = EXTI->RTSR1 & (~EXTI_RTSR1_RT14_Msk);
	EXTI->RTSR1 = EXTI->RTSR1 & (~EXTI_RTSR1_RT15_Msk);
	EXTI->RTSR1 = EXTI->RTSR1 | EXTI_RTSR1_RT12;
	EXTI->RTSR1 = EXTI->RTSR1 | EXTI_RTSR1_RT13;
	EXTI->RTSR1 = EXTI->RTSR1 | EXTI_RTSR1_RT14;
	EXTI->RTSR1 = EXTI->RTSR1 | EXTI_RTSR1_RT15;

	EXTI->IMR1 = EXTI->IMR1 & (~EXTI_IMR1_IM12_Msk);
	EXTI->IMR1 = EXTI->IMR1 & (~EXTI_IMR1_IM13_Msk);
	EXTI->IMR1 = EXTI->IMR1 & (~EXTI_IMR1_IM14_Msk);
	EXTI->IMR1 = EXTI->IMR1 & (~EXTI_IMR1_IM15_Msk);
	EXTI->IMR1 = EXTI->IMR1 | EXTI_IMR1_IM12;
	EXTI->IMR1 = EXTI->IMR1 | EXTI_IMR1_IM13;
	EXTI->IMR1 = EXTI->IMR1 | EXTI_IMR1_IM14;
	EXTI->IMR1 = EXTI->IMR1 | EXTI_IMR1_IM15;
	return;
}
void EXTI15_10_IRQHandler(void)
{
	//TODO: Read the keypad row value
	SysTick->CTRL = SysTick->CTRL & (~SysTick_CTRL_ENABLE_Msk);
	input_value = GPIOB->IDR;
	input_value = input_value >> 12;
 	if(input_value == 8)
		key_value = match_matrix[3][3-current_col];
	else if(input_value == 4)
		key_value = match_matrix[2][3-current_col];
	else
		key_value = match_matrix[input_value - 1][3 - current_col];
	display(key_value,2);
	EXTI->PR1 = EXTI->PR1 | EXTI_PR1_PIF12;
	EXTI->PR1 = EXTI->PR1 | EXTI_PR1_PIF13;
	EXTI->PR1 = EXTI->PR1 | EXTI_PR1_PIF14;
	EXTI->PR1 = EXTI->PR1 | EXTI_PR1_PIF15;
	NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
	SysTick->CTRL = SysTick->CTRL | (0x01U << SysTick_CTRL_ENABLE_Pos);
	return;
}

int main()
{
	Essential_GPIO_init();
	GPIO_init();
	SystemClock_Config();
	EXTI_Setup();
	while(1)
	{

	}
	return 0;
}
