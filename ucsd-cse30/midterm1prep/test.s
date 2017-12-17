
.global _start

_start:
	mov	r0, #0x00000008
	lsls	r0,r0, #3	
	mov	r1, #0x20000001
	lsls	r1, r1, #3
	mov	r2, #0x80000000
	lsls	r2, r2, #3
	mov	r3, #0x10000000
	lsls	r3, r3, #3
	mov	r4, #0x20000002
	lsls	r4, r4, #3
	
end:
	mov	r7, #1
	svc	#0
