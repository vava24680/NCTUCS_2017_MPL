#include"../inc/lab7_header.h"
#define PRESCALER 0
#define DO (4000000 / 262)
#define RE (4000000 / 294)
#define MI (4000000 / 330)
#define FA (4000000 / 350)
#define SOL (4000000 / 392)
#define LA (4000000 / 440)
#define SI (4000000 / 494)
#define HIGHDO (4000000 / 523)
#define X0 GPIO_Pin_8
#define X1 GPIO_Pin_9
#define X2 GPIO_Pin_10
#define X3 GPIO_Pin_11
#define Y0 GPIO_Pin_12
#define Y1 GPIO_Pin_13
#define Y2 GPIO_Pin_14
#define Y3 GPIO_Pin_15
unsigned int x_pin[4] = {X0, X1, X2, X3};
unsigned int y_pin[4] = {Y0, Y1, Y2, Y3};
//extern void GPIO_init();
const int match_matrix[4][4]={
	{DO, RE, MI, 1},
	{FA, SOL, LA, 2},
	{SI, HIGHDO, 0, 0},
	{0, 0, 0, 0}
};
/********************************
 *GPIO usage :					*
 *GPIOB->Pin3: Output for buzzer*
 *********************************/
void GPIO_init()
{
	RCC->AHB2ENR = RCC->AHB2ENR & (~RCC_AHB2ENR_GPIOBEN_Msk);
	RCC->AHB2ENR = RCC->AHB2ENR & (~RCC_AHB2ENR_GPIOCEN_Msk);
	RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOCEN;
	/*Port 8,9,10,11 as output mode*/
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE8_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE9_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE10_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE11_Msk);
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE8_0;
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE9_0;
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE10_0;
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE11_0;
	/**/
	/*Ports 8,9,10,11 as output high speed mode*/
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED8_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED9_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED10_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED11_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED8_1;
	GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED9_1;
	GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED10_1;
	GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED11_1;
	/**/
	/*Port 12,13,14,15 as input mode*/
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE12_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE13_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE14_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE15_Msk);
	/*Port 12,13,14,15 as input mode and let them be puul-down*/
	GPIOB->PUPDR = GPIOB->PUPDR & (~GPIO_PUPDR_PUPD12_Msk);
	GPIOB->PUPDR = GPIOB->PUPDR & (~GPIO_PUPDR_PUPD13_Msk);
	GPIOB->PUPDR = GPIOB->PUPDR & (~GPIO_PUPDR_PUPD14_Msk);
	GPIOB->PUPDR = GPIOB->PUPDR & (~GPIO_PUPDR_PUPD15_Msk);
	GPIOB->PUPDR = GPIOB->PUPDR | GPIO_PUPDR_PUPD12_1;
	GPIOB->PUPDR = GPIOB->PUPDR | GPIO_PUPDR_PUPD13_1;
	GPIOB->PUPDR = GPIOB->PUPDR | GPIO_PUPDR_PUPD14_1;
	GPIOB->PUPDR = GPIOB->PUPDR | GPIO_PUPDR_PUPD15_1;

	/*Buzzer Initialize*/

}

void GPIO_init_AF()
{
	//TODO: Initial GPIO pin as alternate function for buzzer. You can choose to use C or assembly to finish this function.
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE3_Msk);
	GPIOB->MODER = GPIOB->MODER | (0x02 << GPIO_MODER_MODE3_Pos);
	GPIOB->AFR[0] = GPIOB->AFR[0] & (~GPIO_AFRL_AFSEL3_Msk);
	GPIOB->AFR[0] = GPIOB->AFR[0] | (0x01 << GPIO_AFRL_AFSEL3_Pos);
}

void Timer_init( TIM_TypeDef *timer)
{
	RCC->APB1ENR1 = RCC->APB1ENR1 & (~RCC_APB1ENR1_TIM2EN_Msk);
	RCC->APB1ENR1 = RCC->APB1ENR1 | RCC_APB1ENR1_TIM2EN;
	TIM2->CR1 = TIM2->CR1 & (~TIM_CR1_CEN_Msk);
	TIM2->CR1 = TIM2->CR1 & (~TIM_CR1_DIR_Msk);
	/*Capture/Compare as Output*/
	TIM2->CCMR1 = TIM2->CCMR1 & (~TIM_CCMR1_CC2S_Msk);
	TIM2->CCMR1 = TIM2->CCMR1 | (0x00U << TIM_CCMR1_CC2S_Pos);
	/*Capture/Compare as PWM mode*/
	TIM2->CCMR1 = TIM2->CCMR1 & (~TIM_CCMR1_OC2M_Msk);
	TIM2->CCMR1 = TIM2->CCMR1 | (0x0006U << TIM_CCMR1_OC2M_Pos);
	/*Capture/Compare output enable*/
	TIM2->CCER = TIM2->CCER & (~TIM_CCER_CC2E_Msk);
	TIM2->CCER = TIM2->CCER | (0x01U << TIM_CCER_CC2E_Pos);
	/*TIM2->CCER = TIM2->CCER & (~TIM_CCER_CC2P_Msk);
	TIM2->CCER = TIM2->CCER | (0x01U << TIM_CCER_CC2P_Pos);*/
	TIM2->PSC = TIM2->PSC & (~TIM_PSC_PSC_Msk);
	TIM2->PSC = TIM2->PSC | (0U);
	/*TIM2 interrupt enable*/
	TIM2->DIER = TIM2->DIER & (~TIM_DIER_UIE_Msk);
	TIM2->DIER = TIM2->DIER | (0x01U << TIM_DIER_UIE_Pos);
	return;
}

