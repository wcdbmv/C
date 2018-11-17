#include "my_snprintf.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h> // strcmp
#include <stdio.h>

typedef uint8_t u_t;

bool test_my_snprintf_simple(void);
bool test_my_snprintf_overflow(void);
bool test_my_snprintf_all_together(void);
bool test_my_snprintf_nullptr(void);

bool (*tests[])(void) = {
	test_my_snprintf_simple,
	test_my_snprintf_overflow,
	test_my_snprintf_all_together,
	test_my_snprintf_nullptr };

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

bool test_my_snprintf_simple(void)
{
	size_t n = 10;
	char s1[n], s2[n];
	const char *format = "uhh";

	int rc1 = my_snprintf(s1, n, format);
	int rc2 = snprintf(s2, n, format);

	bool res = rc1 == rc2 && !strcmp(s1, s2);

	return print_result(__func__, res);
}

bool test_my_snprintf_overflow(void)
{
	size_t n = 5;
	char s1[n], s2[n];
	const char *format = "billion";

	int rc1 = my_snprintf(s1, n, format);
	int rc2 = snprintf(s2, n, format);

	bool res = rc1 == rc2 && !strcmp(s1, s2);

	return print_result(__func__, res);
}

bool test_my_snprintf_all_together(void)
{
	size_t n = 20;
	char s1[n], s2[n];
	const char *format = "hx%hx%%%s%i%__i";
	short unsigned hx = 15;
	char *s = " ";
	int i = 0;

	int rc1 = my_snprintf(s1, n, format, hx, s, i);
	int rc2 = snprintf(s2, n, format, hx, s, i);

	bool res = rc1 == rc2 && !strcmp(s1, s2);

	return print_result(__func__, res);
}


bool test_my_snprintf_nullptr(void)
{
	bool res = my_snprintf(NULL, 0, NULL) == MY_SNPRINTF_ERROR;

	return print_result(__func__, res);
}
