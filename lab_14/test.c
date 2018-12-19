#include "matrix.h"

#include <math.h>

bool test_create_simple(void);
bool test_create_nullptr(void);
bool test_copy_simple(void);
bool test_copy_nullptr(void);
bool test_resize_simple(void);
bool test_resize_nullptr(void);
bool test_add_simple(void);
bool test_add_dif_sizes(void);
bool test_add_nullptr(void);
bool test_multiply_simple(void);
bool test_multiply_dif_sizes(void);
bool test_multiply_nullptr(void);
bool test_solve_simple(void);
bool test_solve_zeros(void);
bool test_solve_incompatible(void);
bool test_solve_wrong_size(void);
bool test_solve_nullptr(void);
bool test_transpose_simple(void);
bool test_transpose_nullptr(void);
bool test_determinant_simple(void);
bool test_determinant_wrong_size(void);
bool test_determinant_nullptr(void);
bool test_rang_simple(void);
bool test_rang_nullptr(void);

bool (*tests[])(void) = {
	test_create_simple,
	test_create_nullptr,
	test_copy_simple,
	test_copy_nullptr,
	test_resize_simple,
	test_resize_nullptr,
	test_add_simple,
	test_add_dif_sizes,
	test_add_nullptr,
	test_multiply_simple,
	test_multiply_dif_sizes,
	test_multiply_nullptr,
	test_solve_simple,
	test_solve_zeros,
	test_solve_incompatible,
	test_solve_wrong_size,
	test_solve_nullptr,
	test_transpose_simple,
	test_transpose_nullptr,
	test_determinant_simple,
	test_determinant_wrong_size,
	test_determinant_nullptr,
	test_rang_simple,
	test_rang_nullptr };

extern inline bool print_result(const char *func, const bool res);
extern inline bool print_passed(const size_t passed, const size_t total);

int main()
{
	setbuf(stderr, NULL);
	const size_t n_tests = (&tests)[1] - tests;
	size_t passed = 0;

	for (size_t i = 0; i != n_tests; ++i)
		passed += tests[i]();

	return print_passed(passed, n_tests);
}

//——————————————————————————————————————————————————————————————————————— print

inline bool print_result(const char *func, const bool res)
{
	fprintf(stderr, "%s: %s\033[0m\n", func, res ? "\033[32mpassed" : "\033[31mfailed");
	return res;
}

// success — 0
inline bool print_passed(const size_t passed, const size_t total)
{
	fprintf(stderr, "passed %lu/%lu\n", passed, total);
	return passed != total;
}

//———————————————————————————————————————————————————————————————————————— test

bool test_create_simple(void)
{
	matrix_t matrix = create(4, 5);

	bool res = matrix;

	delete(matrix);

	return print_result(__func__, res);
}

bool test_create_nullptr(void)
{
	return print_result(__func__, !create(0, 1) && !create(1, 0) && !create(0, 0));
}

bool test_copy_simple(void)
{
	matrix_t a = create(2, 1);
	set(a, 0, 0, 0);
	set(a, 1, 0, 1);

	matrix_t b = copy(a);

	bool res = equal(a, b);

	delete(a);
	delete(b);

	return print_result(__func__, res);
}

bool test_copy_nullptr(void)
{
	return print_result(__func__, !copy(NULL));
}

bool test_resize_simple(void)
{
	matrix_t a = create(2, 1);
	set(a, 0, 0, 0);
	set(a, 1, 0, 1);

	a = resize(a, 3, 2);
	bool res = *at(a, 0, 0) == 0 && *at(a, 1, 0) == 1;

	delete(a);

	return print_result(__func__, res);
}

bool test_resize_nullptr(void)
{
	return print_result(__func__, !resize(NULL, 4, 4));
}

