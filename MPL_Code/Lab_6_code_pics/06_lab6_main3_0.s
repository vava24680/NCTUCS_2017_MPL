	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	user_stack: .zero 128
.text
	.global GPIO_init
	.global MAX7219_init
	.global MAX7219Send
	.equ RCC_AHB2ENR, 0x4002104C
	.equ GPIOB_MODER, 0x48000400
	.equ GPIOB_OTYPER, 0x48000404
	.equ GPIOB_OSPEEDR, 0x48000408
	.equ GPIOB_PURDR, 0x4800040C
	.equ GPIOB_ODR, 0x48000414
GPIO_init:
	//TODO: Initialize three GPIO pins as output for max7219 DIN, CS and CLK
	//RCC_AHB2ENR enable
	movs r0, #0x2
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
	bx lr

MAX7219_init:
	//TODO: Initialize max7219 registers
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
	//ldr r1,=#0x09000000
	DECODE_INIT:
		ldr r0,=#0x09
		ldr r1,=#0xff
		bl MAX7219Send

	//ldr r0,=#16
	//ldr r1,=#0x0B000000
	SCANLIMIT_INIT:
		ldr r0,=#0x0B
		ldr r1,=#0x06
		bl MAX7219Send

	//ldr r0,=#16
	//ldr r1,=#0x0A090000
	INTERNSITY_INIT:
		ldr r0,=#0x0A
		ldr r1,=#0x09
		bl MAX7219Send

	pop {lr}
	bx lr

MAX7219Send:
	//input parameter: r0 is ADDRESS , r1 is DATA
	//TODO: Use this function to send a message to max7219
	push {r0-r5}
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
	pop {r0-r5}
	bx lr
