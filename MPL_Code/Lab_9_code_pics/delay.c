#include "./inc/delay.h"

/*
* Here our system clokc is assumed as 4Mhz
*/
void Timer2_Init(void)
{
	RCC->APB1ENR1 = RCC->APB1ENR1 & (~RCC_APB1ENR1_TIM2EN_Msk);
	RCC->APB1ENR1 = RCC->APB1ENR1 | RCC_APB1ENR1_TIM2EN;
	TIM2->CR1 = TIM2->CR1 & (~TIM_CR1_DIR_Msk);/*Counting Down*/
	TIM2->PSC = TIM2->PSC & (~TIM_PSC_PSC_Msk);
	TIM2->PSC = TIM2->PSC | (4000000/US_FREQUENCY - 1);
	TIM2->ARR = TIM2->ARR & (~TIM_ARR_ARR_Msk);
	TIM2->ARR = TIM2->ARR | (US_FREQUENCY - 1);
	TIM2->EGR = TIM2->EGR & (~TIM_EGR_UG_Msk);
	TIM2->EGR = TIM2->EGR | (1U << TIM_EGR_UG_Pos);
}
void delay_ms(uint32_t value)
{
	Timer2_Init();
	
	return;
}

void delay_us(uint32_t value)
{


}