CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic

.PHONY: clean

test.exe: test.o libarr.so
	$(CC) $(CFLAGS) -o $@ $^ -L. -larr -Wl,-rpath,. -lm

libarr.so: shift.o copy_squares.o c_print.o gcd.o is_square.o
	$(CC) $(CFLAGS) -o $@ -shared $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -fPIC $<

%.o: %.c arr_lib.h
	$(CC) $(CFLAGS) -c -fPIC $<

clean:
	rm *.o *.exe *.so 2>/dev/null
