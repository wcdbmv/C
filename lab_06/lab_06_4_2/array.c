#include <stdio.h>
#include "array.h"

int read_array(FILE *file, int *a, int **end_a)
{
	int rc;
	for (int i = 0; i != N; ++i)
	{
		if ((rc = fscanf(file, "%d", a++)) == EOF)
		{
			if (i)
			{
				*end_a = --a;
				return SUCCESS;
			}
			return EMPTY_FILE;
		}
		if (!rc)
		{
			return INVALID_FILE_INPUT;
		}
	}
	*end_a = a;
	rc = check_overflow(file);
	return rc;
}

int check_overflow(FILE *file)
{
	int tmp, rc, i = 0;
	while ((rc = fscanf(file, "%d", &tmp)) == 1)
	{
		++i;
	}
	if (!rc)
	{
		return INVALID_FILE_INPUT;
	}
	if (i)
	{
		fprintf(stderr, "Note: There are more than %d numbers in the file.\n", N);
	}
	return SUCCESS;
}

int count_different(int *begin_a, int *end_a)
{
	int *p1 = begin_a + 1;
	int res = 1;
	while (p1 < end_a)
	{
		int *p2 = begin_a;
		int flag_repeat = 1;
		while (p2 < p1)
		{
			if (*p2 == *p1)
			{
				flag_repeat = 0;
				break;
			}
			++p2;
		}
		res += flag_repeat;
		++p1;
	}
	return res;
}
