CFLAGS = -std=c99 -Wall -Werror -pedantic
LFLAGS = -s -pipe
OBJS = action.o interface.o info.o matrix.o
mode = release

ifeq ($(mode), debug)
	CFLAGS += -g3
else ifeq ($(mode), release)
	CFLAGS += -g0 -DNDEBUG
endif

app.exe: $(OBJS) main.o
	gcc $(LFLAGS) -o $@ $^

test.exe: matrix.o test.o
	gcc $(LFLAGS) -o $@ $^

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o *.exe 2>/dev/null/
