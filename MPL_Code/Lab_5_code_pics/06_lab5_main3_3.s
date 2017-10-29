	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	user_stack: .zero 256
.text
	.global main
	.equ RCC_AHB2ENR, 0x4002104C
	.equ GPIOB_MODER, 0x48000400
	.equ GPIOB_OTYPER, 0x48000404
	.equ GPIOB_OSPEEDR, 0x48000408
	.equ GPIOB_PURDR, 0x4800040C
	.equ GPIOB_ODR, 0x48000414

	.equ GPIOC_MODER, 0x48000800
	.equ GPIOC_OTYPER, 0x48000804
	.equ GPIOC_OSPEEDR, 0x48000808
	.equ GPIOC_PURDR, 0x4800080C
	.equ GPIOC_IDR, 0x48000810
GPIO_init:
	//TODO: Initialize three GPIO pins as output for max7219 DIN, CS and CLK
	//RCC_AHB2ENR enable
	movs r0, #0x6
	ldr r1, =RCC_AHB2ENR
	str r0, [r1]

	/*GPIOB Mode setting*/
	ldr r0, =GPIOB_MODER
	ldr r1,[r0]
	ands r1,r1, #0b11111111111111111111000000111111
	orrs r1,r1, #0b00000000000000000000010101000000
	str r1,[r0]

	/*GPIOB Speed setting*/
	ldr r0, =GPIOB_OSPEEDR
	ldr r1,[r0]
	ands r1,r1, #0b11111111111111111111000000111111
	orrs r1,r1, #0b00000000000000000000101010000000
	str r1,[r0]

	/*GPIOC Mode Setting*/
	ldr r0, =GPIOC_MODER
	ldr r1,[r0]
	ands r1,r1, #0b11110011111111111111111111111111
	orrs r1,r1, #0x0
	str r1,[r0]
	bx lr

MAX7219_init:
	//TODO: Initial max7219 registers.
	push {lr}
	ldr r3,=GPIOB_ODR

	//ldr r0,=#16
	//ldr r1,=#0x0C010000
	SHUTDOWN_INIT:
		ldr r0,=#0x0C
		ldr r1,=#0x01
		bl MAX7219Send

	//ldr r0,=#16
	//ldr r1,=#0x0F000000
	TEST_INIT:
		ldr r0,=#0x0F
		ldr r1,=#0x00
		bl MAX7219Send

	//ldr r0,=#16
	//ldr r1,=#0x09ff0000
	DECODE_INIT:
		ldr r0,=#0x09
		ldr r1,=#0xFF
		bl MAX7219Send

	//ldr r0,=#16
	//ldr r1,=#0x0B060000
	SCANLIMIT_INIT:
		ldr r0,=#0x0B
		ldr r1,=#0x07
		bl MAX7219Send

	//ldr r0,=#16
	//ldr r1,=#0x0A090000
	INTERNSITY_INIT:
		ldr r0,=#0x0A
		ldr r1,=#0x09
		bl MAX7219Send

	pop {lr}
	bx lr

MAX7219_Blank:
	/*Function Usage
	 *r0 is the ADDRESS of first digit is going to be blank ,
	 *so each digit above will be blank too.
	 */
	push {r4-r7}
	/*cmp r0,#9
	ITT GE
		popge {r4-r7}
		bxge lr*/
	push {r0,lr}
	ldr r1,=#0xf //CODE B format for "blank"
	LoopReset:
		bl MAX7219Send
		add r0,r0,#1
		cmp r0,#9
		blt LoopReset
	pop {r0,lr}
	pop {r4-r7}
	bx lr

MODULO:
	/*Find the modulo*/
	/*
	 *r1 will carry the parameter in and also pass the remainder back
	 *r2 will pass the value of r1/10
	*/
	mov r4, r1
	ldr r5, =#10
	udiv r6, r4, r5 //r6 is quotient
	mls r1, r6, r5, r4 //r0=r4-r6*r5
	mov r2,r6
	bx lr

main:
	bl GPIO_init
	ldr r0, =user_stack
	add r0,r0,#256
	msr msp,r0
	bl MAX7219_init
	ldr r0,=#0x1
	bl MAX7219_Blank
	nop
	nop
	/*Register usage in INITITAL, LOOP
	 *r0 : store fib parameter
	 *r1 : store fib(r0),   default value is 0
	 *r2 : store fin(r0-1), default value is 0
	 *r3 : Counter for timing
	 *r6 : Store current 32 times button value
	 *r7 : Current state, default is 0
	*/
	INITITAL:
		ldr r0,=#0x1
		ldr r1,=#0x0
		bl MAX7219Send
		ldr r0,=#0x0
		ldr r1,=#0x0
		ldr r2,=#0x0
		ldr r7,=#0x0
	LOOP:
		ldr r3,=#250000
		ldr r6,=#0xFFFFFFFF
		bl Debounce
		cmp r7,#2
			ITTT EQ
				addeq r0, r0, #1
				pusheq {r4-r8}
				bleq Fib
				/*Since the instruction limit, pop is at the end of Fib function*/
		cmp r7,#2
			IT EQ
				bleq OutputMAX7219
		/*cmp r7,#4
		ITTT EQ
			ldreq r0,=#0x1
			ldreq r1,=#0x0
			bleq MAX7219Send
		cmp r7,#4
		ITT EQ
			ldreq r0,=#0x2
			bleq MAX7219_Blank*/
		cmp r7,#4
			beq INITITAL
		ldr r7,=#0x0
		b LOOP

