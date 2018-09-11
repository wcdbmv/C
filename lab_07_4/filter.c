#include "filter.h"

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
