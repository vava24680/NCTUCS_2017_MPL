#include <stdio.h>
#include <string.h>
#define PLUS 0
#define MINUS 1
#define MUL 2
#define DIV 3
#define ASSIGN 4
int opd_stack[1000];
int opr_stack[1000];
int opd_stackp=-1;
int opr_stackp=-1;
int opr_precedence[5]={1,1,2,2,0};
int pop(int* stack, int* stack_p)
{
	return stack[(*stack_p)--];
}

void push(int* stack, int* stack_p, int data)
{
	stack[++(*stack_p)] = data;
}
void plus()
{
	int opd_1 = pop(opd_stack, &opd_stackp);
	int opd_2 = pop(opd_stack, &opd_stackp);
	push(opd_stack, &opd_stackp, opd_1 + opd_2);
}

void minus()
{
	int opd_1 = pop(opd_stack, &opd_stackp);
	int opd_2 = pop(opd_stack, &opd_stackp);
	push(opd_stack, &opd_stackp, opd_2 - opd_1);
}

void mul()
{
	int opd_1 = pop(opd_stack, &opd_stackp);
	int opd_2 = pop(opd_stack, &opd_stackp);
	push(opd_stack, &opd_stackp, opd_1 * opd_2);
}

void div()
{
	int opd_1 = pop(opd_stack, &opd_stackp);
	int opd_2 = pop(opd_stack, &opd_stackp);
	push(opd_stack, &opd_stackp, opd_2 / opd_1);
}

int compare(int opr)
{
	//opr pop
	if(opr_stackp==-1)
		return 0;
	//stack is not empty
	int pre_opr = opr_stack[opr_stackp];
	if(opr_precedence[opr] <= opr_precedence[pre_opr])
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
	switch (opr) {
		case 0:
			plus();
			break;
		case 1:
			minus();
			break;
		case 2:
			mul();
			break;
		case 3:
			div();
			break;
	}
}

int main(void)
{
	char input[]="123+456-111*5+3=";
	int number = 0;
	int i=0;
	int result = 0;
	int digit = 0;
	do{
		if(input[i]>='0' && input[i]<='9')
		{
			if(digit<3)
			{
				//Only 3 digits
				//Display on the MAX7219
				//Clear the last operator variable
				number *= 10;
				number += (input[i]-'0');
				digit++;
			}
		}
		else
		{
			digit = 0;
			//Check last operator
			//Clear MAX7219
			push(opd_stack, &opd_stackp, number);
			number = 0;
			int operator = input[i];
			switch (operator){
				case '+':
					operator = PLUS;
					break;
				case '-':
					operator = MINUS;
					break;
				case '*':
					operator = MUL;
					break;
				case '/':
					operator = DIV;
					break;
				case '=':
					operator = ASSIGN;
					break;
			}
			while(compare(operator))
			{
				int pre_opr = pop(opr_stack, &opr_stackp);
				calculation(pre_opr);
			}
			if(operator==ASSIGN)
			{
				result = pop(opd_stack, &opd_stackp);
				break;
			}
			push(opr_stack, &opr_stackp, operator);
		}
		i++;
	} while(1);
	printf("Result is %d\n", result);
	return 0;
}
