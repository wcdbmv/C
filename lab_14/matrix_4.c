#include "matrix.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

struct matrix_type {
	size_t height;
	size_t width;
	item_t *data;
};

//—————————————————————————————————————————————————————————————————————— access

#define _at(matrix, i, j) matrix->data[(i) * matrix->width + (j)]

item_t *at(matrix_t matrix, size_t i, size_t j)
{
	if (!matrix || i >= matrix->height || j >= matrix->width)
		return NULL;

	return &_at(matrix, i, j);
}

void set(matrix_t matrix, size_t i, size_t j, item_t key)
{
	if (!matrix || i >= matrix->height || j >= matrix->width)
		return;

	_at(matrix, i, j) = key;
}

//——————————————————————————————————————————————————————————————————————— utils

extern inline size_t min(size_t a, size_t b);
extern inline size_t max(size_t a, size_t b);

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

matrix_t create(size_t height, size_t width)
{
	if (!height || !width)
		return NULL;

	matrix_t matrix = malloc(sizeof (struct matrix_type));
	if (!matrix)
		return NULL;

	matrix->data = malloc(height * width * sizeof (item_t));
	if (!matrix->data)
	{
		free(matrix);
		return NULL;
	}

	matrix->height = height;
	matrix->width = width;

	return matrix;
}

void delete(matrix_t matrix)
{
	free(matrix->data);
	free(matrix);
}

matrix_t copy(matrix_t matrix)
{
	if (!matrix)
		return NULL;

	matrix_t copied = create(matrix->height, matrix->width);
	if (!copied)
		return NULL;

	for (size_t i = 0; i != copied->height; ++i)
		for (size_t j = 0; j != copied->width; ++j)
			_at(copied, i, j) = _at(matrix, i, j);

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
			_at(new_matrix, i, j) = _at(matrix, i, j);

	delete(matrix);

	return new_matrix;
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
			_at(c, i, j) = _at(a, i, j) + _at(b, i, j);

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
			_at(c, i, j) = 0;
			for (size_t k = 0; k != a->width; ++k)
				_at(c, i, j) += _at(a, i, k) * _at(b, k, j);
		}

	return c;
}

size_t find_max_in_col(matrix_t matrix, size_t col)
{
	size_t i_max = col;
	item_t max = fabs(_at(matrix, i_max, col));
	for (size_t i = col + 1; i != matrix->height; ++i)
	{
		item_t tmp = fabs(_at(matrix, i, col));
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
		double d = -_at(matrix, i, col) / _at(matrix, col, col);
		_at(matrix, i, col) = 0;
		for (size_t j = col + 1; j != matrix->width; ++j)
			_at(matrix, i, j) += d * _at(matrix, col, j);
	}
}

void swap_rows(matrix_t matrix, size_t i, size_t j)
{
	for (size_t k = 0; k != matrix->width; ++k)
	{
		item_t tmp = _at(matrix, i, k);
		_at(matrix, i, k) = _at(matrix, j, k);
		_at(matrix, j, k) = tmp;
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

		if (fabs(_at(g, k, k)) < EPS)
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
		_at(x, i, 0) = _at(g, i, n) / _at(g, i, i);
		for (int k = i - 1; k >= 0; --k)
			_at(g, k, n) -= _at(g, k, i) * _at(x, i, 0);
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
			_at(transposed, i, j) = _at(matrix, j, i);

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
			if (fabs(_at(m, j, i)) > fabs(_at(m, k, i)))
				k = j;
		if (fabs(_at(m, k, i)) < EPS)
		{
			det = 0.0;
			break;
		}
		swap_rows(m, i, k);
		if (i != k)
			det = -det;
		det *= _at(m, i, i);
		for (size_t j = i + 1; j != m->height; ++j)
			_at(m, i, j) /= _at(m, i, i);
		for (size_t j = 0; j != m->height; ++j)
			if (j != i && fabs(_at(m, j, i)) > EPS)
				for (size_t k = i + 1; k != m->height; ++k)
					_at(m, j, k) -= _at(m, i, k) * _at(m, j, i);
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
			if (!line_used[j] && fabs(_at(m, j, i)) > EPS)
				break;
		if (j == m->height)
			--r;
		else
		{
			line_used[j] = true;
			for (size_t p = i + 1; p != m->width; ++p)
				_at(m, j, p) /= _at(m, j, i);
			for (size_t k = 0; k != m->height; ++k)
				if (k != j && fabs(_at(m, k, i)) > EPS)
					for (size_t p = i + 1; p != m->width; ++p)
						_at(m, k, p) -= _at(m, j, p) * _at(m, k, i);
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
			if (fabs(_at(a, i, j) - _at(b, i, j)) > EPS)
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
	for (size_t i = 0; i != matrix->height; ++i)
	{
		for (size_t j = 0; j != matrix->width; ++j)
			fprintf(stream, FORMAT_ITEM_T " ", _at(matrix, i, j));
		fprintf(stream, "\n");
	}
}
