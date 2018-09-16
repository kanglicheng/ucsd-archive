@ Unique class id: fajr
@ strrev.s
@ 10/28/2017

@ Registers
@ r0 = input, return value 
@ r1 = start
@ r2 = end
@ r4 = temp input addr, strlen
@ r5 = counter register
@ r6 = end - start(num_of_swaps), working register

.text
.global mystrrev

mystrrev:				@ reverse main label
	push	{r4, r5, r6, r7, r8, r9, r10, lr}    @ Preserve caller registers
	mov	r4, r0
	push	{r0, r1, r2, r3}        @ Push input registers(function call
	mov	r0, r4                  @ Put the input into r0 for mystrlen
	bl	mystrlen                @ Call mystrlen
	mov	r4, r0                  @ r4 has the strlen now
	pop	{r0, r1, r2, r3}        @ Pop input registers(function call)
tes:
	cmp	r1, r2			@ Compare start and end
	movpl	r0, #-1			@ N == 0, r0 = -1 
	bpl	end			@ N == 0, b to end
	
	cmp	r1, #0			@ Compare start and 0
	movmi	r0, #-1			@ N == 0, r0 = -1
	bmi	end			@ N ==0, b to end

	cmp	r2, r4			@ Compare end and strlen
	movge	r0, #-1			@ N == 0, r0 = -1
	bge	end			@ (Z ==0) && (N == V), b to end

	mov	r5, #0			@ Initialize r5 counter to 0
	sub	r6, r2, r1		@ Subtract end from r6
	lsr	r6, #1			@ Divide r6 by 2
	add	r6, #1			@ Add r6 += 1

	mov	r8, r1			@ Store in r8 the index of start revers
	mov	r9, r2			@ Store in r9 the index of end reversd
loop1:
	cmp	r5, r6			@ Compare counter to num_of_swaps
	subeq	r0, r2, r1		@ Set r0 = end - start
	addeq	r0, #1			@ Add one to fix it
	beq	end			@ Once reached, b to end

	ldrb	r7, [r0, r8]		@ LOAD LHS char
	ldrb	r10, [r0, r9]		@ LOAD RHS char
	strb	r7, [r0, r9]		@ STORE LHS char
	strb	r10, [r0, r8]		@ STORE RHS char

	add	r8, #1			@ Change offset
	sub	r9, #1			@ Change offset

	add	r5, #1			@ loop counter
	b	loop1			@ uncond branch to loop

end:
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}    @ Pop caller registers

