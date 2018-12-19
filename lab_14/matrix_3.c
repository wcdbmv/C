#include "matrix.h"
#include "matrix.c"

matrix_t create(size_t height, size_t width)
{
	if (!height || !width)
		return NULL;

	matrix_t matrix = malloc(sizeof (struct matrix_type));
	if (!matrix)
		return NULL;

	matrix->data = calloc(height, sizeof (item_t *));
	if (!matrix->data)
	{
		free(matrix);
		return NULL;
	}

	for (size_t i = 0; i != height; ++i)
	{
		matrix->data[i] = malloc(width * sizeof (item_t));
		if (!matrix->data[i])
		{
			delete(matrix);
			return NULL;
		}
	}

	matrix->height = height;
	matrix->width = width;

	return matrix;
}

void delete(matrix_t matrix)
{
	for (size_t i = 0; i != matrix->height; ++i)
		free(matrix->data[i]);
	free(matrix->data);
	free(matrix);
}
