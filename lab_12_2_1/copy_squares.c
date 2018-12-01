#include "arr_lib.h"

#include "is_square.h"

size_t copy_squares(const int *a, const size_t n, int *b)
{
	int *s = b;
	for (size_t i = 0; i != n; ++a, ++i)
		if (is_square(*a))
			*b++ = *a;
	return b - s;
}
