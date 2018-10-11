#include "my_strspn.h"

size_t my_strspn(const char *str, const char *sym)
{
	if (!str || !sym)
		return 0;

	const char *p_str = str;
	for (; *p_str; ++p_str)
	{
		bool findet = false;
		for (const char *p_sym = sym; *p_sym; ++p_sym)
			if (*p_str == *p_sym)
			{
				findet = true;
				break;
			}
		if (!findet)
			return p_str - str;
	}
	return p_str - str;
}
