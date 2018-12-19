/*
 * There are common funcs that do not depend on the method of memory allocation
 */

#include "matrix.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

struct matrix_type {
	size_t height;
	size_t width;
	item_t **data;
};

extern inline size_t min(size_t a, size_t b);
extern inline size_t max(size_t a, size_t b);

//——————————————————————————————————————————————————————————————————————— utils

inline size_t min(size_t a, size_t b)
{
	if (a < b)
		return a;
	return b;
}

inline size_t max(size_t a, size_t b)
{
	if (a < b)
		return b;
	return a;
}

//—————————————————————————————————————————————————————————————————————— memory

matrix_t copy(matrix_t matrix)
{
	if (!matrix)
		return NULL;

	matrix_t copied = create(matrix->height, matrix->width);
	if (!copied)
		return NULL;

	for (size_t i = 0; i != copied->height; ++i)
		for (size_t j = 0; j != copied->width; ++j)
			copied->data[i][j] = matrix->data[i][j];

	return copied;
}

matrix_t resize(matrix_t matrix, size_t height, size_t width)
{
	if (!matrix)
		return NULL;

	matrix_t new_matrix = create(height, width);
	if (!new_matrix)
		return NULL;

	const size_t h = min(height, matrix->height);
	const size_t w = min(width, matrix->width);
	for (size_t i = 0; i != h; ++i)
		for (size_t j = 0; j != w; ++j)
			new_matrix->data[i][j] = matrix->data[i][j];

	delete(matrix);

	return new_matrix;
}

//—————————————————————————————————————————————————————————————————————— access

item_t *at(matrix_t matrix, size_t i, size_t j)
{
	if (!matrix || i >= matrix->height || j >= matrix->width)
		return NULL;

	return &matrix->data[i][j];
}

void set(matrix_t matrix, size_t i, size_t j, item_t key)
{
	if (!matrix || i >= matrix->height || j >= matrix->width)
		return;

	matrix->data[i][j] = key;
}

//———————————————————————————————————————————————————————————————————————— main

matrix_t add(matrix_t a, matrix_t b)
{
	if (!a || !b || a->height != b->height || a->width != b->width)
		return NULL;

	matrix_t c = create(a->height, a->width);
	if (!c)
		return NULL;

	for (size_t i = 0; i != c->height; ++i)
		for (size_t j = 0; j != c->width; ++j)
			c->data[i][j] = a->data[i][j] + b->data[i][j];

	return c;
}

matrix_t multiply(matrix_t a, matrix_t b)
{
	if (!a || !b || a->width != b->height)
		return NULL;

	matrix_t c = create(a->height, b->width);
	if (!c)
		return NULL;

	for (size_t i = 0; i != c->height; ++i)
		for (size_t j = 0; j != c->width; ++j)
		{
			c->data[i][j] = 0;
			for (size_t k = 0; k != a->width; ++k)
				c->data[i][j] += a->data[i][k] * b->data[k][j];
		}

	return c;
}

size_t find_max_in_col(matrix_t matrix, size_t col)
{
	size_t i_max = col;
	item_t max = fabs(matrix->data[i_max][col]);
	for (size_t i = col + 1; i != matrix->height; ++i)
	{
		item_t tmp = fabs(matrix->data[i][col]);
		if (tmp > max)
		{
			i_max = i;
			max = tmp;
		}
	}

	return i_max;
}

void make_zeros(matrix_t matrix, size_t col)
{
	for (size_t i = col + 1; i != matrix->height; ++i)
	{
		double d = -matrix->data[i][col] / matrix->data[col][col];
		matrix->data[i][col] = 0;
		for (size_t j = col + 1; j != matrix->width; ++j)
			matrix->data[i][j] += d * matrix->data[col][j];
	}
}

void swap_rows(matrix_t matrix, size_t i, size_t j)
{
	for (size_t k = 0; k != matrix->width; ++k)
	{
		item_t tmp = matrix->data[i][k];
		matrix->data[i][k] = matrix->data[j][k];
		matrix->data[j][k] = tmp;
	}
}

