@ Unique class id: fajr
@ strlen.s
@ 10/27/2017

@ Registers:
@ r0 = input addr, return value 
@ r4 = working register
@ r5 = counter register(offset)

.text
.global mystrlen

mystrlen:			@ main function label
	push	{r4, r5, lr}	@ Push values in r4, r5, lr onto stack
	mov	r5, #0		@ Put 0 into the counter register(r5)

loop:				@ Loops through characters until null byte
	ldrb	r4, [r0, r5]	@ Load offset byte(r5) into work register(r4)
	cmp	r4, #0		@ Compare r4 to 0
	beq	end		@ If null characer has been reached, branch end
	add	r5, #1		@ Increment counter
	b	loop		@ Branch loop

end:				@ end label
	mov	r0, r5		@ Move the final result of counter(r5) -> r0
	pop	{r4, r5, pc}	@ Pop r4, r5, pc back
