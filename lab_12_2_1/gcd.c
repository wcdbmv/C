#include "gcd.h"

#define swap(a, b) \
do \
{ \
	a ^= b; \
	b ^= a; \
	a ^= b; \
} \
while (0)

int_t gcd(int_t a, int_t b)
{
	int_t r = a | b;

	if (!a || !b)
		return r;

	b >>= __builtin_ctzl(b);
	if (b == 1)
		return r & -r;

	for (;;)
	{
		a >>= __builtin_ctzl(a);
		if (a == 1)
			return r & -r;
		if (a == b)
			return a << __builtin_ctzl(r);

		if (a < b)
			swap(a, b);
		a -= b;
	}
}
