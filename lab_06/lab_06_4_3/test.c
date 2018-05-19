#include <stdio.h>
#include <string.h>
#include "array.h"

void test_read_array_error(int i, int error)
{
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

void test_check_overflow()
{
	char *file_name = "io/in_4.txt";
	FILE *file = fopen(file_name, "r");
	if (file != NULL)
	{
		printf("# ");
		int a[N], *end_a = NULL;
		int rc = read_array(file, a, &end_a);

		char *s = (rc == SUCCESS && end_a - a == N ? "Passed" : "Failed");
		printf("%s check_overflow test 4\n", s);
		fclose(file);
	}
	else
	{
		perror(file_name);
	}
}

void set_values(int i, int *a, int **end_a, int *res)
{
	switch (i)
	{
		case 5:
			for (int i = 0; i != N; ++i)
			{
				a[i] = i + 1;
			}
			*end_a = a + N;
			*res = N;
			break;
		case 6:
			for (int i = 0; i != 10; ++i)
			{
				a[i] = 0;
			}
			*end_a = a + 10;
			*res = 1;
			break;
		case 7:
			a[0] = 1;
			*end_a = a + 1;
			*res = 1;
			break;
		case 8:
			a[0]  = -8; a[1]  = 5; a[2]  = -3; a[3] = 2; a[4] = -1;
			a[5]  =  1; a[6]  = 0; a[7]  =  1; a[8] = 1; a[9] =  2;
			a[10] =  3; a[11] = 5; a[12] = 8;
			*end_a = a + 13;
			*res = 9;
			break;
	}
}

void test_count_different(int i)
{
	int a[N], *end_a = NULL, res = 0;
	set_values(i, a, &end_a, &res);
	int different = count_different(a, end_a);
	char *s = (res == different ? "Passed" : "Failed");
	printf("%s count_different test %d\n", s, i);
}

void test_read_array(int i)
{
	char file_name[16];
	sprintf(file_name, "io/in_%d.txt", i);
	FILE *file = fopen(file_name, "r");
	if (file != NULL)
	{
		int a[N], *end_a = NULL;
		int rc = read_array(file, a, &end_a);
		fclose(file);

		if (rc != SUCCESS)
		{
			printf("Failed read_array test %d\n", i);
			return;
		}

		int b[N], *end_b = NULL, res = 0;
		set_values(i, b, &end_b, &res);

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
		printf("%s read_array test %d\n", s, i);
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

	test_read_array_error(1, EMPTY_FILE);
	test_read_array_error(2, INVALID_FILE_INPUT);
	test_read_array_error(3, INVALID_FILE_INPUT);

	test_check_overflow();

	for (int i = 5; i <= 8; ++i)
	{
		test_read_array(i);
		test_count_different(i);
	}
}
