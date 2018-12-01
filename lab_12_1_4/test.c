#include "arr_lib.h"

#include <stdint.h>

typedef uint8_t u_t;

bool test_mysort_random(void);
bool test_mysort_sorted(void);
bool test_mysort_reversed(void);
bool test_key_simple(void);
bool test_key_empty_output(void);

bool (*tests[])(void) = {
	test_mysort_random,
	test_mysort_sorted,
	test_mysort_reversed,
	test_key_simple,
	test_key_empty_output };

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

bool test_mysort_random(void)
{
	int a[] = { 2, 0, 4, 1, 3 };

	mysort(a, 5, sizeof (int), compare_int);

	bool res = a[0] == 0 && a[1] == 1 && a[2] == 2 && a[3] == 3 && a[4] == 4;

	return print_result(__func__, res);
}

bool test_mysort_sorted(void)
{
	int a[] = { 0, 1, 2, 3, 4 };

	mysort(a, 5, sizeof (int), compare_int);

	bool res = a[0] == 0 && a[1] == 1 && a[2] == 2 && a[3] == 3 && a[4] == 4;

	return print_result(__func__, res);
}

bool test_mysort_reversed(void)
{
	int a[] = { 4, 3, 2, 1, 0 };

	mysort(a, 5, sizeof (int), compare_int);

	bool res = a[0] == 0 && a[1] == 1 && a[2] == 2 && a[3] == 3 && a[4] == 4;

	return print_result(__func__, res);
}

bool test_key_simple(void)
{
	int old_pb[] = { 0, 1, 2, 3, 4 };
	int *old_pe = old_pb + 5;

	bool res = false;

	double average;
	size_t size = kpp(old_pb, old_pe, &average);
	if (size == 2 && average == 2)
	{
		int *pb = malloc(size * sizeof (int));
		if (!pb)
			return false;
		int *pe = pb + size;
		key(old_pb, old_pe, pb, pe, average);
		res = pb[0] == 3 && pb[1] == 4;
		free(pb);
	}

	return print_result(__func__, res);
}

bool test_key_empty_output(void)
{
	int old_pb[] = { 0, 0, 0, 0, 0 };
	int *old_pe = old_pb + 5;

	double average;
	size_t size = kpp(old_pb, old_pe, &average);

	bool res = !size && !average;

	return print_result(__func__, res);
}
