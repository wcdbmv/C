#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "my_string.h" // <string.h>
#include "my_getline.h" // <stdio.h>
#include "str_replace.h"
#include "info.h"

int check_args(int argc, char *argv[]);
int open_files(const char *argv1, const char *argv2, FILE **in, FILE **out);
int fstr_replace(FILE *in, FILE *out, const char *search, const char *replace);
void close_files(FILE *in, FILE *out);

#endif // __INTERFACE_H__
