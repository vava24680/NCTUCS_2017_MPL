#include"../inc/lab6_header.h"
//TODO: define your gpio pin
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
/* TODO: initial keypad gpio pin, X as output and Y as input
*/

const int match_matrix[4][4]={
	{1,2,3,10},
	{4,5,6,11},
	{7,8,9,12},
	{0,0,0,13}
};

int button_state[4][4]={
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
};

/*Open GPIOB*/
extern void MAX7219Send(unsigned char address, unsigned char data);
extern void STACK_INIT();
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

void clear_seven_segment_all()
{
	seven_segment_blank(8);
}
/*Use GPIOB 3,4,5 as output mode*/
void seven_segment_int()
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

void keypad_init()
{
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
	/**/
	GPIOB->PUPDR = GPIOB->PUPDR & (~GPIO_PUPDR_PUPD12_Msk);
	GPIOB->PUPDR = GPIOB->PUPDR & (~GPIO_PUPDR_PUPD13_Msk);
	GPIOB->PUPDR = GPIOB->PUPDR & (~GPIO_PUPDR_PUPD14_Msk);
	GPIOB->PUPDR = GPIOB->PUPDR & (~GPIO_PUPDR_PUPD15_Msk);
	GPIOB->PUPDR = GPIOB->PUPDR | GPIO_PUPDR_PUPD12_1;
	GPIOB->PUPDR = GPIOB->PUPDR | GPIO_PUPDR_PUPD13_1;
	GPIOB->PUPDR = GPIOB->PUPDR | GPIO_PUPDR_PUPD14_1;
	GPIOB->PUPDR = GPIOB->PUPDR | GPIO_PUPDR_PUPD15_1;
}

void display(int display_number)
{
	//clear_seven_segment_all();
	uint32_t address = 0x01;
	int remainder;
	int flag=0;
	if(display_number<0)
	{
		display_number*=(-1);
		flag=1;
	}
	do
	{
		remainder = display_number%10;
		MAX7219Send(address, remainder);
		address++;
		display_number/=10;
	} while(display_number!=0);
	if(flag)
		MAX7219Send(address, 10U);
}
/* TODO: scan keypad value
* return:
* >=0: key pressed value
* -1: no key press
*/
void keypad_scan(void)
{
	int32_t input_value;
	uint32_t mask = 0x00U;//Not Umask
	int32_t total_button_value = 0;
	//MAX7219 blank;
	clear_seven_segment_all();
	while(1)
	{
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
			if(input_value & 0x01U)
			{
				switch (button_state[0][3-i]) {
					case 0:
						button_state[0][3-i] = 1;
						break;
					case 1:
						button_state[0][3-i] = 2;
						break;
					case 2:
						button_state[0][3-i] = 2;
						break;
				}
			}
			else
			{
				button_state[0][3-i] = 0;
			}

			if(input_value & 0x02U)
			{
				switch (button_state[1][3-i]) {
					case 0:
						button_state[1][3-i] = 1;
						break;
					case 1:
						button_state[1][3-i] = 2;
						break;
					case 2:
						button_state[1][3-i] = 2;
						break;
				}
			}
			else
			{
				button_state[1][3-i] = 0;
			}

			if(input_value & 0x04U)
			{
				switch (button_state[2][3-i]) {
					case 0:
						button_state[2][3-i] = 1;
						break;
					case 1:
						button_state[2][3-i] = 2;
						break;
					case 2:
						button_state[2][3-i] = 2;
						break;
				}
			}
			else
			{
				button_state[2][3-i] = 0;
			}

			if(input_value & 0x08U)
			{
				switch (button_state[3][3-i]) {
					case 0:
						button_state[3][3-i] = 1;
						break;
					case 1:
						button_state[3][3-i] = 2;
						break;
					case 2:
						button_state[3][3-i] = 2;
						break;
				}
			}
			else
			{
				button_state[3][3-i] = 0;
			}
			for(int j = 0; j < 4; j++)
			{
				if(button_state[j][3-i] == 1)
				{
					total_button_value += match_matrix[j][3-i];
				}
			}
		}
		if(button_state[3][0] || button_state[3][2])
		{
			clear_seven_segment_all();
			total_button_value = 0;
		}
		display(total_button_value);
	}
}
int main(void)
{
	STACK_INIT();
	Essential_GPIO_init();
	seven_segment_int();
	keypad_init();
	keypad_scan();
	return 0;
}
