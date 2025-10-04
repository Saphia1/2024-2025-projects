CC=gcc
CFLAGS=-Wall -ansi -pedantic-errors -g
CLIBS=-lm

TASK1_2_TEST=harmonious pencil push naive jittery greedy billowy practise lock star appear record precede pen lace

TASK3_4_TESTS="5+2-3*4/2^((1.43+2.57)/3)" "4 * (3.332 + 5.668) / 3 ^ 2.0" "-5 + 6 / (+2.76 + 1.24 + +1 ^ 2) - -10.2" "((1+7)-(1*6)" "a+b"

all: disarm_test

disarm_test.o: disarm_test.o
	$(CC) -c $< $(CFLAGS)

disarm.o: disarm.c 
	$(CC) -c $< $(CFLAGS)

# disarm_test 

disarm_test: disarm_test.c disarm.o
	$(CC) -o $@ $^ $(CFLAGS) $(CLIBS)

disarm_test_run: disarm_test
	./disarm_test 

clean:
	rm -f disarm_test *.o
