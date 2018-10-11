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
	test_my_strspn_zero,
	test_my_strspn_full,
	test_my_strspn_empty_str,
	test_my_strspn_empty_sym };

const char *names[] = {
	"test_my_strspn_simple",
	"test_my_strspn_zero",
	"test_my_strspn_full",
	"test_my_strspn_empty_str",
	"test_my_strspn_empty_sym" };

int main(void)
{
	size_t passed = 0;

	for (size_t i = 0; i != TESTS; ++i)
	{
		fprintf(stderr, "%s: ", names[i]);
		if (tests[i]())
		{
			fprintf(stderr, "passed\n");
			++passed;
		}
		else
			fprintf(stderr, "failed\n");
	}

	fprintf(stderr, "passed %lu/%d\n", passed, TESTS);
	return passed != TESTS;
}

bool test_my_strspn_simple(void)
{
	const char *str = "123th19", *sym = "0123456789";
	return my_strspn(str, sym) == strspn(str, sym);
}

bool test_my_strspn_zero(void)
{
	const char *str = "alphavezzy10", *sym = "0123456789";
	return my_strspn(str, sym) == strspn(str, sym);
}

bool test_my_strspn_full(void)
{
	const char *str = "123000", *sym = "0123456789";
	return my_strspn(str, sym) == strspn(str, sym);
}

bool test_my_strspn_empty_str(void)
{
	const char *str = "", *sym = "abcdef";
	return my_strspn(str, sym) == strspn(str, sym);
}

bool test_my_strspn_empty_sym(void)
{
	const char *str = "abcdef", *sym = "";
	return my_strspn(str, sym) == strspn(str, sym);
}
