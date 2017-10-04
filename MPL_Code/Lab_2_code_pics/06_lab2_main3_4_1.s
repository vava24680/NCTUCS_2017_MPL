	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	x: .float 0.123
	y: .float -0.456
	z: .word 20
.text
	.global main

enable_fpu:
	LDR.W r0, =0xE000ED88
	LDR r1, [r0]
	ORR r1, r1, #(0xF << 20)
	STR r1, [r0]
	DSB
	ISB
	bx lr

main:
	bl enable_fpu //enabling the fpu function
	ldr r0,=x
	vldr.f32 s0, [r0]
	ldr r0,=y
	vldr.f32 s1, [r0]
	vadd.f32 s2, s0, s1

	//Your code start from here
	//Calculate the following values using FPU instructions
	//and show the register result in your report

	vsub.f32 s2, s0, s1//s2=x-y
	vmul.f32 s2, s0, s1//s2=x*y
	vdiv.f32 s2, s0, s1//s2=x/y

	ldr r0,=z
	vldr.f32 s2, [r0]//copy z from r0 to s2,
	vcvt.f32.u32 s2,s2//convert z from U32 to float representation F32 in s2
	vadd.f32 s3, s0, s1//calculate s3=z+x+y
	vadd.f32 s3, s3, s2
L: b L
