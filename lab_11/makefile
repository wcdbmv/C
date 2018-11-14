CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic -Wno-format-security
OBJS = my_itoa.o my_snprintf.o

.PHONY: clean

test.exe: $(OBJS) test.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *.exe
