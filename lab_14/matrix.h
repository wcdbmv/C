#ifndef MATRIX_H_
#define MATRIX_H_

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

typedef double item_t;
#define FORMAT_ITEM_T "%g"
#define EPS 1E-9

typedef struct matrix_type *matrix_t;

matrix_t create(size_t height, size_t width);
matrix_t copy(matrix_t matrix);
matrix_t resize(matrix_t matrix, size_t height, size_t width);
void delete(matrix_t matrix);

item_t *at(matrix_t matrix, size_t i, size_t j);
void set(matrix_t matrix, size_t i, size_t j, item_t key);

matrix_t add(matrix_t a, matrix_t b);
matrix_t multiply(matrix_t a, matrix_t b);
matrix_t solve(matrix_t matrix);
matrix_t transpose(matrix_t matrix);
double determinant(matrix_t matrix);
size_t rang(matrix_t matrix);

bool equal(matrix_t a, matrix_t b);
size_t get_height(matrix_t matrix);
size_t get_width(matrix_t matrix);

void fprint(matrix_t matrix, FILE *stream);

#endif // MATRIX_H_
