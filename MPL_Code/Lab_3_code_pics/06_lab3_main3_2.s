	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	result: .word 0
	max_size: .word 0
	user_stack: .zero 1024
.text
	.global main
	m: .word 0x5E
	n: .word 0x60

Program_end:
	nop
	b Program_end

main:
	ldr r0,=m
	ldr r1,=n
	ldr r2,[r0]
	ldr r3,[r1]

	ldr r0,=1//Use to store the GDB result
	ldr r1,=0//Use to record the max size using by stack
	ldr r10,=user_stack //Stack Limit
	adds r9,r10,#1024 //Stack Base
	msr msp,r9

	/*----------------------*/
	push {r2,r3}
	/*Push neccessary parameter into stack*/
	bl GCD
	ldr r4,=max_size
	ldr r5,=result
	str r1,[r4]
	str r0,[r5]
	b Program_end

//TODO: Implement your GCD function
GCD:
	ldr r4, [sp]
	ldr r5, [sp,#4]


	cmp r4,r5//two operands are the same
	ITTTT EQ
		mrseq r2,msp
		subeq r1,r9,r2
		muleq r0,r0,r4
		bxeq lr

	cmp r4,#0
	ITTTT EQ
		mrseq r2,msp
		subeq r1,r9,r2
		muleq r0,r0,r5
		bxeq lr

	cmp r5,#0
	ITTTT EQ
		mrseq r2,msp
		subeq r1,r9,r2
		muleq r0,r0,r4
		bxeq lr

	ands r6,r4,#1
	ands r7,r5,#1
	lsl r8,r6,1
	orr r8,r8,r7//r8 could be 00,01,10,11

	cmp r8,#0//Both Even
		ITTT EQ
			asreq r4,r4,1
			asreq r5,r5,1
			lsleq r0,r0,1

	cmp r8,#1//r4->even r5->odd
		IT EQ
			asreq r4,r4,1

	cmp r8,#2//r4->odd r5->even
		IT EQ
			asreq r5,r5,1

	cmp r8,#3//Both Odd
		ITT EQ
		pusheq {r4,r5,lr}
		bleq Adjust
	cmp r8,#3
		IT EQ
		popeq {r4,r5,lr}

	mov r2, r4
	mov r3, r5
	push {r2,r3,lr}
	bl GCD
	pop {r2,r3,lr}
	bx lr

Adjust:
	ldr r2,[sp]
	ldr r3,[sp,#4]
	cmp r2,r3
	ITTEE GE
		subge r2,r2,r3
		asrge r2,1
		sublt r3,r3,r2
		asrlt r3,1
	str r2,[sp]
	str r3,[sp,#4]
	bx lr
