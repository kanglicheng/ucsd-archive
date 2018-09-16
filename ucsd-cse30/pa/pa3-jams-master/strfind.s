@ Unique class id: fajr
@ mystrfind.s
@ 10/29/2017

@ Registers
@ r4 = length of input1
@ r5 = length of toFind
@ r6 = holds current input1 character
@ r7 = holds current toFind character
@ r8 = outer loop counter register
@ r9 = testing toFind loop register
@ r10 = hold output before it gets put in r0

.text
.global mystrfind

mystrfind:				@ strfind main label
	push	{r4, r5, r6, r7, r8, r9, r10, lr}	@ push caller registers
	ldrb	r6, [r1, #0]		@ load r1[0] into r6
	cmp	r6, #0			@ compare r6 and 0
	moveq	r0, #0			@ Z == 0, r0=0
	beq	end			@ Z == 0, b to end

	push	{r0, r1, r2, r3}	@ preserve r0-r3
	bl	mystrlen		@ call mystrlen
	mov	r4, r0			@ move result out to r4
	mov	r0, r1			@ move toFind into r0
	bl	mystrlen		@ call mystrlen
	mov	r5, r0			@ move result out to r5
	pop	{r0, r1, r2, r3}	@ restore r0 - r3

	mov	r8, #0			@ Initialize outer loop register to 0
	mov	r9, #0			@ Initialize toFind testing loop reg=0
	mov	r10, #0			@ Initialize temp output holder to 0

loop_out:
	ldrb	r6, [r0, r8]		@ LOAD input char at offset into r6
	ldrb	r7, [r1, r9]		@ STORE toFindChar at offset2 into r6
	cmp	r6, #0			@ If r6 == null, reached end of input
	moveq	r0, #-1			@ Therefore, mov r0=-1
	beq	end			@ And b to end
	
	cmp	r6, r7			@ If r6, r7 are not equal and non null
	bne	add_label		@ Continue to loop through input
	beq	dks			@ If they are equal, b->toFind tester

dks:					@ label loops through input if r6=r7
	ldrb	r6, [r0, r8]		@ LOAD offset value into r6
	ldrb	r7, [r1, r9]		@ LOAD offset value into r7
	add	r8, #1			@ increment offset
ct:	cmp	r7, #0			@ Chek if we have hit toFind's null
	moveq	r0, r10			@ if we have, move the index into r10
	beq	end			@ And also b to end
	
	cmp	r6, r7			@ Compare r6, r7
	bne	addsub_label		@ branch properly
	addeq	r9, #1			@ Increment toFind loop counter 
	moveq	r10, r8			@ Save the index
	subeq	r10, r5			@ needed because goes over by r5 indexs
	ldrb	r6, [r0, r8]		@ load the next input
	ldrb	r7, [r1, r9]		@ load the next toFind
	add	r8, #1			@ increment r8
	b	ct

add_label:				@ label handles looping and index
	add	r8, #1			@ add input index
	b	loop_out	

addsub_label:				@ branched to not all toFind is matchin
	sub	r9, #1			@ Subtract toFind index
	add	r8, #1			@ Add input index
	b	loop_out		@ b to loop_out

end:					@ end label
	pop	{r4, r5, r6, r7, r8, r9,r10, pc}	@ restore regs

