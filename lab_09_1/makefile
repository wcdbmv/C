CFLAGS = -std=c99 -Wall -Werror -pedantic

test.exe: my_strspn.o test.o
	gcc -o $@ $^

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o *.exe 2>/dev/null
