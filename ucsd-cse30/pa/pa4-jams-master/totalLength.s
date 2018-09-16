@ Unqiue class id: fajr
@ 11/9/2017

@ Put your implementation of totalLength here
@ int totalLength(struct BSTNode* node)

.text
.global totalLength
.global mystrlen

mystrlen:
	mov	r7, #0		@ counter for key iteration
	@mov	r3, r4
startl:
	ldrb	r9, [r0, r7]	@ each key char
	cmp	r9, #0		@ compare each key char to NULL
	beq	end		@ if eq, branch to end
	add	r7, #1		@ increment counter
	b	startl		@ branch back to startl if not broken
end:
	mov	r0, r7		@ return length to r0
	mov	pc, lr		@ pop reg as needed

totalLength:			@totalLength start label
	push	{r4-r11, lr}	@ preserve regs
	mov	r4, r0		@ save r0 (curr node address)	
	cmp	r0, #0		@ compare r0 (node) with NULL
	moveq	r0, #0		@ not really needed I suppose haha
	beq	end2		@ branch to end

	ldr	r0, [r4, #0]	@ load mem address of key into r0
	bl	mystrlen	@ call my own strlen program on r0
	mov	r8, r0		@ save the strlen in r8
	
	ldr	r1, [r4, #4]	@ node->left
	mov	r0, r1		@ move leftnode onto currnode reg
	bl	totalLength	@ branchlink to beginning of function
	mov	r5, r0		@ r5 is left subtree counter

	ldr	r2, [r4, #8]	@ node->right
	mov	r0, r2		@ move rightnode onto currnode reg
	bl	totalLength	@ branchlink to beginning of function
	mov	r6, r0		@ r6 is right subtree counter

	add	r0, r5, r6	@ sum left and right subtree counters
	add	r0, r8		@ add sum of node keys
	
end2:
	pop	{r4-r11, pc}	@ preserve regs
