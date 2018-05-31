#include <stdio.h>
#include <string.h>
#include "array.h"

void test_correct_read_array()
{
	char *file_name = "io/in_8.txt"; // view-source(file): -8 5 -3 2 -1 1 0 1 1 2 3 5 8
	FILE *file = fopen(file_name, "r");
	if (file != NULL)
	{
		int a[N], *end_a = NULL;
		int rc = read_array(file, a, &end_a);
		fclose(file);

		if (rc != SUCCESS)
		{
			printf("Failed read_array test\n");
			return;
		}

		int b[N] = {-8, 5, -3, 2, -1, 1, 0, 1, 1, 2, 3, 5, 8};
		int *end_b = b + 13;

		int flag = 1;
		int *pa = a;
		int *pb = b;
		while (pa < end_a && pb < end_b)
		{
			if (*pa++ != *pb++)
			{
				flag = 0;
				break;
			}
		}

		char *s = (flag && pa == end_a && pb == end_b ? "Passed" : "Failed");
		printf("%s read_array correctness test\n", s);
	}
	else
	{
		perror(file_name);
	}
}

void test_correct_count_different()
{
	int a[N] = {-8, 5, -3, 2, -1, 1, 0, 1, 1, 2, 3, 5, 8};
	int *end_a = a + 13;

	int different = count_different(a, end_a);
	char *s = (different == 9 ? "Passed" : "Failed");
	printf("%s count_different correctness test\n", s);
}

void test_correct_check_overflow()
{
	char *file_name = "io/in_7.txt"; // view-source(file): 1
	FILE *file = fopen(file_name, "r");
	if (file != NULL)
	{
		printf("# ");
		int rc = check_overflow(file);

		char *s = (rc == SUCCESS ? "Passed" : "Failed");
		printf("%s check_overflow correctness test\n", s);
		fclose(file);
	}
	else
	{
		perror(file_name);
	}
}

void test_check_overflow_error()
{
	char *file_name = "io/in_2.txt"; // view-source(file): hehe huhu
	FILE *file = fopen(file_name, "r");
	if (file != NULL)
	{
		int rc = check_overflow(file);

		char *s = (rc == INVALID_FILE_INPUT ? "Passed" : "Failed");
		printf("%s check_overflowt_error test\n", s);
		fclose(file);
	}
	else
	{
		perror(file_name);
	}
}

void test_read_array_error(int i, int error)
{
	// in_1.txt is empty
	// in_2.txt is invalid (hehe huhu)
	// in_3.txt is invalid (1 2 3 .. 100 101 102 103 hehe huhu)
	char file_name[16];
	sprintf(file_name, "io/in_%d.txt", i);
	FILE *file = fopen(file_name, "r");
	if (file != NULL)
	{
		int a[N], *end_a = NULL;
		int rc = read_array(file, a, &end_a);

		char *s = (rc == error ? "Passed" : "Failed");
		printf("%s read_array_error test %d\n", s, i);
		fclose(file);
	}
	else
	{
		perror(file_name);
	}
}



int main()
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	test_correct_read_array();
	test_correct_count_different();
	test_correct_check_overflow();

	test_check_overflow_error();

	test_read_array_error(1, EMPTY_FILE);
	test_read_array_error(2, INVALID_FILE_INPUT);
	test_read_array_error(3, INVALID_FILE_INPUT);
}
