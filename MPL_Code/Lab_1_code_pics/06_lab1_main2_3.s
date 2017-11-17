	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	X: .int 0
	Y: .int 0
	Z: .int 0
.text
	.global main

main:
	ldr r0,=X //r0=&X
	ldr r1,=Y //r1=&Y
	ldr r2,=Z //r2=&Z
	ldr r3,=0x5
	str r3,[r0] //X=5
	ldr r3,=0xA //r3=10
	ldr r4,[r0] //r4=X
	str r3,[r1] //Y=10
	ldr r5,[r1] //r5=Y
	mul r4,r4,r5 //r4=r4*r5(X*10)
	adds r4,r4,r5 //r4=r4+r5
	str r4,[r0] //X=r4=X*10+Y
	subs r4,r5,r4 //r4=r5-r4=Y-X
	str r4,[r2] //Z=r4=Y-X
L:B L
