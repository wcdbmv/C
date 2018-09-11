#include "sort.h"

/*
 * Функция-фильтр работает следующим образом:
 * − определяет количество элементов массива, которые удовлетворяют заданному условию;
 * − выделяет память под соответствующее количество элементов;
 * − копирует элементы, удовлетворяющие условию, из старого массива в новый.
 */
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
	int sum_src = 0, size_src = 0;
	for (const int *pi_src = pb_src; pi_src < pe_src; ++pi_src)
	{
		size_src++;
		sum_src += *pi_src;
	}

	double average = (double) sum_src / size_src; // hmm

	int size_dst = 0;
	for (const int *pi_src = pb_src; pi_src < pe_src; ++pi_src)
	{
		if (*pi_src > average)
		{
			++size_dst;
		}
	}

	if (!size_dst)
	{
		return EMPTY_FILTERED_ARRAY;
	}

	*pb_dst = malloc(size_dst * sizeof (int));
	if (!*pb_dst)
	{
		return FAILED_MALLOC;
	}
	*pe_dst = *pb_dst + size_dst;

	int *pi_dst = *pb_dst;
	for (const int *pi_src = pb_src; pi_dst < *pe_dst; ++pi_src)
	{
		if (*pi_src > average)
		{
			*pi_dst++ = *pi_src;
		}
	}

	return size_dst;
}

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

int compare_int(const void *p, const void *q)
{
	const int *a = p;
	const int *b = q;
	return *a - *b;
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
