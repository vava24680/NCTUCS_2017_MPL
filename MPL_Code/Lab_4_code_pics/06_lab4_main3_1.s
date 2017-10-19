	.syntax unified
	.cpu cortex-m4
	.thumb
.data
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
GPIO_init:
	//RCC_AHB2ENR enable
	movs r0, #0x2
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
	bx lr
main:
	BL GPIO_init
	movs r1, #1
	ldr r0, =leds
	strb r1, [R0]
	ldr r2,=GPIOB_ODR
	ldr r5,=#0x0000FFFF
	strb r5,[r2]
	ldr r5,=#0xFFFFFFE7
	mov r6,#-1 //shift direction, 1=>left, -1=>right
Loop:
	BL DisplayLED
	BL Delay
	B Loop

DisplayLED:
	cmp r1,#4
		IT EQ
		rsbeq r6,r6,#0
	cmp r1,#0
		IT EQ
		rsbeq r6,r6,#0

	cmp r6,#1
	ITE EQ
		lsleq r5,r5,1
		asrne r5,r5,1

	and r3,r5,#1
	cmp r3,#0
	IT EQ
		orreq r5,r5,#1
	strb r5,[r2]
	add r1,r1,r6
	str r1,[r0]
	bx lr

Delay:
	ldr r3,=#2000
	L1: ldr r4,=#610
	L2: subs r4,#1
	bne L2
	subs r3,#1
	bne L1
	bx lr
