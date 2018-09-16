# README answers go here!
Part 1:
I will not use what I learn in this course to break the law or harm others.

Part 2:

There is a vulnerability within the pa4-gradbook binary. 
First off, the password is available at r1 if you set a 
breakpoint at 0x0107e4 and examine the memory. This allows 
students to examine their grade. 

In addition, students can enter a long password and write 
into memory they aren't supposed to. This means that they 
can write the administrator password (which is defined as 
a constant at 0x00021754). By adding 26 extra characters, 
then 2a to the end of the password, the program puts 2a into 
the memory reserved for permissions. There is nothing 
preventing a too large password.
