	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	user_stack .zero 128
	expr_result .word 0
.text
	.global main
	postfix_expr .asciz “-100 10 20 + - 10 +”


main:
	LDR R0, =postfix_expr
	//TODO: Setup stack pointer to end of user_stack and calculate the
	expression using PUSH, POP operators, and store the result into

	expr_result

program_end:
	B program_end

atoi:
	//TODO: implement a “convert string to integer” function
	BX LR