#include <stdbool.h>
#include "matrix.h"

void test_add_matrices_pos(void)
{
	int rc;
	matrix_t a, b, c;
	if ((rc = create_matrix(&a, 2, 2)) != SUCCESS)
	{
		fprintf(stderr, "test_add_matrices_pos: catch error");
		return;
	}
	if ((rc = create_matrix(&b, 2, 2)) != SUCCESS)
	{
		free_matrix(&a);
		fprintf(stderr, "test_add_matrices_pos: catch error");
		return;
	}
	a.data[0][0] = 2;
	a.data[0][1] = 3;
	a.data[1][0] = 5;
	a.data[1][1] = 7;
	b.data[0][0] = 2;
	b.data[0][1] = -3;
	b.data[1][0] = -5;
	b.data[1][1] = 7;
	rc = add_matrices(&a, &b, &c);
	free_matrix(&a);
	free_matrix(&b);
	if (rc == FAILED_MALLOC_ERROR)
	{
		fprintf(stderr, "test_add_matrices_pos: catch error\n");
		return;
	}
	bool cond;
	if (rc == SUCCESS)
	{
		bool cond1 = c.data[0][0] == 4 && !c.data[0][1];
		bool cond2 = !c.data[1][0] && c.data[1][1] == 14;
		cond = cond1 && cond2;
		free_matrix(&c);
	}
	else
		cond = false;
	printf("test_add_matrices_pos: %s\n", cond ? "passed" : "failed");
}

void test_add_matrices_neg(void)
{
	int rc;
	matrix_t a, b, c;
	if ((rc = create_matrix(&a, 2, 3)) != SUCCESS)
	{
		fprintf(stderr, "test_add_matrices_neg: catch error\n");
		return;
	}
	if ((rc = create_matrix(&b, 3, 2)) != SUCCESS)
	{
		free_matrix(&a);
		fprintf(stderr, "test_add_matrices_neg: catch error\n");
		return;
	}
	rc = add_matrices(&a, &b, &c);
	free_matrix(&a);
	free_matrix(&b);
	bool cond;
	if (rc == MATRICES_SIZES_ERROR)
	{
		cond = true;
	}
	else
	{
		cond = false;
		if (rc == SUCCESS)
			free_matrix(&c);
	}
	printf("test_add_matrices_neg: %s\n", cond ? "passed" : "failed");
}

void test_multiply_matrices_pos(void)
{
	int rc;
	matrix_t a, b, c;
	if ((rc = create_matrix(&a, 2, 2)) != SUCCESS)
	{
		fprintf(stderr, "test_multiply_matrices_pos: catch error\n");
		return;
	}
	if ((rc = create_matrix(&b, 2, 2)) != SUCCESS)
	{
		free_matrix(&a);
		fprintf(stderr, "test_multiply_matrices_pos: catch error\n");
		return;
	}
	a.data[0][0] = 1;
	a.data[0][1] = 2;
	a.data[1][0] = 3;
	a.data[1][1] = 4;
	b.data[0][0] = -1;
	b.data[0][1] = 2;
	b.data[1][0] = 3;
	b.data[1][1] = -4;
	rc = multiply_matrices(&a, &b, &c);
	free_matrix(&a);
	free_matrix(&b);
	if (rc == FAILED_MALLOC_ERROR)
	{
		fprintf(stderr, "test_multiply_matrices_pos: catch error\n");
		return;
	}
	bool cond;
	if (rc == SUCCESS)
	{
		bool cond1 = c.data[0][0] == 5 && c.data[0][1] == -6;
		bool cond2 = c.data[1][0] == 9 && c.data[1][1] == -10;
		cond = cond1 && cond2;
		free_matrix(&c);
	}
	else
		cond = false;
	printf("test_multiply_matrices_pos: %s\n", cond ? "passed" : "failed");
}

void test_multiply_matrices_neg(void)
{
	int rc;
	matrix_t a, b, c;
	if ((rc = create_matrix(&a, 2, 3)) != SUCCESS)
	{
		fprintf(stderr, "test_multiply_matrices_neg: catch error\n");
		return;
	}
	if ((rc = create_matrix(&b, 2, 3)) != SUCCESS)
	{
		free_matrix(&a);
		fprintf(stderr, "test_multiply_matrices_neg: catch error\n");
		return;
	}
	rc = multiply_matrices(&a, &b, &c);
	free_matrix(&a);
	free_matrix(&b);
	bool cond;
	if (rc == MATRICES_SIZES_ERROR)
	{
		cond = true;
	}
	else
	{
		cond = false;
		if (rc == SUCCESS)
			free_matrix(&c);
	}
	printf("test_multiply_matrices_neg: %s\n", cond ? "passed" : "failed");
}

void test_solve_matrix_pos(void)
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
	printf("test_solve_matrix_pos: %s\n", cond ? "passed" : "failed");
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

void test_solve_matrix_neg(void)
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
	printf("test_solve_matrix_neg: %s\n", cond ? "passed" : "failed");
	free_matrix(&a);
}

int main(void)
{
	test_add_matrices_pos();
	test_add_matrices_neg();

	test_multiply_matrices_pos();
	test_multiply_matrices_neg();

	test_solve_matrix_pos();
	test_solve_matrix_zeros();
	test_solve_matrix_neg();
}
