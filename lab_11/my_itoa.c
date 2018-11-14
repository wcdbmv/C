#include "my_itoa.h"

#include <stddef.h>
#include <stdbool.h>

void swap(char *a, char *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void reverse(char *s, char *f)
{
	while (s < f)
		swap(s++, f--);
}

char *my_itoa(int value, char *str, int base)
{
	char *str_start = str;
	bool is_neg = false;

	if (!value)
	{
		*str++ = '0';
		*str = '\0';
		return str;
	}

	if (value < 0 && base == 10)
	{
		is_neg = true;
		value = -value;
	}

	while (value != 0)
	{
		int r = value % base;
		*str++ = r > 9 ? r - 10 + 'a' : r + '0';
		value = value / base;
	}

	if (is_neg)
		*str++ = '-';

	*str = '\0';

	reverse(str_start, str - 1);

	return str_start;
}
