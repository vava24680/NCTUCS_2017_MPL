	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	user_stack: .zero 128
	leds: .byte 0
	password: .byte 6
.text
	.global main
	.equ RCC_AHB2ENR, 0x4002104C
	.equ GPIOB_MODER, 0x48000400
	.equ GPIOB_OTYPER, 0x48000404
	.equ GPIOB_OSPEEDR, 0x48000408
	.equ GPIOB_PURDR, 0x4800040C
	.equ GPIOB_IDR, 0x48000410
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
	ldr r2,=#0b11111111110000000000000000111111
	and r1,r1,r2
	orr r1,r1, #0b00000000000000000001010101000000
	str r1,[r0]

	/*GPIOB Speed setting*/
	ldr r0, =GPIOB_OSPEEDR
	ldr r1,[r0]
	and r1,r1, #0b11111111111111111100000000111111
	orr r1,r1, #0b00000000000000000010101010000000
	str r1,[r0]

	/*GPIOB Pull-Up Setting for DIP Switch*/
	ldr r0, =GPIOB_PURDR
	ldr r1,[r0]
	and r1,r1, #0b11111111110000000011111111111111
	orr r1,r1, #0b00000000000101010100000000000000
	str r1,[r0]

	/*GPIOC Mode Setting*/
	ldr r0, =GPIOC_MODER
	ldr r1,[r0]
	and r1,r1, #0b11110011111111111111111111111111
	orr r1,r1, #0x0
	str r1,[r0]
	bx lr
	/*GPIOA Mode Setting*/


main:
	BL GPIO_init
	ldr r0, =GPIOB_ODR
	ldr r1, =#0xFFFFFFFF
	strh r1,[r0]
	ldr r6,=#0xFFFFFFFF
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
		ITTT EQ
			ldreq r2,=#0xFFFFFF78 //Code for LED not lighting
			moveq r7,#0
			beq Check
		cmp r7,#0
		IT EQ
			cmpeq r6,#0
			IT EQ
				moveq r7,#1
	b Debounce

Check:
	/*Read the data from DIP Switch*/
	//ldr r4, =#0x00000005
	ldr r5, =GPIOB_IDR
	ldr r4,[r5]
	lsr r4,r4,7
	and r4,r4,0x0000000F
	/*-----------------------------*/
	/*Check Equality*/
	ldr r5, =password
	ldr r6,[r5]
	cmp r6,r4
	ITE EQ
		moveq r0,#6
		movne r0,#2

Loop:
	BL DisplayLED
	BL Delay
	sub r0,r0,#1
	cmp r0,#0
	beq Debounce
	bne Loop

DisplayLED:
	mvn r2,r2
	ldr r1, =GPIOB_ODR
	strh r2,[r1]
	bx lr

Delay:
	ldr r3,=#710
	L1: ldr r4,=#710
	L2: subs r4,#1
	bne L2
	subs r3,#1
	bne L1
	bx lr