bool test_add_simple(void)
{
	matrix_t a = create(2, 2);
	set(a, 0, 0, 0);
	set(a, 0, 1, 1);
	set(a, 1, 0, 2);
	set(a, 1, 1, 3);

	matrix_t b = create(2, 2);
	set(b, 0, 0, -1);
	set(b, 0, 1, -2);
	set(b, 1, 0, -3);
	set(b, 1, 1, -4);

	matrix_t c = add(a, b);

	matrix_t d = create(2, 2);
	set(d, 0, 0, -1);
	set(d, 0, 1, -1);
	set(d, 1, 0, -1);
	set(d, 1, 1, -1);

	bool res = equal(c, d);

	delete(a);
	delete(b);
	delete(c);
	delete(d);

	return print_result(__func__, res);
}

bool test_add_dif_sizes(void)
{
	matrix_t a = create(2, 2);
	set(a, 0, 0, 0);
	set(a, 0, 1, 1);
	set(a, 1, 0, 2);
	set(a, 1, 1, 3);

	matrix_t b = create(1, 2);
	set(b, 0, 0, -1);
	set(b, 0, 0, -2);

	bool res = !add(a, b);

	delete(a);
	delete(b);

	return print_result(__func__, res);
}

bool test_add_nullptr(void)
{
	matrix_t a = create(1, 1);
	set(a, 0, 0, 0);

	bool res = !add(a, NULL) && !add(NULL, a) && !add(NULL, NULL);

	delete(a);

	return print_result(__func__, res);
}

bool test_multiply_simple(void)
{
	matrix_t a = create(3, 2);
	set(a, 0, 0, 1);
	set(a, 0, 1, 0);
	set(a, 1, 0, 2);
	set(a, 1, 1, 1);
	set(a, 2, 0, -1);
	set(a, 2, 1, 1);

	matrix_t b = create(2, 3);
	set(b, 0, 0, 1);
	set(b, 0, 1, 2);
	set(b, 0, 2, 0);
	set(b, 1, 0, 0);
	set(b, 1, 1, -1);
	set(b, 1, 2, 1);

	matrix_t c = multiply(a, b);

	matrix_t d = create(3, 3);
	set(d, 0, 0, 1);
	set(d, 0, 1, 2);
	set(d, 0, 2, 0);
	set(d, 1, 0, 2);
	set(d, 1, 1, 3);
	set(d, 1, 2, 1);
	set(d, 2, 0, -1);
	set(d, 2, 1, -3);
	set(d, 2, 2, 1);

	bool res = equal(c, d);

	delete(a);
	delete(b);
	delete(c);
	delete(d);

	return print_result(__func__, res);
}

bool test_multiply_dif_sizes(void)
{
	matrix_t a = create(2, 2);
	set(a, 0, 0, 0);
	set(a, 0, 1, 1);
	set(a, 1, 0, 2);
	set(a, 1, 1, 3);

	matrix_t b = create(1, 2);
	set(b, 0, 0, -1);
	set(b, 0, 0, -2);

	bool res = !multiply(a, b);

	delete(a);
	delete(b);

	return print_result(__func__, res);
}

bool test_multiply_nullptr(void)
{
	matrix_t a = create(1, 1);
	set(a, 0, 0, 0);

	bool res = !multiply(a, NULL) && !multiply(NULL, a) && !multiply(NULL, NULL);

	delete(a);

	return print_result(__func__, res);
}

bool eq(item_t a, item_t b)
{
	return fabs(a - b) < EPS;
}

bool test_solve_simple(void)
{
	matrix_t a = create(2, 3);
	set(a, 0, 0, 0);
	set(a, 0, 1, 1);
	set(a, 0, 2, 2);
	set(a, 1, 0, 3);
	set(a, 1, 1, 4);
	set(a, 1, 2, 5);

	matrix_t x = solve(a);

	bool res = eq(*at(x, 0, 0), -1) && eq(*at(x, 1, 0), 2);

	delete(a);
	delete(x);

	return print_result(__func__, res);
}

