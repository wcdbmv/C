#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int input(int array[], size_t N, size_t *size);
int odd_product(const int array[], size_t size);

int main(void)
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	const size_t N = 10;
	int array[N];
	size_t size;

	int rc;
	if ((rc = input(array, N, &size)) != 0)
	{
		return rc;
	}

	printf("The product of odd numbers: %d\n", odd_product(array, size));

	return 0;
}

int input(int array[], size_t N, size_t *size)
{
	printf("Input integer array: ");
	*size = 0;
	int tmp;
	int rc;
	while ((rc = scanf("%d", &tmp)) != EOF)
	{
		if (*size == N)
		{
			fprintf(stderr, "input: Too many arguments\n");
			return -1;
		}
		if (!rc)
		{
			fprintf(stderr, "input: Invalid input\n");
			return -2;
		}
		array[(*size)++] = tmp;
	}
	if (*size == 0)
	{
		fprintf(stderr, "input: Empty input\n");
		return -3;
	}
	return 0;
}

int odd_product(const int array[], size_t size)
{
	int res = 1;
	for (ptrdiff_t i = 0; i != size; ++i)
	{
		if (array[i] % 2)
		{
			res *= array[i];
		}
	}
	return res;
}
