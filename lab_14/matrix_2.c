#include "matrix.h"
#include "matrix.c"

#include <stdio.h>

matrix_t create(size_t height, size_t width)
{
	if (!height || !width)
		return NULL;

	matrix_t matrix = malloc(sizeof (struct matrix_type));
	if (!matrix)
		return NULL;

	matrix->data = malloc(height * sizeof (item_t *));
	if (!matrix->data)
	{
		free(matrix);
		return NULL;
	}

	item_t *data = malloc(height * width * sizeof (item_t));
	if (!data)
	{
		free(matrix->data);
		free(matrix);
		return NULL;
	}

	for (size_t i = 0; i != height; ++i)
		matrix->data[i] = data + i * width;

	matrix->height = height;
	matrix->width = width;

	return matrix;
}

void delete(matrix_t matrix)
{
	free(matrix->data[0]);
	free(matrix->data);
	free(matrix);
}
