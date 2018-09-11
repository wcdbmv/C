CC := gcc
CFLAGS := -Wall -Werror -std=c99
OBJS := filter.o sort.o array_io.o comparator.o error.o

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

app.exe: $(OBJS) main.o
	$(CC) -o $@ $^

test.exe: sort.o filter.o comparator.o test.o
	$(CC) -o $@ $^

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *.exe 2>/dev/null
