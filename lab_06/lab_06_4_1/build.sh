#!/usr/bin/bash
gcc -Wall -Werror -std=c99 -pedantic -c array.c
gcc -Wall -Werror -std=c99 -pedantic -c different.c
gcc -Wall -Werror -std=c99 -pedantic -o different.exe array.o different.o
