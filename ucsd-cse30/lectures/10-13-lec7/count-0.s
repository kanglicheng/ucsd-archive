@ build with
@
@ $ as -g -o count-0.o count-0.s
@ $ ld -o count-0 count-0.o


.text
.global _start
_start:
  mov r2, #1
  mov r1, #0
loop: lsls r2, #1
  bcs end
  add r1, #1
  b loop
end:
  @ CSE 120
  mov r7, #1  @ #1 means Exit
  mov r0, r1
  svc #0


@ What will happen when I press enter?
@ A: Some error
@ B: Infinite loop
@ C: Nothing
@ D: Print register values
@ E: Something else


@ Where will pc go next?

@ A: Go on to loop+8
@ B: Go on to 0x1006c (end)
@ C: Something else
