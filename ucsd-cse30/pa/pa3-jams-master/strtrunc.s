@ Unique class id: fajr
@ strtrunc.s
@ 10/28/2017

@ Registers
@ r0 = input, return value
@ r1 = val
@ r4 = temp input addr, strlen
@ r5 = counter register
@ r6 = strlen - val  = new word length
@ r7 = null register (storage only)

.text
.global mystrtrunc

mystrtrunc:				@ truncate function label
	push	{r4, r5, r6, r7, lr}	@ Preserve caller registers
	mov	r4, r0			@ Prep r4	
	push	{r0, r1, r2, r3}	@ Push input registers(function call)
	mov	r0, r4			@ Put the input into r0 for mystrlen
	bl	mystrlen		@ Call mystrlen
	mov	r4, r0			@ r4 has the strlen now
	pop	{r0, r1, r2, r3}	@ Pop input registers(function call)

	cmp	r1, r4			@ Compare r1, r4
	movpl	r0, #-1			@ N == 0, r0 = -1
	bpl	end			@ N == 0, b to end

temp:	subs	r6, r4, r1		@ Find the length of the new string
	mov	r7, #0			@ initialize r7 to 0
	strb	r7, [r0, r6]		@ Store null in the correct offset
	movpl	r0, r6			@ Mov new length into r0 

end:
	pop	{r4, r5, r6, r7, pc}	@ Pop caller registers
