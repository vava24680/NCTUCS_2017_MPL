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
#define PLUS 0
#define MINUS 1
#define MUL 2
#define DIV 3
#define ASSIGN 4
#define CLEAR 5
unsigned int x_pin[4] = {X0, X1, X2, X3};
unsigned int y_pin[4] = {Y0, Y1, Y2, Y3};

int operand_stack[500];
int operator_stack[500];
int operand_stackp;
int operator_stackp;
int operator_precedence[5]={1,1,2,2,0};
/**********************************/
		/* 10->add */
		/* 11->sub */
		/* 12->mul */
		/* 13->div */
		/* 14->clear */
		/* 15->assign */
/**********************************/
const int match_matrix[4][4]={
	{1,2,3,10},
	{4,5,6,11},
	{7,8,9,12},
	{15,0,14,13}
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

char keypad_scan()
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

void display(int display_number)
{
	clear_seven_segment_all();
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

int pop(int* stack, int* stack_p)
{
	int ptr = (*stack_p);
	int content = stack[ptr];
	ptr--;
	(*stack_p) = ptr;
	return content;
}

void push(int* stack, int* stack_p, int data)
{
	int ptr = (*stack_p);
	ptr++;
	(*stack_p) = ptr;
	stack[ptr] = data;
}

int compare(int opr)
{
	//opr pop
	if(operator_stackp==-1)
		return 0;
	//stack is not empty
	int pre_opr = operator_stack[operator_stackp];
	if(operator_precedence[opr] <= operator_precedence[pre_opr])
	{
		return 1;
	}
	else
	{
		return 0;//Can not do
	}
}

void calculation(int opr)
{
	int opd_1 = pop(operand_stack, &operand_stackp);
	int opd_2 = pop(operand_stack, &operand_stackp);
	switch (opr)
	{
		case 0:
			push(operand_stack, &operand_stackp, opd_2 + opd_1);
			break;
		case 1:
			push(operand_stack, &operand_stackp, opd_2 - opd_1);
			break;
		case 2:
			push(operand_stack, &operand_stackp, opd_2 * opd_1);
			break;
		case 3:
			push(operand_stack, &operand_stackp, opd_2 / opd_1);
			break;
	}
}

int main(void)
{
	STACK_INIT();
	Essential_GPIO_init();
	seven_segment_int();
	keypad_init();
	clear_seven_segment_all();
	int result;
	int keypad_value;
	int last_operator = 0;
	int last_keypad_value;
	int input_number;
	int input_digit;
	while(1)
	{
		/*No reseting the last_operator value since it will cause result on the MAX7219 be zero*/
		operand_stackp = -1;
		operator_stackp = -1;
		last_keypad_value = -1;
		input_number = 0;
		input_digit = 0;
		do{
			keypad_value = keypad_scan();
			if(keypad_value>=0 && keypad_value<=9)
			{
				if(input_digit < 3)//Only 3 input_digits
				{/*(input_number*10)<=999 && (input_number*10)>=0*/
					if(keypad_value != last_keypad_value)
					{
						//Clear the last operator variable
						last_operator = 0;
						input_number *= 10;
						input_number += (keypad_value);
						//Display on the MAX7219
						display(input_number);
						input_digit++;
						last_keypad_value = keypad_value;
					}
				}
			}
			else if(keypad_value>= 10 && keypad_value<=15)
			{
				int operator = keypad_value;
				//Check last operator
				if(operator == last_operator)
					continue;
				else
				{
					push(operand_stack, &operand_stackp, input_number);
					last_keypad_value = -1;
					input_digit = 0;
					input_number = 0;
					last_operator=operator;
				}
				//Clear MAX7219
				clear_seven_segment_all();
				if(operator==14)
				{
					result = 0;
					break;
				}
				switch (operator){
					case 10:
						operator = PLUS;
						break;
					case 11:
						operator = MINUS;
						break;
					case 12:
						operator = MUL;
						break;
					case 13:
						operator = DIV;
						break;
					case 15:
						operator = ASSIGN;
						break;
				}
				while(compare(operator))
				{
					int pre_opr = pop(operator_stack, &operator_stackp);
					calculation(pre_opr);
				}
				if(operator==ASSIGN)
				{
					result = pop(operand_stack, &operand_stackp);
					break;
				}
				push(operator_stack, &operator_stackp, operator);
			}
			else
			{
				/*For the input like 555
				  Without this, user can input 555 since last_keypad_value is same as current keypad value
				  So it will no be shown because of the block of line 272
				*/
				last_keypad_value = -1;
			}
		} while(1);
		display(result);
	}
	return 0;
}
