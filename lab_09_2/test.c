#define _GNU_SOURCE // getline
#include <stdio.h>  //
#include <string.h>
#include "interface.h"

#define TESTS 19

bool test_my_strcmp_less(void);
bool test_my_strcmp_equal(void);
bool test_my_strcmp_more(void);
bool test_my_strcmp_empty_s1(void);
bool test_my_strcmp_empty_s2(void);
bool test_my_strchr_simple(void);
bool test_my_strchr_zero(void);
bool test_my_strchr_empty(void);
bool test_my_strlen_simple(void);
bool test_my_strlen_empty(void);
bool test_my_strcpy_simple(void);
bool test_my_strncpy_less(void);
bool test_my_strncpy_more(void);
bool test_my_strstr_simple(void);
bool test_my_strstr_zero(void);
bool test_my_strstr_empty(void);
bool test_my_getline_simple(void);
bool test_my_getline_zero(void);
bool test_my_getline_empty(void);

bool (*tests[])(void) = {
	test_my_strcmp_less,
	test_my_strcmp_equal,
	test_my_strcmp_more,
	test_my_strcmp_empty_s1,
	test_my_strcmp_empty_s2,
	test_my_strchr_simple,
	test_my_strchr_zero,
	test_my_strchr_empty,
	test_my_strlen_simple,
	test_my_strlen_empty,
	test_my_strcpy_simple,
	test_my_strncpy_less,
	test_my_strncpy_more,
	test_my_strstr_simple,
	test_my_strstr_zero,
	test_my_strstr_empty,
	test_my_getline_simple,
	test_my_getline_zero,
	test_my_getline_empty };

const char *names[] = {
	"test_my_strcmp_less",
	"test_my_strcmp_equal",
	"test_my_strcmp_more",
	"test_my_strcmp_empty_s1",
	"test_my_strcmp_empty_s2",
	"test_my_strchr_simple",
	"test_my_strchr_zero",
	"test_my_strchr_empty",
	"test_my_strlen_simple",
	"test_my_strlen_empty",
	"test_my_strcpy_simple",
	"test_my_strncpy_less",
	"test_my_strncpy_more",
	"test_my_strstr_simple",
	"test_my_strstr_zero",
	"test_my_strstr_empty",
	"test_my_getline_simple",
	"test_my_getline_zero",
	"test_my_getline_empty" };

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

bool test_my_strcmp_less(void)
{
	const char *s1 = "Aleksander Mishin", *s2 = "Aleksander Petrov";
	return my_strcmp(s1, s2) == strcmp(s1, s2);
}

bool test_my_strcmp_equal(void)
{
	const char *s1 = "Ruslan Boshirov", *s2 = "Ruslan Boshirov";
	return my_strcmp(s1, s2) == strcmp(s1, s2);
}

bool test_my_strcmp_more(void)
{
	const char *s1 = "Aleksander Petrov", *s2 = "Aleksander Mishkin";
	return my_strcmp(s1, s2) == strcmp(s1, s2);
}

bool test_my_strcmp_empty_s1(void)
{
	const char *s1 = "", *s2 = "Rulan Boshirov";
	return my_strcmp(s1, s2) == strcmp(s1, s2);
}

bool test_my_strcmp_empty_s2(void)
{
	const char *s1 = "Anatoliy Chepiga", *s2 = "";
	return my_strcmp(s1, s2) == strcmp(s1, s2);
}

bool test_my_strchr_simple(void)
{
	const char *str = "abcdef0012", sym = '0';
	return my_strchr(str, sym) == strchr(str, sym);
}

bool test_my_strchr_zero(void)
{
	const char *str = "1234567890", sym = 'a';
	return my_strchr(str, sym) == strchr(str, sym);
}

bool test_my_strchr_empty(void)
{
	const char *str = "", sym = '!';
	return my_strchr(str, sym) == strchr(str, sym);
}

bool test_my_strlen_simple(void)
{
	const char *str = "Anatoliy Chepiga";
	return my_strlen(str) == strlen(str);
}

bool test_my_strlen_empty(void)
{
	const char *str = "";
	return my_strlen(str) == strlen(str);
}

bool test_my_strcpy_simple(void)
{
	char des1[32], des2[32], *src = "Salisbury";
	my_strcpy(des1, src);
	strcpy(des2, src);
	return !my_strcmp(des1, des2);
}

bool test_my_strncpy_less(void)
{
	size_t n = 3;
	char des1[32], des2[32], *src = "Salisbury";
	my_strncpy(des1, src, n);
	strncpy(des2, src, n);
	for (size_t i = 0; i != n; ++i)
		if (des1[i] != des2[i])
			return false;
	return true;
}

bool test_my_strncpy_more(void)
{
	char des1[32], des2[32], *src = "Salisbury";
	my_strncpy(des1, src, 16);
	strncpy(des2, src, 16);
	return !my_strcmp(des1, des2);
}

bool test_my_strstr_simple(void)
{
	const char *str = "Miss Salisbury (Chepiga & Mishkin)", *sub = "Mishkin";
	return my_strstr(str, sub) == strstr(str, sub);
}

bool test_my_strstr_zero(void)
{
	const char *str = "Salisbury (Chepiga & Mishkin)", *sub = "Boshirov";
	return my_strstr(str, sub) == strstr(str, sub);
}

bool test_my_strstr_empty(void)
{
	const char *str = "", *sub = "Spire";
	return my_strstr(str, sub) == strstr(str, sub);
}

bool test_my_getline_simple(void)
{
	FILE *file = fopen("in_1.txt", "r"); // I love it\n
	if (!file)
	{
		fprintf(stderr, "(error while fopen) ");
		return false;
	}

	char *l1 = NULL, *l2 = NULL;
	size_t n1 = 0, n2 = 0;
	bool rc = my_getline(&l1, &n1, file) >= 0;
	if (rc)
	{
		rewind(file);
		if ((rc = getline(&l2, &n2, file) >= 0))
		{
			rc = !my_strcmp(l1, l2);
			free(l2);
		}
		free(l1);
	}
	fclose(file);
	return rc;
}

bool test_my_getline_zero(void)
{
	FILE *file = fopen("in_3.txt", "r"); // \n
	if (!file)
	{
		fprintf(stderr, "(error while fopen) ");
		return false;
	}

	char *l1 = NULL, *l2 = NULL;
	size_t n1 = 0, n2 = 0;
	bool rc = my_getline(&l1, &n1, file) >= 0;
	if (rc)
	{
		rewind(file);
		if ((rc = getline(&l2, &n2, file) >= 0))
		{
			rc = !my_strcmp(l1, l2);
			free(l2);
		}
		free(l1);
	}
	fclose(file);
	return rc;
}

bool test_my_getline_empty(void)
{
	FILE *file = fopen("in_4.txt", "r"); // <empty>
	if (!file)
	{
		fprintf(stderr, "(error while fopen) ");
		return false;
	}

	char *l1 = NULL;
	size_t n1 = 0;
	int rc = my_getline(&l1, &n1, file);
	if (rc > 0)
		free(l1);
	fclose(file);
	return rc == EOF;
}
