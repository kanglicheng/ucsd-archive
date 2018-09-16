@ Put your implementation of decryption here

@ First off:
@ r0 has the encrypted character
@ r1 has the updated key

@ Since we are using the same key for both encryption and decryption, 
@ we only need to reverse the process of encrypting the character. 
@ In other words, we don't need to reverse the process of updating the key.

	eor	r2, r0, r1

	@for nand, and the two registers then xor it with all 1s
	mov	r3, #0x1f
	and	r2, r2, r3
	eor	r2, r2, #0xff

	mov	r0, r2
