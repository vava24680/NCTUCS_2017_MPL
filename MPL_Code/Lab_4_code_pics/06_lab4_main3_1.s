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

GPIO_init:
	//RCC_AHB2ENR enable
	movs r0, #0x1
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
	MOVS R1, #1
	LDR R0, =leds
	STRB R1, [R0]
	Loop:
	//TODO: Write the display pattern into leds variable