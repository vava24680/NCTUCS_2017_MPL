	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	user_stack: .zero 128
	expr_result: .word 0
.text
	.global main
	postfix_expr: .asciz "100 10 20 + - 10 +"

main:
	ldr r0,=postfix_expr
	movs r1,#0 //Counter
	movs r2,#0 //Operand
	movs r4,#10
	//TODO: Setup stack pointer to end of user_stack and calculate the
	//expression using PUSH, POP operators, and store the result into
	read:
	ldrb r3,[r0,r1]
	add r1,r1,#1
	//expr_result
	//TODO: Setup stack pointer to end of user_stack and calculate the
	//expression using PUSH, POP operators, and store the result into
	//expr_result
	b atoi
program_end:
	B program_end

atoi:
	//TODO: implement a “convert string to integer” function
	mov r2,r3
	read_int:
	ldrb r3,[r0,r1]
	add r1,r1,#1
	cmp r3,#0x20//0x20 is space
	beq read
	mul r2,r2,r4
	adds r2,r2,r3
	b read_int
