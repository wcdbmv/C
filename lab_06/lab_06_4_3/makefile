CC := gcc
CFLAGS := -Wall -Werror -std=c99 -pedantic
OBJS := array.o

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

%.exe: $(OBJS) %.o
	$(CC) -o $@ $^

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *.exe
