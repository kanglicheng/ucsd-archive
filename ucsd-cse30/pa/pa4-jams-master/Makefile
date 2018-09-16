CC=gcc
AS=as
ASSIGNMENT_PATH=~/../public/pa4/
VG=valgrind --leak-check=full --undef-value-errors=no

count.o: count.s
	as -o $@ $<
totalLength.o: totalLength.s
	as -o $@ $<
clean:
	rm -f main *.o core* *~

test: test.run
	./test.run

vtest: test.run
	$(VG) ./test.run

test.run: bst.o test.c runtests.c count.o totalLength.o
	gcc -Wall -g -o test.run test.c runtests.c cutest/CuTest.c bst.o count.o totalLength.o

bst.o: bst.h bst.c
	gcc -Wall -g -c -o bst.o bst.c

testbst%: testbst%.run
	./$<

vtestbst%: testbst%.run
	$(VG) ./$<

testbst%.run: $(ASSIGNMENT_PATH)/bst%.o test.c runtests.c
	gcc -Wall -o $@ test.c runtests.c cutest/CuTest.c $<
