@ Put your definition of divmod here
@ Initial values:
@     r0 = dividend
@     r1 = divisor
@ dividend/divisor = quotient
@ Don't have to worry about division by zero or negative numbers

@ Output:
@     r0 = quotient
@     r1 = remainder

@ logic is subtract divisor from dividend until divisor > whatever is left from the dividend
@ whatever is left is the remainder

@ r2 used for quotient(counter)
	mov r2, #0
loop:	add	r2, #1	
	subs	r0,r0,r1
	bpl	loop		@ if divident > divisor, loop again till its not
	sub	r2, #1
	add	r0,r0,r1

	@ move values into their final registers
	mov	r1, r0
	mov	r0, r2
