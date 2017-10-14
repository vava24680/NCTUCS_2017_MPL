	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	result: .word 0
	max_size: .word 0
	user_stack: .zero 128
.text
	.global main
	m: .word 0x5E
	n: .word 0x60
main:
	ldr r0,=m
	ldr r1,=n
	ldr r2,[r0]
	ldr r3,[r1]
	/*Deal with m==n,m=0,n=0*/
	/*eors r4,r2,r3//m and n are the same
		streq r2,[r0]
		beq Program_end
	cmp r2,#0
		streq r3,[r0]
		beq Program_end
	cmp r3,#0
		streq r2,[r0]
		beq Program_end*/
	ldr r0,=0//Use to store the GDB result
	ldr r1,=0//Use to record the max size using by stack
	ldr r10,=user_stack //Stack Limit
	adds r9,r10,#128 //Stack Base
	msr MSP,r9
	subs r6,r9,#4
	/*----------------------*/
	push {r2,r3}
	/*Push neccessary parameter into stack*/
	bl GCD
	ldr r4,=max_size
	ldr r5,=result


	b Program_end

GCD:
	//pop {r4,r5}
	ldr r4, [sp]
	ldr r5, [sp,#4]

	TEQ r4,r5//two operands are the same
	ITT EQ
		moveq r0,r4
		bxeq lr

	cmp r4,#0
	ITT EQ
		moveq r0,r5
		bxeq lr

	cmp r5,#0
	ITT EQ
		moveq r0,r4
		bxeq lr

	ands r6,r4,#1
	ands r7,r5,#1
	lsl r8,r6,1
	orr r8,r8,r7//r8 could be 00,01,10,11

	cmp r8,#0//Both Even
		ITT EQ
			asreq r4,r4,1
			asreq r5,r5,1

	cmp r8,#1//r4->even r5->odd
		IT EQ
			asreq r4,r4,1

	cmp r8,#2//r4->odd r5->even
		IT EQ
			asreq r5,r5,1

	cmp r8,#3//Both Odd
		IET EQ
			bne GCD_RECURSIVE
			cmpeq r4,r5
				ITTEE GE
					subge r4,r4,r5
					asrge r4,r4,1
					sublt r5,r5,r4
					asrlt r5,r5,1
GCD_RECURSIVE:
	push {r4,r5,lr}
	bl GCD
	pop {r4,r5,lr}
	bx lr

Program_end:
	nop
	b Program_end
//TODO: Implement your GCD function
