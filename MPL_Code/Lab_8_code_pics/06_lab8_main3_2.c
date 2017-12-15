#include "./inc/core_cm4.h"
#include "./inc/stm32l476xx.h"
#include "./inc/system_stm32l4xx.h"
#include "./inc/lab8_header.h"
#define base 8
#define GPIO_Pin_8 8
#define GPIO_Pin_9 9
#define GPIO_Pin_10 10
#define GPIO_Pin_11 11
int current_col = 3;
char key_value = 0;
unsigned int x_pin[4] = {GPIO_Pin_8, GPIO_Pin_9, GPIO_Pin_10, GPIO_Pin_11};
void EXIT_Setup()
{
	//TODO: Setup EXTI interrupt
}
void SystemClock_Config()
{
	//TODO: Setup system clock and SysTick timer interrupt

}
void SysTick_Handler(void) {
	//TODO: Scan the keypad column
	//Clear the specific bit using BRR
	GPIOB->BRR = GPIOB->BRR & (0x01U << (current_col + 8));
	GPIO->BSRR = 
	current_col++;
	current_col %= 4;
	//Set the next bit BSRR
	GPIOB->BSRR = GPIOB->BSRR & (0x01U << (current_col + 8));
}
void EXTIx_IRQHandler(void)
{
	//TODO: Read the keypad row value
}

int main()
{
	SystemClock_Config();
	GPIO_init();
	EXTI_Setup();
	while(1){
	display(key_value,2);
}