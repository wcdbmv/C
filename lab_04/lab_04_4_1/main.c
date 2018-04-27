#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int input(int array[], size_t N, size_t *length);
void insertion_sort(int array[], size_t length);
void print_integer_array(const int array[], size_t length);

int main(void)
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	const size_t N = 10;
	int array[2*N];
	size_t length;

	int rc;
	if ((rc = input(array, N, &length)) != 0)
	{
		return rc;
	}

	insertion_sort(array, length);

	printf("Sorted array: ");
	print_integer_array(array, length);

	return 0;
}

int input(int array[], size_t N, size_t *length)
{
	printf("Input integer array: ");
	*length = 0;
	int tmp;
	int rc;
	while ((rc = scanf("%d", &tmp)) != EOF)
	{
		if (*length == N)
		{
			fprintf(stderr, "input: Too many arguments\n");
			return -1;
		}
		if (!rc)
		{
			fprintf(stderr, "input: Invalid input\n");
			return -2;
		}
		array[(*length)++] = tmp;
	}
	if (*length == 0)
	{
		fprintf(stderr, "input: Empty input\n");
		return -3;
	}
	return 0;
}

void insertion_sort(int array[], size_t length)
{
	for (size_t i = 1; i != length; ++i)
	{
		int curr = array[i];
		size_t j = i;
		while (j && array[j - 1] > curr)
		{
			array[j] = array[j - 1];
			--j;
		}
		array[j] = curr;
	}
}

void print_integer_array(const int array[], size_t length)
{
	for (int i = 0; i != length; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}
