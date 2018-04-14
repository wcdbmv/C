#include <stdio.h>

int sorted(unsigned n);

int main(void)
{
	setbuf(stdout, NULL);
	
	unsigned n;
	printf("Input natural number: ");
	scanf("%u", &n);
	
	printf("sorted: ");
	if (sorted(n))
	{
		puts("YES");
	}
	else
	{
		puts("NO");
	}
	return 0;
}

int sorted(unsigned n)
{
	unsigned last_digit = n % 10;
	while (n > 9)
	{
		n /= 10;
		unsigned curr_digit = n % 10;
		if (curr_digit > last_digit) // неубываение
		{
			return 0;
		}
		last_digit = curr_digit;
	}
	return 1;
}