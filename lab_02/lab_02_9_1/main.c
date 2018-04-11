#include <stdio.h>

int gcd(int a, int b);
void swap(int *a, int *b);

int main(void)
{
	setbuf(stdout, NULL);

	int a, b;

	printf("Input natural a, b: ");
	if (scanf("%d%d", &a, &b) < 2 || a <= 0 || b <= 0)
	{
		printf("a and b must be natural numbers.\n");
		return 1;
	}

	printf("gcd(%d, %d) = %d\n", a, b, gcd(a, b));

	return 0;
}

int gcd(int a, int b)
{
	while (b)
	{
		a %= b;
		swap(&a, &b);
	}
	return a;
}

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
