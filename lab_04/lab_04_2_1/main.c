#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int input(int array[], size_t N, size_t *length);
void copy_primes(const int a[], size_t len_a, int primes[], size_t *len_p);
int is_prime(int n);
void print_integer_array(const int array[], size_t length);

int main(void)
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	const size_t N = 10;
	int array[N];
	size_t length_array;

	int rc;
	if ((rc = input(array, N, &length_array)) != 0)
	{
		return rc;
	}

	int primes[N];
	size_t length_primes;
	copy_primes(array, length_array, primes, &length_primes);

	printf("Primes: ");
	print_integer_array(primes, length_primes);

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

void copy_primes(const int a[], size_t len_a, int primes[], size_t* len_p)
{
	*len_p = 0;
	for (int i = 0; i != len_a; ++i)
	{
		if (is_prime(a[i]))
		{
			primes[(*len_p)++] = a[i];
		}
	}
}

int is_prime(int n)
{
	if (n < 2 || (n != 2 && n % 2 == 0))
	{
		return 0;
	}
	for (int i = 3; i*i <= n; i += 2)
	{
		if (n % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

void print_integer_array(const int array[], size_t length)
{
	for (int i = 0; i != length; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}
