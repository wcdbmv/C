#include "sub.h"

#include <stdbool.h>
#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include "errcodes.h"

#include <stdio.h>

int sub(int *a, size_t n, int *b, size_t m, int **c, size_t *k)
{
	if (n < m)
		return NEGATIVE_ANSWER;

	*c = (int *) malloc(n * sizeof (int));

	bool in_mind = false;
	for (int i = n - 1, j = m - 1; i >= 0; --i, --j)
	{
		int minuend = a[i];
		int subtrahend = (j >= 0 ? b[j] : 0) + in_mind;

		if (minuend < subtrahend)
		{
			if (!i)
			{
				free(*c);
				c = NULL;

				return NEGATIVE_ANSWER;
			}

			in_mind = true;
			minuend += 10;
		}
		else
			in_mind = false;

		int difference = minuend - subtrahend;

		(*c)[i] = difference;
	}

	int zeros = 0;
	for (; zeros != n; ++zeros)
		if ((*c)[zeros])
			break;


	*k = n - zeros;
	if (!*k)
	{
		*k = 1;
		*c = realloc(*c, sizeof (int));
		return SUCCESS;
	}

	if (zeros)
	{
		int *buf = (int *) malloc(*k * sizeof (int));
		memcpy(buf, *c + zeros, *k * sizeof (int));
		free(*c);
		*c = buf;
	}

	return SUCCESS;
}
