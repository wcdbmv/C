#include "my_strspn.h"

size_t my_strspn(const char *str, const char *sym)
{
	size_t res = 0;
	for (const char *p_str = str; *p_str; ++p_str)
		for (const char *p_sym = sym; *p_sym; ++p_sym)
			if (*p_str == *p_sym)
			{
				++res;
				break;
			}
	return res;
}
