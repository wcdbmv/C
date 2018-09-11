#include "comparator.h"

int compare_int(const void *p, const void *q)
{
	const int *a = p;
	const int *b = q;
	return *a - *b;
}
