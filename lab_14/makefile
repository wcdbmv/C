CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic

OBJS = matrix_1.o

ifeq ($(matrix), 2)
	OBJS = matrix_2.o
else ifeq ($(matrix), 3)
	OBJS = matrix_3.o
else ifeq ($(matrix), 4)
	OBJS = matrix_4.o
endif

.PHONY: test_all clean

test_all:
	make test.exe matrix=1
	valgrind ./test.exe
	make test.exe matrix=2
	valgrind ./test.exe
	make test.exe matrix=3
	valgrind ./test.exe
	make test.exe matrix=4
	valgrind ./test.exe

test.exe: $(OBJS) test.o
	$(CC) $(CFLAGS) -o $@ $^

matrix_%.o: matrix_%.c matrix.h matrix.c
	$(CC) $(CFLAGS) -c $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *.o *.exe 2>/dev/null
