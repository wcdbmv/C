#include "arr_lib.h"

#include <stdio.h>

void c_print(const int *a, size_t n)
{
	for (size_t i = 0; i != n; ++a, ++i)
		printf("%d ", *a);
	putchar('\n');
}
