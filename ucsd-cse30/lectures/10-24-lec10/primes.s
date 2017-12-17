@ expects dividend in r0, divisor in r1
@ r0 holds the remainder at the end

mod:      subs r0, r1
          addmi r0, r1
          bpl mod


@ expects number in r2
@ changes r1, r0 (because it uses divmod)
@ r2 holds the true/false answer at the end

isprime:  mov r1, #1     @ The current factor
loop:     add r1, #1     @ Increment the current factor (start at 2)
          cmp r1, r2     @ If the current factor is bigger
          bge prime      @   then we've tried everything, it's prime
          mov r0, r2
          b mod          @ Compute r0 % r1 using mod, store in r0
          cmp r1, #0     @   if that value is 0
          beq notprime   @   then we know the number isn't prime
          b loop         @ Otherwise, keep incrementing
prime:    mov r2, #1     @ Store #1 in r0 for "yes it's prime" ~ true
          b end
notprime: mov r2, #0     @ Store #0 in r0 for "no it's not" ~ false
end:


@ Problem!! There's nothing at the end of mod that tells us what to do!
@ What do we want to happen at the end of mod?


@ Where do we want the program counter to go at the end of mod?

A: loop + 24 (cmp r1, #0)
C: isprime
D: prime
B: loop + 20 (b mod)
E: notprime


Proposal:

mod:      subs r0, r1
          addmi r0, r1
          bpl mod
          b loop+24

Should we do this?

A: Yes
B: No



@ We need something to _remember_ what address we came from, so we can get back
@ there. We want to remember the _next_ instruction before we do the break, so
@ that we can come back after.

Something like:


mod:      subs r0, r1
          addmi r0, r1
          bpl mod
          mov pc, r14

prime:
          ...
          mov r14, pc   @ save the current address in r14 (* plus whatever offsets we need)
          b mod
          ...


@ There is one instruction that does this for us:

  bl <label>

@ Stores the next instruction's address in r14 (also known as lr or _link
@ register_), and jumps to the given label.


isprime:  mov r1, #1     @ The current factor
loop:     add r1, #1     @ Increment the current factor (start at 2)
          cmp r1, r2     @ If the current factor is bigger
          bge prime      @   then we've tried everything, it's prime
          mov r0, r2
          bl mod          @ Compute r0 % r1 using mod, store in r0
          cmp r1, #0     @   if that value is 0
          beq notprime   @   then we know the number isn't prime
          b loop         @ Otherwise, keep incrementing
prime:    mov r2, #1     @ Store #1 in r0 for "yes it's prime" ~ true
          b end
notprime: mov r2, #0     @ Store #0 in r0 for "no it's not" ~ false
end:


@ Now any context can use bl to jump to mod after putting the two "arguments"
@ in r0 and r1, and expect control to return directly after with the result in r0


@ bl is a shortcut for something we could have figured out ourselves (if we
@ were clever enough) but it's a pretty powerful idea! We are storing the
@ address of _code_ in a register other than the pc. That is a brand-new idea
@ to us, even if it could be accomplished using what we knew already.



Awesome! Let's now find the first prime larger than a given number!

@ Find the first prime larger than the value in r3 and put it in r0. Use
@ isprime!

Q: Do we need to change isprime?

A: Yes
B: No


findprime:
loop:       mov r2, r3
            bl isprime
            cmp r0, #1            
            beq foundit
            addne r3, #1
            bne loop

foundit:    mov r0, r3
