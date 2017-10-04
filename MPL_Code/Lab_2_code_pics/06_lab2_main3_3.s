	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	address: .int 0//For storing the return address in mem
	address_2: .int 0//For storing the return address in mem
	arr1: .byte 0x19, 0x34, 0x14, 0x32, 0x52, 0x23, 0x61, 0x29
	arr2: .byte 0x18, 0x17, 0x33, 0x16, 0xFF, 0x20, 0x55, 0xAC
.text
	.global main
	.equ LENGTH,8

/* Register Usage
	r0: address for arr1 and arr2 respectively
	r1: 7,Outer loop range top
	r2: 7-r3
	r3: Outer loop iterator(i)
	r4: Inner loop iterator(j)
	r5: address for variable address(Storing the return address from do_sort back to main)
	r6&r7: Two consecutive elements comparing
	r8: temporary register for swapping
	r9: address for variable address_2(Storing the return address from inner_swap back to do_sort)
*/

swap:
	/*Swaping two elements*/
	movs r8,r6
	movs r6,r7
	movs r7,r8
	/*---------------------------*/
	/*Store the sort value into the memory*/
	strb r7,[r0,r4]
	subs r4,r4,#1
	strb r6,[r0,r4]
	adds r4,r4,#1
	/*------------------------------------*/
	bx lr

inner_swap:
	ldrb r6,[r0,r4] //r6=r0[j]
	adds r4,r4,#1//j++ //r4=r4+1=>j++
	ldrb r7,[r0,r4] //r7=r0[j]
	str lr,[r9]
	cmp r6,r7//result=r6-r7
	/*if r6>r7, Jump to swap segment*/
	IT GT
	blgt swap
	/*------------------------------*/
	ldr lr,[r9]
	cmp r4,r2
	blt inner_swap
	bx lr

do_sort:
	rsbs r2,r3,#7//r2=7-r3
	str lr,[r5]
	movs r4,#0
	/*Jump into inner loop*/
	bl inner_swap
	/*--------------------*/
	ldr lr,[r5]
	adds r3,r3,#1//i++
	cmp r3,r1//if i<7
	blt do_sort
	bx lr

main:
	ldr r5,=address
	ldr r9,=address_2
	movs r1,#7 //Outer loop control top(LENGTH-1)
	//r2 is inner loop control top(LENGTH-i-1)
	/*------------------------------------------*/
	ldr r0,=arr1
	movs r3,#0 //Outer loop control(i)
	movs r4,#0 //Inner loop control(j)
	bl do_sort

	nop

	ldr r0,=arr2
	movs r3,#0 //Outer loop control
	movs r4,#0 //Inner loop control
	bl do_sort
	nop
L: b L
