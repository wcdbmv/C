#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "my_strspn.h"

#define TESTS 5

bool test_my_strspn_simple(void);
bool test_my_strspn_zero(void);
bool test_my_strspn_full(void);
bool test_my_strspn_empty_str(void);
bool test_my_strspn_empty_sym(void);

bool (*tests[])(void) = {
	test_my_strspn_simple,
		test_my_strspn_zero, // omg style check
		test_my_strspn_full,
		test_my_strspn_empty_str,
		test_my_strspn_empty_sym
};

int main(void)
{
	size_t passed = 0;

	for (size_t i = 0; i != TESTS; ++i)
		if (tests[i]())
		{
			fprintf(stderr, "passed\n");
			++passed;
		}
		else
			fprintf(stderr, "failed\n");

	fprintf(stderr, "passed %lu/%d\n", passed, TESTS);
	return passed != TESTS;
}

bool test_my_strspn_simple(void)
{
	fprintf(stderr, "test_my_strspn_simple: ");
	const char *str = "123th", *sym = "0123456789";
	return my_strspn(str, sym) == strspn(str, sym);
}

bool test_my_strspn_zero(void)
{
	fprintf(stderr, "test_my_strspn_zero: ");
	const char *str = "alphavezzy", *sym = "0123456789";
	return my_strspn(str, sym) == strspn(str, sym);
}

bool test_my_strspn_full(void)
{
	fprintf(stderr, "test_my_strspn_full: ");
	const char *str = "123000", *sym = "0123456789";
	return my_strspn(str, sym) == strspn(str, sym);
}

bool test_my_strspn_empty_str(void)
{
	fprintf(stderr, "test_my_strspn_empty_str ");
	const char *str = "", *sym = "abcdef";
	return my_strspn(str, sym) == strspn(str, sym);
}

bool test_my_strspn_empty_sym(void)
{
	fprintf(stderr, "test_my_strspn_empty_sym: ");
	const char *str = "abcdef", *sym = "";
	return my_strspn(str, sym) == strspn(str, sym);
}
