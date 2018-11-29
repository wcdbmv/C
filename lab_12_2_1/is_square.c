#include "is_square.h"

#include <math.h>

bool is_square(int n)
{
#if defined(BOOST16)
	// last digit d = n & 15
	// 0x213 == 0b1000010011
	//            9    4  10
	// True only if n mod 16 is 0, 1, 4 or 9
	if (0x213 & (1 << (n & 15)))
#elif defined(BOOST64)
	// upgrade
	if (0x202021202030213L & (1L << (n & 63)))
#else
	int r = n % 10;
	if (!(r == 2 || r == 3 || r == 7 || r == 8))
#endif
	{
		int t = floor(sqrt((double) n) + 0.5);
		return t * t == n;
	}
	return false;
}