bool test_solve_zeros(void)
{
	matrix_t a = create(2, 3);
	set(a, 0, 0, 1);
	set(a, 0, 1, 1);
	set(a, 0, 2, 0);
	set(a, 1, 0, 1);
	set(a, 1, 1, -1);
	set(a, 1, 2, 0);

	matrix_t x = solve(a);

	bool res = eq(*at(x, 0, 0), 0) && eq(*at(x, 1, 0), 0);

	delete(a);
	delete(x);

	return print_result(__func__, res);
}

bool test_solve_incompatible(void)
{
	matrix_t a = create(2, 3);
	set(a, 0, 0, 0);
	set(a, 0, 1, 1);
	set(a, 0, 2, 2);
	set(a, 1, 0, 0);
	set(a, 1, 1, -2);
	set(a, 1, 2, -4);

	bool res = !solve(a);

	delete(a);

	return print_result(__func__, res);
}

bool test_solve_wrong_size(void)
{
	matrix_t a = create(1, 3);

	bool res = !solve(a);

	delete(a);

	return print_result(__func__, res);
}

bool test_solve_nullptr(void)
{
	return print_result(__func__, !solve(NULL));
}

bool test_transpose_simple(void)
{
	matrix_t a = create(2, 2);
	set(a, 0, 0, 0);
	set(a, 0, 1, 1);
	set(a, 1, 0, 2);
	set(a, 1, 1, 3);

	matrix_t b = transpose(a);

	bool res = eq(*at(b, 0, 0), *at(a, 0, 0)) && eq(*at(b, 0, 1), *at(a, 1, 0))
	        && eq(*at(b, 1, 0), *at(a, 0, 1)) && eq(*at(b, 1, 1), *at(a, 1, 1));

	delete(a);
	delete(b);

	return print_result(__func__, res);
}

bool test_transpose_nullptr(void)
{
	return print_result(__func__, !transpose(NULL));
}

bool test_determinant_simple(void)
{
	matrix_t a = create(4, 4);
	set(a, 0, 0, 3);
	set(a, 0, 1, 1);
	set(a, 0, 2, 13);
	set(a, 0, 3, -1);
	set(a, 1, 0, 1);
	set(a, 1, 1, 2);
	set(a, 1, 2, 5);
	set(a, 1, 3, -2);
	set(a, 2, 0, -4);
	set(a, 2, 1, 4);
	set(a, 2, 2, 8);
	set(a, 2, 3, -12);
	set(a, 3, 0, 5);
	set(a, 3, 1, -4);
	set(a, 3, 2, -2);
	set(a, 3, 3, 12);

	bool res = eq(determinant(a), 72);

	delete(a);

	return print_result(__func__, res);
}

bool test_determinant_wrong_size(void)
{
	matrix_t a = create(2, 3);

	bool res = !determinant(a);

	delete(a);

	return print_result(__func__, res);
}

bool test_determinant_nullptr(void)
{
	return print_result(__func__, !determinant(NULL));
}

bool test_rang_simple(void)
{
	matrix_t a = create(4, 5);
	set(a, 0, 0, 6);
	set(a, 0, 1, 0);
	set(a, 0, 2, 2);
	set(a, 0, 3, 1);
	set(a, 0, 4, -3);
	set(a, 1, 0, 9);
	set(a, 1, 1, 5);
	set(a, 1, 2, 7);
	set(a, 1, 3, 6);
	set(a, 1, 4, -6);
	set(a, 2, 0, 3);
	set(a, 2, 1, 0);
	set(a, 2, 2, 1);
	set(a, 2, 3, 2);
	set(a, 2, 4, -1);
	set(a, 3, 0, 0);
	set(a, 3, 1, 5);
	set(a, 3, 2, 4);
	set(a, 3, 3, 3);
	set(a, 3, 4, -2);

	bool res = rang(a) == 3;

	delete(a);

	return print_result(__func__, res);
}

bool test_rang_nullptr(void)
{
	return print_result(__func__, !rang(NULL));
}
