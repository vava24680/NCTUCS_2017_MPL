	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	user_stack: .zero 128 //Means there will be 128 bytes all filled in by 0
	expr_result: .word 0
.text
	.global main
	postfix_expr: .asciz "-100 10 20 + - 10 +"
	.align 4
calculation:
	pop {r2,r5} //r5: opd 1, r2: opd 2
	cmp r3,0x2D
	IT EQ
		subeq r5,r5,r2
	IT NE
		addne r5,r5,r2
	push {r5}
	b read

program_end:
	nop
	B program_end

main:
	ldr r0,=postfix_expr
	ldr r1,=user_stack
	add r1,r1,#128
	msr msp,r1
	movs r1,#0 //Counter
	movs r2,#0 //Operand
	movs r4,#10
	//Indicatie positive or negative
	//TODO: Setup stack pointer to end of user_stack and calculate the
	//expression using PUSH, POP operators, and store the result into
read:
	movs r6,#1
	ldrb r3,[r0,r1]
	add r1,r1,#1
	/*CheckPoint 1, Check whether it's a terminate sign*/
	cmp r3,#0
	ITTT EQ
		popeq {r0}
		ldreq r1,=expr_result
		streq r0,[r1]
	beq program_end
	/*-------------------------------------------------*/
	/*CheckPoint 2, Check whether it's a space*/
	cmp r3,#0x20
	beq read
	/*----------------------------------------*/
	/*CheckPoint 3, Check whether it's a negative sign*/
	cmp r3,#0x2D
	ITTT EQ
		ldreq r6,=-1
		ldrbeq r3,[r0,r1]
		addeq r1,r1,#1
		/*CheckPoint 3-1, Check whether it's a space*/
		cmp r3,#0x20
		IT EQ
			ldreq r3,=0x2D
			beq calculation
		cmp r3,#0x0 //Means minus sign is at the end of the expr
		ITT EQ
			ldreq r3,=0x2D
			subeq r1,r1,#1
			beq calculation
	/*------------------------------------------*/
	/*CheckPoint 4, Check whether it's a plus sign*/
	cmp r3,#0x2B
	beq calculation
	/*--------------------------------------------*/
	b atoi
	//expr_result
	//TODO: Setup stack pointer to end of user_stack and calculate the
	//expression using PUSH, POP operators, and store the result into
	//expr_result

atoi:
	//TODO: implement a “convert string to integer” function
	sub r3,r3,#48
	mov r2,r3
	read_int:
	ldrb r3,[r0,r1]
	add r1,r1,#1
	cmp r3,#0x0//0x0 is '\0'
	ITTT EQ
		subeq r1,r1,#1
		muleq r2,r2,r6
		pusheq {r2}
	beq read
	cmp r3,#0x20//0x20 is space
	ITT EQ
		muleq r2,r2,r6
		pusheq {r2}
	beq read
	mul r2,r2,r4
	sub r3,r3,#48
	adds r2,r2,r3
	b read_int
