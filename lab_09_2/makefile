CFLAGS = -std=c99 -Wall -Werror -pedantic
OBJS = info.o my_string.o my_getline.o str_replace.o interface.o

app.exe: $(OBJS) main.o
	gcc -o $@ $^

test.exe: $(OBJS) test.o
	gcc $(LDFLAGS) -o $@ $^

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o *.exe 2>/dev/null