int keypad_scan()
{
	uint32_t input_value;
	uint32_t y_value;
	unsigned mask = 0x00U;//Not Umask
	for(int i = 0; i < 4; i++)
	{
		mask = (0x01U << x_pin[i]);
		GPIOB->BSRR = GPIOB->BSRR & (~mask);
		GPIOB->BSRR = GPIOB->BSRR | mask;
		input_value = GPIOB->IDR;
		/*
		 *Important!! After scanning one column, clear that column is necessary
		 *Or it may cause error(e.g. push 1 but you see 2)
		 */
		GPIOB->BRR = GPIOB->BRR & (~mask);
		GPIOB->BRR = GPIOB->BRR | mask;
		/*---------------------------------------------------------------------*/
		input_value = input_value >> 12;
		input_value &= 0x0000000F;
		if(input_value==8)
		{
			y_value = 3;
		}
		else if(input_value==4)
		{
			y_value = 2;
		}
		else
		{
			y_value = input_value-1;
		}
		if(input_value>0)
		{
			return match_matrix[y_value][3-i];
		}
	}
	return -1;
}

void close()
{
	/*Capture/Compare enable*/
	/*TIM2->CCER = TIM2->CCER & (~TIM_CCER_CC2E_Msk);
	TIM2->CCER = TIM2->CCER | (0x00U << TIM_CCER_CC2E_Pos);
	TIM2->CCER = TIM2->CCER & (~TIM_CCER_CC2P_Msk);
	TIM2->CCER = TIM2->CCER | (0x00U << TIM_CCER_CC2P_Pos);*/
	TIM2->CR1 = TIM2->CR1 & (~TIM_CR1_CEN_Msk);
	TIM2->CR1 = TIM2->CR1 & (0x00U << TIM_CR1_CEN_Pos);
	return;
}

void PWM_channel_init(int autoreload, int duty_ratio)
{
	//TODO: Initialize timer PWM channel
	/*Disable counter*/
	TIM2->CR1 = TIM2->CR1 & (~TIM_CR1_CEN_Msk);
	TIM2->CR1 = TIM2->CR1 | (0U << TIM_CR1_CEN_Pos);
	/*Write new Autoreload value*/
	TIM2->ARR = TIM2->ARR & (~TIM_ARR_ARR_Msk);
	TIM2->ARR = TIM2->ARR | (autoreload);
	/*Capture/Compare register value*/
	TIM2->CCR2 = TIM2->CCR2 & (~TIM_CCR2_CCR2_Msk);
	TIM2->CCR2 = TIM2->CCR2 | (((int)(autoreload * duty_ratio / 100.0)));
	/*Update Prescaler and Autoreloader*/
	TIM2->EGR = TIM2->EGR & (~TIM_EGR_UG_Msk);
	TIM2->EGR = TIM2->EGR | (1U << TIM_EGR_UG_Pos);
	/*Enable counter*/
	TIM2->CR1 = TIM2->CR1 & (~TIM_CR1_CEN_Msk);
	TIM2->CR1 = TIM2->CR1 | (1U << TIM_CR1_CEN_Pos);
}

int main()
{
	GPIO_init();
	GPIO_init_AF();
	Timer_init(TIM2);
	int pre_result = -1000;
	int result;
	int default_ratio = 50;
	int low_ratio = 10;
	int high_ratio = 90;
	int current_ratio = default_ratio;
	close();
	while(1)
	{
		result = keypad_scan();
		if(result > 0)
		{
			if(pre_result != result)
			{
				if(result == 2 || result == 1)
				{
					current_ratio = result == 1 ? current_ratio + 5 : current_ratio - 5;
					current_ratio = current_ratio >= high_ratio ? 90 : current_ratio;
					current_ratio = current_ratio <= low_ratio ? 10 : current_ratio;
				}
				else
				{
					PWM_channel_init(result, current_ratio);
				}
			}
		}
		else
		{
			close();
		}
		pre_result = result;
	}
	//TODO: Scan the keypad and use PWM to send the corresponding
	//frequency square wave to buzzer.
	return 0;
}
