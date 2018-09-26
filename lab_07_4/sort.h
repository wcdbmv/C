#ifndef __SORT_H__
#define __SORT_H__

#include <stdio.h>
#include <stddef.h>
#include "errcodes.h"

typedef int (*compare_t)(const void *, const void *);

void my_sort(void *base, size_t nmemb, size_t size, compare_t compar);
void swap(void *a, void *b, size_t size);

#endif // __SORT_H__
