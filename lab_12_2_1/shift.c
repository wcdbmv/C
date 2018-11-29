#include "arr_lib.h"

#include "gcd.h"

void shift(int *a, size_t n, int s)
{
	s = (s % (int) n + (int) n) % (int) n;
	if (!s || n < 2)
		return;

	int_t g = gcd(n, s);
	for (int i = 0; i != g; ++i)
	{
		int t = a[i];
		int j = i;
		for (;;)
		{
			int k = j + s;
			if (k >= n)
				k -= n;
			if (k == i)
				break;
			a[j] = a[k];
			j = k;
		}
		a[j] = t;
	}
}
