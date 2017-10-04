	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	address: .int 0//For storing the return address in mem
.text
	.global main
	.equ N, 50

/* Register Usage
	r0: Stroing N
	r1: Represent fib(n-2)
	r2: Represent fib(n-1)
	r3: Store the addition times(Initial value is 1 and it has no special meaning)
	r4: Result of fin(N)
	r5: address for variable address(Storing the return address from fib back to main)
*/

init_check://check if r0 is out of range
	cmp r0,#100
	IT GT//T means then and EQ will be a condition fields for add
	movs r4,#-1 //So here we can use GT this condition field
	b L

calculate://Basic idea is that N>=2, then f(N) needs (N-1) addtions
	adds r3,r3,#1 //Control the addtions times
	adds r4,r2,r1 //f(n)=f(n-1)+f(n-2)
	ITT VS //VS is overflow condition tag
	movvs r4,#-2
	bxvs lr
	movs r1,r2 //f(n-2)=f(n-1)
	movs r2,r4 //f(n-1)=f(n)
	cmp r3,#N //when r3=N, r4=f(N) if there is no overflow
	IT LT	//IT instruction
	blt calculate
	bx lr

fib:
	//TODO
	cmp r0,#1
	ITT EQ
	addeq r4,r4,r1
	bxeq lr;
	str lr,[r5]
	bl calculate
	ldr lr,[r5]
	bx lr

main:
	movs r0,#N
	movs r1,#0 //To be fib(N-2)
	movs r2,#1 //To be fib(N-1)
	movs r3,#1 //To control the branch times
	ldr r5,=address
	bl init_check //Check N is in the range
	bl fib
	nop
L: b L
