#include <stdbool.h>
#include "matrix.h"

void test_add_matrices_positive(void)
{
	matrix_t a, b, c;
	create_matrix(&a, 2, 2);
	create_matrix(&b, 2, 2);
	a.data[0][0] = 2;
	a.data[0][1] = 3;
	a.data[1][0] = 5;
	a.data[1][1] = 7;
	b.data[0][0] = 2;
	b.data[0][1] = -3;
	b.data[1][0] = -5;
	b.data[1][1] = 7;
	int rc = add_matrices(&a, &b, &c);
	bool cond1 = c.data[0][0] == 4 && !c.data[0][1];
	bool cond2 = !c.data[1][0] && c.data[1][1] == 14;
	bool cond = rc == SUCCESS && cond1 && cond2;
	printf("test_add_matrices_positive: %s\n", cond ? "passed" : "failed");
	free_matrix(&a);
	free_matrix(&b);
	free_matrix(&c);
}

void test_add_matrices_negative(void)
{
	matrix_t a, b, c;
	create_matrix(&a, 2, 3);
	create_matrix(&b, 3, 2);
	int rc = add_matrices(&a, &b, &c);
	bool cond = rc == MATRICES_SIZES_ERROR;
	printf("test_add_matrices_negative: %s\n", cond ? "passed" : "failed");
	free_matrix(&a);
	free_matrix(&b);
}

void test_multiply_matrices_positive(void)
{
	matrix_t a, b, c;
	create_matrix(&a, 2, 2);
	create_matrix(&b, 2, 2);
	a.data[0][0] = 1;
	a.data[0][1] = 2;
	a.data[1][0] = 3;
	a.data[1][1] = 4;
	b.data[0][0] = -1;
	b.data[0][1] = 2;
	b.data[1][0] = 3;
	b.data[1][1] = -4;
	int rc = multiply_matrices(&a, &b, &c);
	bool cond1 = c.data[0][0] == 5 && c.data[0][1] == -6;
	bool cond2 = c.data[1][0] == 9 && c.data[1][1] == -10;
	bool cond = rc == SUCCESS && cond1 && cond2;
	printf("test_multiply_matrices_positive: %s\n", cond ? "passed" : "failed");
	free_matrix(&a);
	free_matrix(&b);
	free_matrix(&c);
}

void test_multiply_matrices_negative(void)
{
	matrix_t a, b, c;
	create_matrix(&a, 2, 3);
	create_matrix(&b, 2, 3);
	int rc = add_matrices(&a, &b, &c);
	bool cond = rc == MATRICES_SIZES_ERROR;
	printf("test_multiply_matrices_negative: %s\n", cond ? "passed" : "failed");
	free_matrix(&a);
	free_matrix(&b);
}

void test_copy_swap(void)
{
	matrix_t a, b;
	create_matrix(&a, 4, 2);
	copy_matrix(&a, &b);
	swap_rows(&a, 1, 3);
	bool cond1 = b.data[1][0] == a.data[3][0] && b.data[1][1] == a.data[3][1];
	bool cond2 = b.data[3][0] == a.data[1][0] && b.data[3][1] == a.data[1][1];
	bool cond3 = b.data[2][0] == a.data[2][0] && b.data[2][1] == a.data[2][1];
	bool cond4 = b.data[0][0] == a.data[0][0] && b.data[0][1] == a.data[0][1];
	bool cond = cond1 && cond2 && cond3 && cond4;
	printf("test_copy_swap: %s\n", cond ? "passed" : "failed");
	free_matrix(&a);
	free_matrix(&b);
}

void test_solve_matrix_positive(void)
{
	matrix_t a, x;
	create_matrix(&a, 2, 3);
	a.data[0][0] = 0;
	a.data[0][1] = 1;
	a.data[0][2] = 2;
	a.data[1][0] = 3;
	a.data[1][1] = 4;
	a.data[1][2] = 5;
	int rc = solve_matrix(&a, &x);
	bool cond = rc == SUCCESS && x.data[0][0] == -1 && x.data[1][0] == 2;
	printf("test_solve_matrix_positive: %s\n", cond ? "passed" : "failed");
	free_matrix(&a);
	free_matrix(&x);
}

void test_solve_matrix_zeros(void)
{
	matrix_t a, x;
	create_matrix(&a, 2, 3);
	a.data[0][0] = 1;
	a.data[0][1] = 1;
	a.data[0][2] = 0;
	a.data[1][0] = 1;
	a.data[1][1] = -1;
	a.data[1][2] = 0;
	int rc = solve_matrix(&a, &x);
	bool cond = rc == SUCCESS && !x.data[0][0] && !x.data[1][0];
	printf("test_solve_matrix_zeros: %s\n", cond ? "passed" : "failed");
	free_matrix(&a);
	free_matrix(&x);
}

void test_solve_matrix_negative(void)
{
	matrix_t a, x;
	create_matrix(&a, 2, 3);
	a.data[0][0] = 0;
	a.data[0][1] = 1;
	a.data[0][2] = 2;
	a.data[1][0] = 0;
	a.data[1][1] = -2;
	a.data[1][2] = -4;
	int rc = solve_matrix(&a, &x);
	bool cond = rc == INCOMPATIBLE_SLAE_ERROR;
	printf("test_solve_matrix_negative: %s\n", cond ? "passed" : "failed");
	free_matrix(&a);
}

int main(void)
{
	test_add_matrices_positive();
	test_add_matrices_negative();

	test_multiply_matrices_positive();
	test_multiply_matrices_negative();

	test_copy_swap();

	test_solve_matrix_positive();
	test_solve_matrix_zeros();
	test_solve_matrix_negative();
}
