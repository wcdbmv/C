#include "matrix.h"

int create_matrix(matrix_t *matrix, size_t height, size_t width)
{
	assert(height && width);

	size_t s1 = height * sizeof (double *);
	size_t s2 = height * width * sizeof (double);
	matrix->data = (double **) malloc(s1 + s2);

	if (!matrix->data)
	{
		return FAILED_MALLOC_ERROR;
	}

	s1 = height * sizeof (double *);
	s2 = width * sizeof (double);
	for (size_t i = 0; i != height; ++i)
	{
		matrix->data[i] = (double *) ((char *) matrix->data + s1 + i * s2);
	}

	matrix->height = height;
	matrix->width = width;

	matrix->nonzeros = 0;

	return SUCCESS;
}

int get_matrix_1(FILE *file, matrix_t *matrix)
{
	int rc;
	size_t height, width;
	if ((rc = fscanf(file, "%lu%lu", &height, &width)) != 2)
	{
		if (rc == EOF)
		{
			return EMPTY_INPUT_FILE_ERROR;
		}

		return INVALID_INPUT_FILE_ERROR;
	}

	if (!height && !width)
	{
		return INVALID_INPUT_FILE_ERROR;
	}

	if ((rc = create_matrix(matrix, height, width)) != SUCCESS)
	{
		return rc;
	}

	double tmp;
	for (size_t i = 0; i != height; ++i)
	{
		for (size_t j = 0; j != width; ++j)
		{
			if ((rc = fscanf(file, "%lf", &tmp)) != 1)
			{
				free_matrix(matrix);
				return INVALID_INPUT_FILE_ERROR;
			}

			if (fabs(tmp) > EPS)
			{
				++matrix->nonzeros;
			}

			matrix->data[i][j] = tmp;
		}
	}

	if ((rc = fscanf(file, "%lf", &tmp)) != EOF)
	{
		free_matrix(matrix);
		return INVALID_INPUT_FILE_ERROR;
	}

	return SUCCESS;
}

int add_matrices(const matrix_t *a, const matrix_t *b, matrix_t *c)
{
	assert(a->height && a->width && b->height && b->width);

	if (a->height != b->height || a->width != b->width)
	{
		return MATRICES_SIZES_ERROR;
	}

	int rc;
	if ((rc = create_matrix(c, a->height, a->width)) != SUCCESS)
	{
		return rc;
	}

	for (size_t i = 0; i != c->height; ++i)
	{
		for (size_t j = 0; j != c->width; ++j)
		{
			double tmp = a->data[i][j] + b->data[i][j];
			if (fabs(tmp) > EPS)
			{
				++c->nonzeros;
			}
			c->data[i][j] = tmp;
		}
	}

	return SUCCESS;
}

int multiply_matrices(const matrix_t *a, const matrix_t *b, matrix_t *c)
{
	assert(a->height && a->width && b->height && b->width);

	if (a->width != b->height)
	{
		return MATRICES_SIZES_ERROR;
	}

	int rc;
	if ((rc = create_matrix(c, a->height, b->width)) != SUCCESS)
	{
		return rc;
	}

	for (size_t i = 0; i != c->height; ++i)
	{
		for (size_t j = 0; j != c->width; ++j)
		{
			double tmp = 0;
			for (size_t k = 0; k != a->width; ++k)
			{
				tmp += a->data[i][k] * b->data[k][j];
			}

			if (fabs(tmp) > EPS)
			{
				++c->nonzeros;
			}

			c->data[i][j] = tmp;
		}
	}

	return SUCCESS;
}

int copy_matrix(const matrix_t *from, matrix_t *to)
{
	assert(from->height && from->width);

	int rc;
	if ((rc = create_matrix(to, from->height, from->width)) != SUCCESS)
	{
		return rc;
	}

	for (size_t i = 0; i != to->height; ++i)
	{
		for (size_t j = 0; j != to->width; ++j)
		{
			to->data[i][j] = from->data[i][j];
		}
	}

	to->nonzeros = from->nonzeros;

	return SUCCESS;
}

void swap_rows(matrix_t *matrix, size_t i, size_t j)
{
	assert(matrix->height && matrix->width);
	assert(i < matrix->height && j < matrix->height);

	if (i == j)
	{
		return;
	}

	double *tmp = matrix->data[i];
	matrix->data[i] = matrix->data[j];
	matrix->data[j] = tmp;
}

size_t find_max_in_col(const matrix_t *matrix, size_t col)
{
	assert(matrix->height && matrix->height + 1 == matrix->width);
	assert(col < matrix->width - 1);

	size_t i_max = col;
	double max = fabs(matrix->data[i_max][col]);
	for (size_t i = col + 1; i != matrix->height; ++i)
	{
		double tmp = fabs(matrix->data[i][col]);
		if (tmp > max)
		{
			i_max = i;
			max = tmp;
		}
	}

	return i_max;
}

void make_zeros(matrix_t *matrix, size_t col)
{
	assert(matrix->height && matrix->height + 1 == matrix->width);
	assert(col < matrix->width - 1);

	for (size_t i = col + 1; i != matrix->height; ++i)
	{
		double d = -matrix->data[i][col] / matrix->data[col][col];
		for (size_t j = col; j != matrix->width; ++j)
		{
			if (j == col)
			{
				matrix->data[i][j] = 0;
			}
			else
			{
				matrix->data[i][j] += d * matrix->data[col][j];
			}
		}
	}
}

int solve_matrix(const matrix_t *a, matrix_t *x)
{
	assert(a->height && a->width);

	if (a->height + 1 != a->width)
	{
		return MATRICES_SIZES_ERROR;
	}

	size_t n = a->height;

	int rc;
	matrix_t g;
	if ((rc = copy_matrix(a, &g)) != SUCCESS)
	{
		return rc;
	}

	for (size_t k = 0; k != n; ++k)
	{
		size_t max_row = find_max_in_col(&g, k);
		swap_rows(&g, max_row, k);
		make_zeros(&g, k);

		if (fabs(g.data[k][k]) < EPS)
		{
			free_matrix(&g);
			return INCOMPATIBLE_SLAE_ERROR;
		}
	}

	if ((rc = create_matrix(x, n, 1)) != SUCCESS)
	{
		free_matrix(&g);
		return rc;
	}
	for (int i = n - 1; i >= 0; --i)
	{
		double tmp = g.data[i][n] / g.data[i][i];
		if (fabs(tmp) > EPS)
		{
			++x->nonzeros;
		}
		x->data[i][0] = tmp;
		for (int k = i - 1; k >= 0; --k)
		{
			g.data[k][n] -= g.data[k][i] * x->data[i][0];
		}
	}

	free_matrix(&g);
	return SUCCESS;
}

void free_matrix(matrix_t *matrix)
{
	free(matrix->data);
	matrix->data = NULL;
	matrix->height = matrix->width = matrix->nonzeros = 0;
}

void write_matrix_2(FILE *file, const matrix_t *matrix)
{
	fprintf(file, "%lu %lu %lu\n", matrix->height, matrix->width, matrix->nonzeros);

	for (size_t i = 0; i != matrix->height; ++i)
	{
		for (size_t j = 0; j != matrix->width; ++j)
		{
			double tmp = matrix->data[i][j];
			if (fabs(tmp) > EPS)
			{
				fprintf(file, "%lu %lu %lf\n", i, j, tmp);
			}
		}
	}
}
