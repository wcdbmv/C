#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int input(int array[], size_t N, size_t *length);
void insert_fib(int array[], size_t *length);
void insert(int array[], size_t *length, size_t position, int value);
void print_integer_array(int array[], size_t length);

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

	insert_fib(array, &length);

	printf("Fibonaccied array: ");
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

void insert_fib(int array[], size_t *length)
{
	int prev = 1, fib = 0;
	int j = 0;
	size_t initial_length = *length;
	for (int i = 0; i != initial_length; ++i)
	{
		if (array[i + j] % 3 == 0)
		{
			insert(array, length, i + j + 1, fib);
			fib += prev;
			prev = fib - prev;
			++j;
		}
	}
}

void insert(int array[], size_t *length, size_t position, int value)
{
	for (size_t i = *length; i != position; --i)
	{
		array[i] = array[i-1];
	}
	array[position] = value;
	++*length;
}

void print_integer_array(int array[], size_t length)
{
	for (int i = 0; i != length; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}
