#include "arr_lib.h"

#include "errcodes.h"

int count_array_size(FILE *file)
{
	int size = 0, tmp, rc;

	while ((rc = fscanf(file, "%d", &tmp)) == 1)
	{
		++size;
	}

	if (!rc)
	{
		return INVALID_INPUT_FILE_SYNTAX;
	}

	if (!size)
	{
		return EMPTY_INPUT_FILE;
	}

	return size;
}

int get_array(FILE *file, int **pb, int **pe, size_t size)
{
	*pb = malloc(size * sizeof (int));
	if (!pb)
	{
		return FAILED_MALLOC;
	}
	*pe = *pb + size;
	for (int *pi = *pb; pi < *pe; ++pi)
	{
		fscanf(file, "%d", pi);
	}

	return SUCCESS;
}

void write_array(FILE *file, const int *pb, const int *pe)
{
	for (const int *pi = pb; pi < pe; ++pi)
	{
		fprintf(file, "%d ", *pi);
	}
	fprintf(file, "\n");
}

int compare_int(const void *p, const void *q)
{
	return *(int *) p - *(int *) q;
}

// key preprocessor
size_t kpp(const int *pb_src, const int *pe_src, double *average)
{
	int sum_src = 0;
	for (const int *pi_src = pb_src; pi_src < pe_src; ++pi_src)
	{
		sum_src += *pi_src;
	}

	*average = (double) sum_src / (pe_src - pb_src);

	size_t size_dst = 0;
	for (const int *pi_src = pb_src; pi_src < pe_src; ++pi_src)
	{
		if (*pi_src > *average)
		{
			++size_dst;
		}
	}

	return size_dst;
}

void key(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst, double average)
{
	int *pi_dst = pb_dst;
	for (const int *pi_src = pb_src; pi_dst < pe_dst; ++pi_src)
	{
		if (*pi_src > average)
		{
			*pi_dst++ = *pi_src;
		}
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
	}
	while (--size > 0);
}

void mysort(void *base, size_t nmemb, size_t size, compare_t compar)
{
	char *pi = base;
	char *pe = pi + (nmemb - 1) * size;
	while (pe - pi > 0)
	{
		char *pi = base;
		while (pe - pi > 0)
		{
			if (compar(pi, pi + size) > 0)
			{
				swap(pi, pi + size, size);
			}
			pi += size;
		}
		pe -= size;
	}
}
