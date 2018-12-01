#include "arr_lib.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "gcd.h"

typedef uint8_t u_t;

bool test_gcd_simple(void);
bool test_gcd_hard(void);
bool test_gcd_zeros(void);
bool test_shift_simple(void);
bool test_shift_zero(void);
bool test_copy_squares(void);

bool (*tests[])(void) = {
	test_gcd_simple,
	test_gcd_hard,
	test_gcd_zeros,
	test_shift_simple,
	test_shift_zero,
	test_copy_squares };

extern inline bool print_result(const char *func, const bool res);
extern inline bool print_passed(const u_t passed, const u_t total);

int main(void)
{
	const u_t ntests = sizeof tests / sizeof tests[0];
	u_t passed = 0;

	for (u_t i = 0; i != ntests; ++i)
		passed += tests[i]();

	return print_passed(passed, ntests);
}

//——————————————————————————————————————————————————————————————————————— print

inline bool print_result(const char *func, const bool res)
{
	fprintf(stderr, "%s: %s\n", func, res ? "passed" : "failed");
	return res;
}

// success — 0
inline bool print_passed(const u_t passed, const u_t total)
{
	fprintf(stderr, "passed %hhu/%hhu\n", passed, total);
	return passed != total;
}

//———————————————————————————————————————————————————————————————————————— test

bool test_gcd_simple(void)
{
	return print_result(__func__, gcd(12, 18) == 6);
}

bool test_gcd_hard(void)
{
	//                                 fib(39)    fib(40)
	return print_result(__func__, gcd(63245986, 102334155) == 1);
}

bool test_gcd_zeros(void)
{
	bool res = true;

	res &= gcd(0, 0) == 0;
	res &= gcd(0, 5) == 5;
	res &= gcd(5, 0) == 5;

	return print_result(__func__, res);
}

bool test_shift_simple(void)
{
	int a[] = { 0, 1, 2, 3, 4, 5 };

	shift(a, 6, -4);

	bool res = true;
	res &= a[0] == 2 && a[1] == 3 && a[2] == 4;
	res &= a[3] == 5 && a[4] == 0 && a[5] == 1;

	return print_result(__func__, res);
}

bool test_shift_zero(void)
{
	int a[] = { 0, 1, 2, 3, 4, 5 };
	size_t n = sizeof a / sizeof a[0];

	shift(a, n, 0);

	bool res = true;
	for (size_t i = 0; i != n; ++i)
		res &= a[i] == i;

	return print_result(__func__, res);
}

bool test_copy_squares(void)
{
	//                                                             2401^2
	int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 32, 5764800, 5764801, 5764802 };
	size_t n = sizeof a / sizeof a[0];
	int b[n];

	bool res = copy_squares(a, n, b) == 6;
	res &= b[0] == 0 && b[1] == 1 && b[2] == 4 && b[3] == 9 && b[4] == 16 && b[5] == 5764801;

	return print_result(__func__, res);
}