/*Register usage in Debounce
 *r3 : Counter for timing
 *r4 : ADDRESS of GPIOC_IDR
 *r5 : button value(1 bit)
 *r6 : Store current 32 times button value
 *r7 : Current state, default is 0
*/
Debounce:
	ldr r4, =GPIOC_IDR
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
		IT EQ
			bxeq lr
		cmp r7,#3
		ITTTT EQ
			pusheq {lr}
			ldreq r0,=#0x1
			ldreq r1,=#0x0
			bleq MAX7219Send
		cmp r7,#3
		ITTT EQ
			addeq r0,r0,#1
			ldreq r1,=#0xF
			bleq MAX7219_Blank
		cmp r7,#3
		ITT EQ
			popeq {lr}
			addeq r7,r7,r5
		cmp r7,#4
		IT EQ
			bxeq lr
		cmp r7,#0
		IT EQ
			cmpeq r6,#0
			IT EQ
				moveq r7,#1
	subs r3,r3,#1
	bgt Debounce
	/*When executing this code segment, r7 will be 0 or 1*/
	cmp r7,#0 /*button is not pushed more than one second, let it re-debounce*/
		IT EQ
			ldreq r3,=#250000
	cmp r7,#1 /*button is pushed more than one second, change to new-state r3*/
		ITT EQ
			ldreq r3,=#250000
			moveq r7,#3
	/*---------------------------------------------------*/
	b Debounce

/*Register usage in OutputMAX7219
 *r0 : digit ADDRESS
 *r1 : the value pass to MODULO and return the remainder
 *r1 : So it's also CODE B encoding value with current digit pass to MAX7219Send
 *r2 : Quotient of the value which be passed to MODULO
 *r3 : AND value of quotient and remainder
 *r4 : Clone of current fib value, comparing user_stack
 *r5 : Constant 100000000
*/
OutputMAX7219:
	push {r0-r8,lr}
	ldr r0,=#0x0
	mov r4,r1
	ldr r5,=#100000000
	cmp r4,r5
	ITTT GE
		addge r0,r0,#1
		ldrge r1,=#0x1 //CODE B format for "One"
		blge MAX7219Send
	cmp r4,r5
	ITTT GE
		addge r0,r0,#1
		ldrge r1,=#0xA //CODE B format for "-"
		blge MAX7219Send
	cmp r4,r5
	ITTT GE
		addge r1,r5,#1
		addge r0,r0,#1
		blge MAX7219_Blank
	cmp r4,r5
	ITT GE
		popge {r0-r8,lr}
		bxge lr

	Compute_Modulo:
		bl MODULO
		orr r3,r1,r2
		cmp r3,#0
			ITT NE
				addne r0,r0,#1
				blne MAX7219Send
		/*cmp r3,#0
			ITT EQ
				addeq r0,r0,#1
				bleq MAX7219_Blank*/
		cmp r3,#0
			IT NE
			movne r1,r2
			bne Compute_Modulo
	pop {r0-r8,lr}
	bx lr

Fib:
	/*
	 *For case that push button again after the value has exceded 100000000
	 *, force it to return.
	*/
	ldr r4,=#100000000
	cmp r1,r4
	IT GE
		bxge lr
	/*---------------------------------------------------------------------*/
	cmp r0,#1
	IT EQ/*For the initial case, that is N=1*/
		ldreq r1,=#1
	ITTT NE
		movne r4,r1
		addne r1,r1,r2
		movne r2,r4
	pop {r4-r8}
	bx lr

MAX7219Send:
	push {r0-r7}
	//input parameter: r0 is ADDRESS , r1 is DATA
	//TODO: Use this function to send a message to max7219
	lsl r4,r0,8
	orr r4,r4,r1
	lsl r4,r4,16
	push {r0,r1}

	ldr r2,=#16
	ldr r3,=GPIOB_ODR
	SEND:
		and r0,r4,#0x80000000
		lsr r0,r0,28
		ldr r1, [r3]
		and r1,r1,#0xFFFFFFF7
		orr r1,r1,r0
		strh r1, [r3]

		orr r1,r1,#0b100000
		strh r1, [r3]

		and r1,r1,#0xFFFFFFDF
		strh r1, [r3]

		sub r2,r2,#1
		lsl r4,r4,1
		cmp r2,#0
			bne SEND
		orr r1,r1,0b10000
		strh r1,[r3]

		and r1,r1,#0xFFFFFFEF
		strh r1, [r3]
	pop {r0,r1}
	pop {r0-r7}
	bx lr
