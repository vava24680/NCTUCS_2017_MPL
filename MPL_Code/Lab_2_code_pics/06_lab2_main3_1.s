	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	address: .int 0//For storing the return address in mem
	result: .byte 0
.text
	.global main
	.equ X, 0x55AA
	.equ Y, 0xAA55
	.equ FIRST_BIT,0b1000000000000000

/* Register Usage
	r0: Stroing X
	r1: Stroing Y
	r2: address for variable result
	r3: Result of r0 XOR r1
	r4: Result of r3 AND #FIRST_BIT
	r5: Count the distance
	r6: Control the compare times
*/

count:
	and r4,r3,#FIRST_BIT //r4=r3&FIRST_BIT
	lsr r4,r4,15
	lsl r3,r3,1 //r3=r3<<1
	add r5, r5, r4 //r5=r5+r4
	subs r6,r6,#1 //r6=r6-1
	bne count
	bx lr

hamm:
	eors r3,r0,r1 //r3=r0^r1
	bne count //Use the equal flag implicitly
	bx lr

main:
	//movs r0, #X
	//movs r1, #Y
	ldr r0,=X
	ldr r1,=Y
	mov r5,#0
	mov r6,#16
	ldr r2, =result
	bl hamm
	str r5,[r2]
L: b L
