CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic
OBJS := io.o sub.o info.o

.PHONY: build run clean test memory

build: app.exe

app.exe: $(OBJS) main.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

run: app.exe
	./$<

clean:
	rm -f *.o *.exe

memory: app.exe
	valgrind ./$<
