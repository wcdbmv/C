#ifndef __SORT_H__
#define __SORT_H__

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "errcodes.h"

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
void my_sort(void *base, size_t nmemb, size_t size,
             int (*compar)(const void *, const void *));
int compare_int(const void *p, const void *q);
void swap(void *a, void *b, size_t size);

#endif // __SORT_H__
