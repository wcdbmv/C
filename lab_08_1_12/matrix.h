#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "errcodes.h"

#define EPS 10E-9

typedef struct
{
	double **data;
	size_t height, width;
	size_t nonzeros;
} matrix_t;


int create_matrix(matrix_t *matrix, size_t height, size_t width);
void free_matrix(matrix_t *matrix);

//             1 means simple format
int get_matrix_1(FILE *file, matrix_t *matrix);

//                2 means coordinate format
void write_matrix_2(FILE *file, const matrix_t *matrix);

int add_matrices(const matrix_t *a, const matrix_t *b, matrix_t *c);
int multiply_matrices(const matrix_t *a, const matrix_t *b, matrix_t *c);
int solve_matrix(const matrix_t *a, matrix_t *x);

int copy_matrix(const matrix_t *from, matrix_t *to);
void swap_rows(matrix_t *matrix, size_t m, size_t n);
size_t find_max_in_col(const matrix_t *matrix, size_t col);

// set to zero all rows below this column
void make_zeros(matrix_t *matrix, size_t col);


#endif // __MATRIX_H__
