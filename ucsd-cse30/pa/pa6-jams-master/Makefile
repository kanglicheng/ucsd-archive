CC=gcc
AS=as
ASSIGNMENT_PATH=~/../public/pa6/
VG=valgrind --leak-check=full --undef-value-errors=no

test: test.run
	./test.run

vtest: test.run
	$(VG) ./test.run

test.run: alloc.o test.c runtest.c
	gcc -Wall -g -o test.run test.c runtest.c cutest/CuTest.c alloc.o

alloc.o: alloc.h alloc.c
	gcc -Wall -g -c -o alloc.o alloc.c

clean:
	rm -f main *.o core* *~

