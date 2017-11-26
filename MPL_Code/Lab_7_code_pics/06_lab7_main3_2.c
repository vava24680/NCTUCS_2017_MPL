#include"../inc/lab7_header.h"
#define TIME_SEC 25.61
//extern void GPIO_init();
//extern void max7219_init();
//extern void Display();
extern void MAX7219Send(unsigned char address, unsigned char data);
/*Use GPIOB 3,4,5 as output mode*/
void GPIO_init()
{
	/**/
	RCC->AHB2ENR = RCC->AHB2ENR & (~RCC_AHB2ENR_GPIOBEN_Msk);
	RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE3_Msk);
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE3_0;
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED3_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED3_1;
	/**/
}

void seven_segment_blank(int num_digts)
{
	for(unsigned int i=0 ; i<num_digts; i++)
	{
		MAX7219Send(i+1,0x0FU);
	}
}


void max7219_init()
{
	/*Port 3,4,5 as output mode*/
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE3_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE4_Msk);
	GPIOB->MODER = GPIOB->MODER & (~GPIO_MODER_MODE5_Msk);
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE3_0;
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE4_0;
	GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE5_0;
	/**/
	/*Ports 3,4,5 as output high speed mode*/
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED3_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED4_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED5_Msk);
	GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED3_1;
	GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED4_1;
	GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED5_1;
	/**/
	MAX7219Send(0x0CU,0x01U);
	MAX7219Send(0x0FU,0x00U);
	MAX7219Send(0x09U,0xFFU);
	MAX7219Send(0x0BU,0x07U);
	MAX7219Send(0x0AU,0x09U);
	seven_segment_blank(2);
}

void Timer_init( TIM_TypeDef *timer)
{
	RCC->APB1ENR1 = RCC->APB1ENR1 & (~RCC_APB1ENR1_TIM2EN_Msk);
	RCC->APB1ENR1 = RCC->APB1ENR1 | RCC_APB1ENR1_TIM2EN;
	TIM2->CR1 = TIM2->CR1 & (~TIM_CR1_DIR_Msk);
	TIM2->PSC = TIM2->PSC & (~TIM_PSC_PSC_Msk);
	TIM2->PSC = TIM2->PSC | (39999U);
	TIM2->ARR = TIM2->ARR & (~TIM_ARR_ARR_Msk);
	TIM2->ARR = TIM2->ARR | (99U);
	TIM2->EGR = TIM2->EGR & (~TIM_EGR_UG_Msk);
	TIM2->EGR = TIM2->EGR | (1U << TIM_EGR_UG_Pos);
	return;
}

void Timer_start(TIM_TypeDef *timer)
{
	//TODO: start timer and show the time on the 7-SEG LED.
	TIM2->CR1 = TIM2->CR1 & (~TIM_CR1_CEN_Msk);
	TIM2->CR1 = TIM2->CR1 | (1U << TIM_CR1_CEN_Pos);
	TIM2->SR = TIM2->SR & (~TIM_SR_UIF);
	return;
}

void float_display(int second, int one_percent_second)
{
	unsigned int address = 0x01U;
	MAX7219Send(address++, one_percent_second % 10);
	one_percent_second /= 10;
	MAX7219Send(address++, one_percent_second % 10);
	MAX7219Send(address++, (second % 10) | 0x80U);
	second /= 10;
	while(second % 10)
	{
		MAX7219Send(address++, second % 10);
		second /= 10;
	}
	return;
}

int main()
{
	int expect_second = ((int)TIME_SEC / 1);
	int expect_one_percent_second = (TIME_SEC * 100 - expect_second * 100);
	int second = 0;
	int polling_CNT;
	GPIO_init();
	max7219_init();
	seven_segment_blank(8);
	Timer_init(TIM2);
	Timer_start(TIM2);
	while(1)
	{
		if(TIME_SEC < 0.01 || TIME_SEC > 10000.0)
		{
			float_display(0, 0);
			break;
		}
		//TODO: Polling the timer count and do lab requirements
		polling_CNT = TIM2->CNT;
		float_display(second, polling_CNT);
		/*************************************************************************************************************
		 * Since it use polling, we need to display again in that if block to archive the the requested output       *
		 * If no polling, then it's ok not to display again since timer is running even at the execution of line 120,* * there may be some deviation.																				 *
		 *************************************************************************************************************/
		polling_CNT = TIM2->CNT;
		if(second == expect_second && polling_CNT == expect_one_percent_second)
		{
			float_display(second, polling_CNT);
			break;
		}
		polling_CNT = TIM2->CNT;
		float_display(second, polling_CNT);
		if(TIM2->SR & TIM_SR_UIF)
		{
			second++;
			TIM2->SR = TIM2->SR & (~TIM_SR_UIF);
		}
		polling_CNT = TIM2->CNT;
		float_display(second, polling_CNT);
	}
	return 0;
}
