.data

HW:
  .ascii "Hello!\n"
ANOTHER:
  .ascii "Another"

.text
.global _start

_start:

  ldr r1, =HW

@ What will end up in r1 after this line runs?
@ A: 0x00020080
@ B: 0x6c6c6548
@ C: Something else


  mov r7, #1
  mov r0, #0
  svc #0
