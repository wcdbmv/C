CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic

.PHONY: clean ftest

SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=%.o)
OBJS := $(filter-out main.o, $(OBJS))
OBJS := $(filter-out test.o, $(OBJS))

app.exe: $(OBJS) main.o
	$(CC) $(CFLAGS) -o $@ $^

test.exe: $(OBJS) test.o
	$(CC) $(CFLAGS) -o $@ $^

ftest:
	chmod +x test.sh
	./test.sh

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *.o *.exe 2>/dev/null
