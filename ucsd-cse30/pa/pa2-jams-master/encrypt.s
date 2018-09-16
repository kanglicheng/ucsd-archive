@ Put your definition of encryption here

@ Key is 16 bits (2 bytes) and is stored in bits 0-15 of r1
@ Character is 8 bits (1 byte) and is stored in bits 0-7 of r1 

@ Inputs:
@	r0 = character to be encrypted
@	r1 = key used for encryption

@ Outputs:
@ 	r0 = encrypted character
@	r1 = updated key


@ ====== Encrypt character (done)======
@ 1. Save original input character in r4
	mov	r4, r0

@ 2. Inspect the most significant bit of the key
	lsrs	r2, r1, #15

	cmp	r2, #1
	bne	set_small_key_lower

	cmp	r2, #1
	beq	set_small_key_upper

@ 3. If the bit is 1, use the upper byte of the key, if it is 0,
@    use the lower byte.
set_small_key_lower:
	lsls	r2, r1, #24
	asr	r2, r2, #24
	b	continue

set_small_key_upper:
	asrs	r2, r1, #8
	b	continue

@ 4. AND the key with with 0x1F
continue:
	and	r3, r2, #0x1f
	
@ 5. EOR the input character with the key in step 4. and put in r0
	eor	r0, r4, r3

@ Clear certain regs
	mov	r2, #0
	mov	r3, #0
	mov	r5, #0
	mov	r6, #0
	mov	r7, #0
	mov	r8, #0
	
@ ====== Update key ======
@ 1. Find (int n) such that encrypted character % n = 5
@ put n in r3

@ First -> If r0 < 11 (at this point), r0 -> r3
	cmp	r0, #11
	blt	encrypt_char_less_than_11

	mov	r3, r0
	mov	r5, #6		
	b	loop_inner
loop_outer:
	mov	r3, r0		@ restore working register after each div loop
	add	r5, #1
loop_inner:
	subs	r3, r3, r5	
	bpl	loop_inner
	add	r3, r3, r5
	cmp	r3, #5
	beq	set_remainder_to_n
	b	loop_outer

encrypt_char_less_than_11:
	mov	r2, r0
	b	continue_branch

set_remainder_to_n:
	mov	r2, r3;
	b	continue_branch

continue_branch:
@ 2. Multiply old key by 4
	mov	r6, #4
	mul	r7, r1, r6

@ 3. Add n(r2) to r7(the working register)
	add	r7, r7, r2

@ 4. Divide by 2 (r5 holds the counter)
	mov	r5, #0
div_loop:
	add	r5, #1
	subs	r7, r7, #2
	bpl	div_loop
	@ Restore the effects of overzealous subtraction and addition
	sub	r5, #1
	add	r7, r7, #2
	@ Move the result of the division back into the working register(r7)
	mov	r7, r5
	mov	r5, #0
	add	r7, #1

@ 5. Subtract the original input character(r4), which was saved at the start
@    from r7.
	sub	r7, r7, r4
	
@ 6. If the value is bigger than 2 bytes, shift the register logically
@    right until there are only 2 bytes left. (upper half word is zero).

	movw	r9, #0xffff
	lsl	r9, r9, #0x10
	cmp	r7, r9
	bgt	logical_shift
	b	skip_shift

logical_shift:
	lsr	r7, #8
	cmp	r7, #0xff
	bgt	logical_shift	
	b	skip_shift

@ 7. Reverse the value of the MSB of the key (that is, bit 15, the highest
@    bit in the 2-byte key). By reverse we mean if it was 1, it becomes 0, 
@    and vice versa.
skip_shift:
	eor	r7, r7, #0x8000

@ Last: Move key back into r1
	mov	r1, r7
