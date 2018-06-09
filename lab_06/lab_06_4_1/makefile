CC := gcc
CFLAGS := -Wall -Werror -std=c99 -pedantic
OBJS := array.o

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

different.exe: $(OBJS) different.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *.exe
