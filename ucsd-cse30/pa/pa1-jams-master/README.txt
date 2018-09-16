==== Question 1. ====

#1. mystery1.bin:
xxd -p -c 4 mystery1.bin --> 010022e0

010022e0 -> e0220001
1110000 0001 0 0010 0000 0000 0000 0001

the opcode of the instruction is 0001 which represents the EOR operation
Rn = r2
Rd = r0
Rm = r1

Therefore the mystery1.bin file runs an xor operation on r1 and r2 and
stores the result in r0.

In assembly, it would be:

EOR r0, r2, r1

When testing with pa1-runner:

pa1-runner mystery1.bin 1 1
r0 = 0    (0)
r1 = 1    (1)
r2 = 1    (1)

pa1-runner mystery1.bin 1 2
r0 = 3    (3)
r1 = 1    (1)
r2 = 2    (2)

pa1-runner mystery1.bin 65535 65535
r0 = 0     (0)
r1 = 65535 (0xffff)
r2 = 65535 (0xffff)

EOR: if both bits are the same, return 0, else return 1.


#2. mystery2.bin:
xxd -p -c 4 mystery2.bin --> 010002e0

e0020001

1110000 0000 0 0010 0000 0000 0000 0001

the opcode of the instruction is 0000 which represents the AND operation
Rn = r2
Rd = r0
Rm = r1

The mysery2.bin file runs a logic AND operation on r1 and r2 and stores
the result in r0.

In assembly, it would be:

AND r0, r2, r1

When testing with pa1-runner:

pa1-runner mystery2.bin 65535 65535
r0 = 0 (0xffff)
r1 = 1 (0xffff)
r2 = 1 (0xffff)


pa1-runner mystery2.bin 65535 0
r0 = 0 (0x0000)
r1 = 1 (0xffff)
r2 = 1 (0x0000)

pa1-runner mystery2.bin 255 2
r0 = 0   (0x00)
r1 = 255 (0xff)
r2 = 0   (0x00)

AND: if both bits compared are 1, return 1, else return 0.

#3. mystery3.bin:
$: xxd -p -c 4 mystery3.bin 
|--> 910203e0
     030082e0

     e0030291
     e0820003

first instruction: 11100000 000 0 0011 0000 0010 1001 0001

the opcode of first instruction is 000 which represents the multiply operation
Rn = r2
Rd = r3
Rm = r1

second instruction: 1110000 0100 0 0010 0000 0000 0000 0011

the opcode of the second instruction is 0100 which represents the ADD operation
Rn = r2
Rd = r0
Rm = r3

The mystery3.bin file multiplies the contents of r1 and r2 and stores
the result in r3. Then it adds r2 and r3 and stores the result in r0.

In assembly, it would be:

MUL r3, r2, r1
ADD r0, r2, r3


When testing with pa1-runner:

pa1-runner mystery3.bin 2 3
r0 = 9   (9)
r1 = 2   (2)
r2 = 3   (3)
r3 = 6   (6)

pa1-runner mystery3.bin 6 2
r0 = e   (14)
r1 = 6   (6)
r2 = 2   (2)
r3 = c   (12)

pa1-runner mystery3.bin 0 1
r0 = 1   (1)
r1 = 0   (0)
r2 = 1   (1)
r3 = 0   (0)

MUL: Multiply two registers and put the result in a register.
ADD: Add two registers and put the result in a register


==== Question 2. ====

Two reversals are required to get from human readable ARM instructions to
an instruction that the machine can read. 

The human readable instruction is written with bit 31 in the leftmost postion. 
However, the machine expects bit 0 to be in the leftmost position and the
bytes are represented as little endian meaning that the MSB of each of the
four 8-bit bytes that make up the 32-bit word is on the left hand side,
so its important to reverse the order of all the bits in the instruction. 

The second reversal is required because each hex value (0x01 as an example) 
is processed in a little-endian manner. This means that if you didn't reverse
each byte, they would still be in big-endian order.


==== Question 3. ====

To represent r0 = r1 + r2 in a binary instruction, we write:

1110000 0100 0 0001 0000 00000000 0010    
	      |----|  
		  ^
		  |
		  Rn = r1 = 0001 (in binary)


Changing r1 would cause the machine code to change for that set of bits. 

If, for example you wanted to change the first operand to r3, the instruction
would look like the code below:

1110000 0100 0 0011 0000 00000000 0010
              |----|
	          ^
                  |
		  Rn = r3 = 0011 (in binary)

