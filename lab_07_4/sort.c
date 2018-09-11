#include "sort.h"

void my_sort(void *base, size_t nmemb, size_t size,
             int (*compar)(const void *, const void *))
{
	void *pi = base;
	void *pe = base + (nmemb - 1) * size;
	while (pe - pi > 0)
	{
		void *pi = base;
		while (pe - pi > 0)
		{
			if ((*compar)(pi, pi + size) > 0)
			{
				swap(pi, pi + size, size);
			}
			pi += size;
		}
		pe -= size;
	}
}

void swap(void *a, void *b, size_t size)
{
	char *pa = a, *pb = b;
	do
	{
		char tmp = *pa;
		*pa++ = *pb;
		*pb++ = tmp;
	} while (--size > 0);
}
