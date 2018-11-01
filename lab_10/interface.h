#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "int_sll_ext.h"
#include "info.h"

#define LIMIT 100

int check_filenames(const char *s1, const char *s2);
int check_args(int argc, char *argv[]);
int open_files(const char *s1, const char *s2, FILE **input, FILE **output);
void close_files(FILE *input, FILE *output);

int solve(FILE *input, FILE *output);
int read_file(FILE *input, int *size, node_t **head);

#endif // __INTERFACE_H__
