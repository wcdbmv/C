CFLAGS = -std=c99 -Wall -Werror -pedantic
COMMON_OBJS = sll.o int_sll_ext.o
APP_OBJS = info.o interface.o

.PHONY: clean

ifeq ($(mode), debug)
	CFLAGS += -g3
else ifeq ($(mode), release)
	CFLAGS += -g0 -DNDEBUG
endif

app.exe: $(COMMON_OBJS) $(APP_OBJS) main.o
	gcc -o $@ $^

test.exe: $(COMMON_OBJS) test.o
	gcc -o $@ $^

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o *.exe 2>/dev/null
