@ Unique class id: fajr
@ palindrome.s
@ 10/28/2017

@ Registers
@ r0 = input
@ r4 = temp input addr, strlen
@ r7 = rightchar
@ r8 = leftchar

.text
.global palindrome

palindrome:			@ Palindrome main label
	push	{r4, r5, r6, r7, r8, lr}	@ Preserve caller registers
	mov	r4, r0
	bl	mystrlen	@ Call mystrlen
	sub	r8, r0, #1	@ r8 = position of last nonnull char
	mov	r7, #0		@ initialize r7
	mov	r0, #1		@ r0 value if no other r0 is set

nextpair:			@ loop label
	ldrb	r5, [r4, r7]	@ grab leftchar
	ldrb	r6, [r4, r8]	@ grab rightchar
	cmp	r5, r6		@ chk leftchar - rightchar
	movne	r0, #0		@ leftchar != rightchar: return -1
	bne	done		@ no palindrome: done
	cmp	r7, r8		@ check left - right
	bge	done		@ left ge right: done (stop)
	add	r7, r7, #1	@ else: go to the next pair: start++
	sub	r8, r8, #1	@ else: go to the next pair: end--
	b       nextpair	@ check the next pair of chars

done:				@ done label
	pop	{r4, r5, r6, r7, r8, lr}	@ Pop caller registers
