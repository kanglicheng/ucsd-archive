pa3.run: strlen.s strcmp.s strfind.s strrev.s palindrome.s strtrunc.s pa3.o
	as -g -o strlen.o strlen.s
	as -g -o strcmp.o strcmp.s
	as -g -o strtrunc.o strtrunc.s
	as -g -o strrev.o strrev.s
	as -g -o palindrome.o palindrome.s
	as -g -o strfind.o strfind.s
	gcc -g -o pa3-runner strlen.o strfind.o strcmp.o strtrunc.o strrev.o palindrome.o pa3.o 
