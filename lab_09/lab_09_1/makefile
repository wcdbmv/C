CFLAGS = -std=c99 -Wall -Werror -pedantic
LDFLAGS = -s -pipe

test.exe: my_strspn.o test.o
	gcc $(LDFLAGS) -o $@ $^

%.o: %.c %.h
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o *.exe 2>/dev/null
