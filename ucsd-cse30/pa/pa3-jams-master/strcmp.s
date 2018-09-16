@ Unique class id: fajr
@ strcmp.s
@ 10/28/2017

@ Registers:
@ r0 = input1 addr, return value
@ r1 = input2 addr
@ r4 = counter register(offset)
@ r5 = input1 working register
@ r6 = input2 working register

.text
.global mystrcmp

mystrcmp:			@ Main function label
	push	{r4, r5, r6, lr}	@ Preserve caller registers
	mov	r4, #0		@ Put 0 into the counter register(r4)
	 
loop:				@ loop to compare
	ldrb	r5, [r0, r4]	@ r0 holds input1, current offset -> r5
	ldrb	r6, [r1, r4]	@ r1 holds input2, current offset -> r6	

	cmp	r5, r6		@ Compare the two
	beq	chk_null	@ Z == 0, check if one(both) are null
	movmi	r0, #-1		@ N == 1, set r0=1
	bmi	end		@ N == 1, b to end
	movhi	r0, #1		@ N == 0, set r0=-1
	bhi	end		@ N == 0, b to end

chk_null:			@ Check for the null character
	cmp	r5, #0		@ If one is null and both are equal,checks both
	moveq	r0, #0		@ Then they are the same length and eq, r0 = 0
	beq	end		@ branch to end
	addne	r4, #1		@ increment r4, the other inc never reached
	bne	loop		@ if r5 = r6 && r5 != null, b to loop

end:				@ End label
	pop	{r4, r5, r6, pc}	@ Pop caller registers
