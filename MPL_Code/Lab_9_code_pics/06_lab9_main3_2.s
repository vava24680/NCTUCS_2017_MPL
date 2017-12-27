	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	user_stack: .zero 128
.text
	.global STACK_INIT
	.global user_press_button
	.equ GPIOC_IDR, 0x48000810
STACK_INIT:
	ldr r0, =user_stack
	add r0,r0,#128
	msr psp,r0
	bx lr
user_press_button:
	nop
	nop
	nop
	nop
	push {r4-r9}
	ldr r0, =#0x0
	ldr r4, =GPIOC_IDR
	ldr r1,=#250000
	ldr r6,=#0xFFFFFFFF
	ldr r7,=#0x0
	Check:
	/*Get the input value*/
		ldr r5, [r4] //2
		lsr r5,r5,13 //2
		and r5,r5,#0x00000001 //1
	/*-------------------*/
	/*Push the input value into Chech Register(R6)*/
		lsl r6,r6,1 //1
		orr r6,r6,r5 //1
	/*--------------------------------------------*/
	/*State Changing and Checking*/
		cmp r7,#1 //1
		IT EQ
			addeq r7,r7,r5
		cmp r7,#2 //1
		ITTT EQ
			ldreq r0, =0x1
			popeq {r4-r9}
			bxeq lr
		cmp r7,#0
		IT EQ
			cmpeq r6,#0
			IT EQ
				moveq r7,#1
	sub r1,r1,#1
	cmp r1,#0
	bne Check
	/*---------------------------*/
	pop {r4-r9}
	bx lr