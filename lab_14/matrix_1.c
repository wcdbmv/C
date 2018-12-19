#include "matrix.h"
#include "matrix.c"

matrix_t create(size_t height, size_t width)
{
	if (!height || !width)
		return NULL;

	matrix_t matrix = malloc(sizeof (struct matrix_type));
	if (!matrix)
		return NULL;

	size_t s1 = height * sizeof (item_t *);
	size_t s2 = height * width * sizeof (item_t);
	matrix->data = malloc(s1 + s2);
	if (!matrix->data)
	{
		free(matrix);
		return NULL;
	}

	s1 = height * sizeof (item_t *);
	s2 = width * sizeof (item_t);
	for (size_t i = 0; i != height; ++i)
		matrix->data[i] = (item_t *) ((char *) matrix->data + s1 + i * s2);

	matrix->height = height;
	matrix->width = width;

	return matrix;
}

void delete(matrix_t matrix)
{
	free(matrix->data);
	free(matrix);
}
