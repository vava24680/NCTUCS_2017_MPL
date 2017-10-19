	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	user_stack: .zero 128
	leds: .byte 0
.text
	.global main
	.equ RCC_AHB2ENR, 0x4002104C
	.equ GPIOB_MODER, 0x48000400
	.equ GPIOB_OTYPER, 0x48000404
	.equ GPIOB_OSPEEDR, 0x48000408
	.equ GPIOB_PURDR, 0x4800040C
	.equ GPIOB_ODR, 0x48000414
	.equ GPIOB_BSRR, 0x48000418

	.equ GPIOC_MODER, 0x48000800
	.equ GPIOC_OTYPER, 0x48000804
	.equ GPIOC_OSPEEDR, 0x48000808
	.equ GPIOC_PURDR, 0x4800080C
	.equ GPIOC_IDR, 0x48000810
GPIO_init:
	//RCC_AHB2ENR enable
	movs r0, #0x6
	ldr r1, =RCC_AHB2ENR
	str r0, [r1]

	/*GPIOB Mode setting*/
	ldr r0, =GPIOB_MODER
	ldr r1,[r0]
	ands r1,r1, #0b11111111111111111100000000111111
	orrs r1,r1, #0b00000000000000000001010101000000
	str r1,[r0]

	/*GPIOB Speed setting*/
	ldr r0, =GPIOB_OSPEEDR
	ldr r1,[r0]
	ands r1,r1, #0b11111111111111111100000000111111
	orrs r1,r1, #0b00000000000000000010101010000000
	str r1,[r0]

	/*GPIOC Mode Setting*/
	ldr r0, =GPIOC_MODER
	ldr r1,[r0]
	ands r1,r1, #0b11110011111111111111111111111111
	orrs r1,r1, #0x0
	str r1,[r0]
	bx lr
/*Global Register Usage
 *R6:Check Register for Debouncing
 *R7:Current State of Debounce Finite State Machine
 *R8:Current State of LED Finite State Machine
 */

/*LED Finite State Machine
 *Two State
 *0=>LED Running State(Default State)
 *1=>LED Stop State
 */

main:
	BL GPIO_init
	/*Stack Initilization*/
		ldr r0, =user_stack
		add r0,r0,#128
		msr msp,r0
	/*-------------------*/
	/*Finite State Initilization*/
		ldr r6,=#0xFFFFFFFF
		mov r7,#0
		mov r8,#1
	/*--------------------------*/
	/*DisplayLED Initilization*/
		mov r2, #1
		ldr r0, =leds
		strb r2, [R0]
		ldr r1,=GPIOB_ODR
		ldr r3,=#0x0000FFFF
		strb r3,[r1]
		ldr r3,=#0xFFFFFFE7
		mov r4,#-1 //shift direction, 1=>left, -1=>right
		push {r0-r4}
	/*------------------------*/
Loop:
	BL DisplayLED
	BL Delay
	B Loop

DisplayLED:
	/*Using Current State to Change what LED will do*/
	cmp r8,#1
	IT NE
		bne Delay
	/*----------------------------------------------*/
	pop {r0-r4}
	cmp r2,#4
		IT EQ
		rsbeq r4,r4,#0
	cmp r2,#0
		IT EQ
		rsbeq r4,r4,#0

	cmp r4,#1
	ITE EQ
		lsleq r3,r3,1
		asrne r3,r3,1

	push {r0}
		and r0,r3,#1
		cmp r0,#0
		IT EQ
			orreq r3,r3,#1
	pop {r0}

	strb r3,[r1]
	add r2,r2,r4
	str r2,[r0]

	push {r0-r4}
	bx lr

Delay:
	ldr r1,=#350000
	ldr r0, =GPIOC_IDR
	Check:
	/*Get the input value*/
		ldr r5, [r0] //2
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
			rsbeq r8,r8,#0
			moveq r7,#0
			beq DisplayLED
		//bne Check
		cmp r7,#0
		IT EQ
			cmpeq r6,#0
			IT EQ
				moveq r7,#1
	sub r1,r1,#1
	cmp r1,#0
	bne Check
	/*---------------------------*/
	bx lr
