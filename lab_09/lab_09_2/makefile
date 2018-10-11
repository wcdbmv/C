CFLAGS = -std=c99 -Wall -Werror -pedantic
LDFLAGS = -s -pipe
OBJS = info.o my_string.o my_getline.o str_replace.o interface.o

app.exe: $(OBJS) main.o
	gcc $(LDFLAGS) -o $@ $^

test.exe: $(OBJS) test.o
	gcc $(LDFLAGS) -o $@ $^

%.o: %.c %.h
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o *.exe 2>/dev/null
