	.syntax unified
	.cpu cortex-m4
	.thumb
.text
	.global main
	.equ RCC_BASE,0x40021000
	.equ RCC_CR,0x0
	.equ RCC_CFGR,0x08
	.equ RCC_PLLCFGR,0x0c
	.equ RCC_CCIPR,0x88
	.equ RCC_AHB2ENR,0x4C
	.equ RNG_CLK_EN,18

	//Register address for RNG (Random Number Generator)
	.equ RNG_BASE, 0x50060800 //RNG BASE Address
	.equ RNG_CR_OFFSET, 0x00 //RNG Control Register
	.equ RNGEN, 2 //RNG_CR bit 2

	.equ RNG_SR_OFFSET, 0x04 //RNG Status Register
	.equ DRDY,1 //RNG_SR bit 0 original: .equ DRDY,0
	.equ RNG_DR_OFFSET, 0x08 //RNG Data Register (Generated random number!)

	//Data Settings for 3.4.4
	.equ SAMPLE, 1000000
	.equ X32LIMIT, 0x80000000
	.equ ONE,1

set_flag:
	ldr r2,[r0,r1]
	orr r2,r2,r3
	str r2,[r0,r1]
	bx lr

enable_fpu:
	LDR.W r0, =0xE000ED88
	LDR r1, [r0]
	ORR r1, r1, #(0xF << 20)
	STR r1, [r0]
	DSB
	ISB
	bx lr

enable_rng:
	ldr r0, =RNG_BASE
	ldr r1, =RNG_CR_OFFSET
	ldr r3, =4
	ldr r2,[r0]
	orr r2,r2,r3
	str r2,[r0]
	bx lr

get_rand:
	//Your code start from here
	//read RNG_SR
	//check DRDY bit, wait until to 1
	//read RNG_DR for random number and store into a register for later usage
	ldr r0, =RNG_BASE
	ldr r1, =RNG_SR_OFFSET
	ldr r2,[r0,r1] //Get the RNG_SR value
	and r2,r2,#DRDY //r2=r2&1
	cmp r2,#1
	bne get_rand
	ldr r1, =RNG_DR_OFFSET
	ldr r2,[r0,r1] //Get the RNG_DR value
	bx lr

main:
//RCC Settings
	ldr r0,=RCC_BASE
	ldr r1,=RCC_CR
	ldr r3,=#(1<<8) //HSION
	bl set_flag
	ldr r1,=RCC_CFGR
	ldr r3,=#(3<<24) //HSI16 selected
	bl set_flag
	ldr r1,=RCC_PLLCFGR
	ldr r3,=#(1<<24|1<<20|1<<16|10<<8|2<<0)
	bl set_flag
	ldr r1,=RCC_CCIPR
	ldr r3,=#(2<<26)
	bl set_flag
	ldr r1,=RCC_AHB2ENR
	ldr r3,=#(1<<RNG_CLK_EN)
	bl set_flag
	ldr r1,=RCC_CR
	ldr r3,=#(1<<24) //PLLON
	bl set_flag

chk_PLLON:
	ldr r2,[r0,r1]
	ands r2,r2,#(1<<25)
	beq chk_PLLON

/*

*/
//Your code start from here
pre_calculation:
	/*Enable the necessary componet-----*/
		bl enable_rng//Enable FPU,RNG
		bl enable_fpu
	/*--------------------------------*/
	ldr r8,=0
	ldr r6,=0
	ldr r5,=SAMPLE
	ldr r0,=X32LIMIT
	vmov s0,r0
	vcvt.f32.s32 s0,s0
	vabs.f32 s0,s0
	ldr r0,=ONE
	vmov s1,r0
	vcvt.f32.s32 s1,s1

calculate:
	/*Get the two random numbers*/
		bl get_rand
		bl get_rand
		bl get_rand
		bl get_rand
		movs r3,r2
		bl get_rand
		bl get_rand
		bl get_rand
		bl get_rand
		movs r4,r2
	/*--------------------------*/
	/*Normalization*/
		vmov.f32 s2,r3
		vmov.f32 s3,r4
		vcvt.f32.s32 s2,s2
		vcvt.f32.s32 s3,s3
		vabs.f32 s2,s2
		vabs.f32 s3,s3
		vdiv.f32 s2, s2,s0
		vdiv.f32 s3 ,s3,s0
	/*-------------*/
	/*Calculate Distance*/
		vmul.f32 s2,s2,s2
		vmul.f32 s3,s3,s3
		vadd.f32 s4,s2,s3
		//vsqrt.f32 s4,s4
	/*------------------*/
	/*Check if point is in the circle*/
		vcmp.f32 s4,s1 //s1=1.0000, s4 is the distance from point to origin.
		VMRS APSR_nzcv, FPSCR
		IT MI
		addmi r6,r6,#1
	/*-------------------------------*/
	subs r5,r5,#1
	bgt calculate
	nop
	ldr r5,=4
	vmov.f32 s5,r5
	vcvt.f32.s32 s5,s5
	vmov.f32 s6,r6
	vcvt.f32.s32 s6,s6
	vmul.f32 s6,s6,s5

	ldr r5,=SAMPLE
	vmov.f32 s5,r5
	vcvt.f32.s32 s5,s5
	vdiv.f32 s6,s6,s5
	nop
	nop
//Generate 2 random U32 number x,y
//Map x,y in unit range [0,1] using FPU
//Calculate the z=sqrt(x^2+y^2) using FPU
//Show the result of z in your report

L: b L