matrix_t solve(matrix_t matrix)
{
	if (!matrix || matrix->height + 1 != matrix->width)
		return NULL;

	const size_t n = matrix->height;

	matrix_t g = copy(matrix);
	if (!g)
		return NULL;

	for (size_t k = 0; k != n; ++k)
	{
		size_t max_row = find_max_in_col(g, k);
		swap_rows(g, max_row, k);
		make_zeros(g, k);

		if (fabs(g->data[k][k]) < EPS)
		{
			delete(g);
			return NULL;
		}
	}

	matrix_t x = create(n, 1);
	if (!x)
	{
		delete(g);
		NULL;
	}

	for (int i = n - 1; i >= 0; --i)
	{
		x->data[i][0] = g->data[i][n] / g->data[i][i];
		for (int k = i - 1; k >= 0; --k)
			g->data[k][n] -= g->data[k][i] * x->data[i][0];
	}

	delete(g);

	return x;
}

matrix_t transpose(matrix_t matrix)
{
	if (!matrix)
		return NULL;

	matrix_t transposed = create(matrix->width, matrix->height);
	if (!transposed)
		return NULL;

	for (size_t i = 0; i != transposed->height; ++i)
		for (size_t j = 0; j != transposed->width; ++j)
			transposed->data[i][j] = matrix->data[j][i];

	return transposed;
}

double determinant(matrix_t matrix)
{
	if (!matrix || matrix->height != matrix->width)
		return 0.0;

	matrix_t m = copy(matrix);
	if (!m)
		return 0.0;

	double det = 1.0;
	for (size_t i = 0; i != m->height; ++i)
	{
		size_t k = i;
		for (size_t j = i + 1; j != m->height; ++j)
			if (fabs(m->data[j][i]) > fabs(m->data[k][i]))
				k = j;
		if (fabs(m->data[k][i]) < EPS)
		{
			det = 0.0;
			break;
		}
		swap_rows(m, i, k);
		if (i != k)
			det = -det;
		det *= m->data[i][i];
		for (size_t j = i + 1; j != m->height; ++j)
			m->data[i][j] /= m->data[i][i];
		for (size_t j = 0; j != m->height; ++j)
			if (j != i && fabs(m->data[j][i]) > EPS)
				for (size_t k = i + 1; k != m->height; ++k)
					m->data[j][k] -= m->data[i][k] * m->data[j][i];
	}

	delete(m);

	return det;
}

size_t rang(matrix_t matrix)
{
	matrix_t m = copy(matrix);
	if (!m)
		return 0;

	size_t r = max(m->height, m->width);
	bool line_used[m->height];
	memset(line_used, 0, m->height * sizeof (bool));
	for (size_t i = 0; i != m->width; ++i)
	{
		size_t j = 0;
		for (; j != m->height; ++j)
			if (!line_used[j] && fabs(m->data[j][i]) > EPS)
				break;
		if (j == m->height)
			--r;
		else
		{
			line_used[j] = true;
			for (size_t p = i + 1; p != m->width; ++p)
				m->data[j][p] /= m->data[j][i];
			for (size_t k = 0; k != m->height; ++k)
				if (k != j && fabs(m->data[k][i]) > EPS)
					for (size_t p = i + 1; p != m->width; ++p)
						m->data[k][p] -= m->data[j][p] * m->data[k][i];
		}
	}

	delete(m);

	return r;
}

bool equal(matrix_t a, matrix_t b)
{
	if (!a || !b || a->height != b->height || a->width != b->width)
		return false;

	for (size_t i = 0; i != a->height; ++i)
		for (size_t j = 0; j != a->width; ++j)
			if (fabs(a->data[i][j] - b->data[i][j]) > EPS)
				return false;

	return true;
}

size_t get_height(matrix_t matrix)
{
	if (!matrix)
		return 0;

	return matrix->height;
}

size_t get_width(matrix_t matrix)
{
	if (!matrix)
		return 0;

	return matrix->width;
}

void fprint(matrix_t matrix, FILE *stream)
{
	if (!matrix)
		return;

	for (size_t i = 0; i != matrix->height; ++i)
	{
		for (size_t j = 0; j != matrix->width; ++j)
			fprintf(stream, FORMAT_ITEM_T " ", matrix->data[i][j]);
		fprintf(stream, "\n");
	}
}
