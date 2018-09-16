@ Unique class id: fajr
@ 11/8/2017

@ Put your implementation of count here
@ int count(struct BSTNode* node)

.text
.global count

count:				@ count start label
	push	{r4-r6, lr}	@ presever regs
	mov	r4, r0		@ save r0 (curr node address)
	cmp	r0, #0		@ compare r0 (node) with NULL
	popeq	{r4-r6, pc}	@ if equal, pop nodes off stack

	ldr	r1, [r4, #4]	@ node->left
	mov	r0, r1		@ move leftnode onto currnode reg
	bl	count		@ branchlink to count (this is recursion)
	mov	r5, r0		@ r5 is left subtree counter

	ldr	r2, [r4, #8]	@ node->right
	mov	r0, r2		@ move rightnode onto currnode reg
	bl	count		@ branchlink to count (this is recursion)
	mov	r6, r0		@ r6 is right subtree counter

	add	r0, r5, r6	@ sum left and right subtree counters
	add	r0, #1		@ increment r0 (counter)
	pop	{r4-r6, pc}	@ pop regs at end
