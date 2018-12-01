CC := gcc
CFLAGS := -Wall -Werror -std=c99 -pedantic

app.exe: interface.o main.o libarr.a
	$(CC) $(CFLAGS) -o $@ $^ -L. -larr

app_d.exe: interface.o main.o libarr.so
	$(CC) $(CFLAGS) -o $@ $^ -L. -larr -Wl,-rpath,.

app_dd.exe: interface.o main_d.o libarr.so
	$(CC) $(CFLAGS) -o $@ interface.o main_d.o -ldl

test.exe: test.o libarr.a
	$(CC) $(CFLAGS) -o $@ $^ -L. -larr

libarr.a: arr_lib.o
	ar rc $@ $<

libarr.so: arr_dlib.o
	$(CC) $(CFLAGS) -o $@ -shared $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

arr_dlib.o: arr_lib.c arr_lib.h
	$(CC) $(CFLAGS) -o $@ -c -fPIC $<

clean:
	rm -f *.o *.exe *.a *.so >/dev/null
