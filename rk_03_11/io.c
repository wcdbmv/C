#include "io.h"
#include "errcodes.h"

int read_array(FILE *stream, int **a, size_t *n)
{
	int rc;

	int d;
	if ((rc = fscanf(stream, "%d", &d)) != 1)
		return rc ? INVALID_FILE : UNEXPECTED_EOF;

	if (d <= 0)
		return NEGATIVE_SIZE;

	*n = d;

	*a = malloc(*n * sizeof (int));
	if (!a)
		return FAILED_ALLOC;

	for (int i = 0; i != d; ++i)
	{
		if ((rc = fscanf(stream, "%d", *a + i)) != 1)
		{
			free(*a);
			a = NULL;

			return rc ? INVALID_FILE : UNEXPECTED_EOF;
		}

		if ((*a)[i] < 0 || (*a)[i] > 9)
		{
			free(*a);
			a = NULL;

			return INVALID_FILE;
		}

	}

	return SUCCESS;
}

int read_arrays(int **a, size_t *n, int **b, size_t *m)
{
	int rc;

	FILE *f = fopen("in.txt", "r");

	if ((rc = read_array(f, a, n)) != SUCCESS)
		goto fin;

	if ((rc = read_array(f, b, m)) != SUCCESS)
		goto fin;

fin:
	fclose(f);
	return rc;
}

void write_array(int *a, size_t n)
{
	FILE *f = fopen("out.txt", "w");

	fprintf(f, "%lu\n", n);

	for (size_t i = 0; i != n; ++i)
		fprintf(f, "%d ", a[i]);

	fputc('\n', f);

	fclose(f);
}
