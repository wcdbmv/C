#ifndef __ARR_LIB_H__
#define __ARR_LIB_H__

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef int (*compare_t)(const void *, const void *);

int count_array_size(FILE *file);
int get_array(FILE *file, int **pb, int **pe, size_t size);
void write_array(FILE *file, const int *pb, const int *pe);
size_t kpp(const int *pb_src, const int *pe_src, double *average);
void key(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst, double average);
void mysort(void *base, size_t nmemb, size_t size, compare_t compar);
int compare_int(const void *p, const void *q);

#endif // __ARR_LIB_H__
