CC := gcc
CFLAGS := -Wall -Werror -std=c99 -pedantic

app.exe: interface.o main.o libarr.a
	$(CC) -o $@ $^ -L. -larr

app_d.exe: interface.o main.o libarr.so
	$(CC) -o $@ $^ -L. -larr -Wl,-rpath,.

app_dd.exe: interface.o main_d.o libarr.so
	$(CC) -o $@ interface.o main_d.o -ldl

test.exe: test.o libarr.a
	$(CC) -o $@ $^ -L. -larr

libarr.a: arr_lib.o
	ar rc $@ $<

libarr.so: arr_dlib.o
	$(CC) -o $@ -shared $<

%.o: %.c %.h
	$(CC) -o $@ -c $<

%.o: %.c
	$(CC) -o $@ -c $<

arr_dlib.o: arr_lib.c arr_lib.h
	gcc -o $@ -c -fPIC $<

clean:
	rm -f *.o *.exe *.a *.so >/dev/null
