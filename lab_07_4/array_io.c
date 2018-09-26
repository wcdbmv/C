#include "array_io.h"

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
	assert(size);

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

void write_array(FILE *file, int *pb, int *pe)
{
	for (int *pi = pb; pi < pe; ++pi)
	{
		fprintf(file, "%d ", *pi);
	}
	fprintf(file, "\n");
}
