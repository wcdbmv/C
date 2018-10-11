#include "str_replace.h"


#include <stdio.h>
char *str_replace(const char *source, const char *search, const char *replace)
{
	if (!source || !source)
		return NULL;

	size_t source_len = my_strlen(source);
	size_t search_len = my_strlen(search);
	size_t replace_len = my_strlen(replace);

	if (!search_len)
		return NULL;

	size_t nreps = 0;
	char *irep = (char *) source;
	for (; (irep = my_strstr(irep, search)); ++nreps)
		irep += search_len;

	char *res = malloc(source_len + (replace_len - search_len) * nreps + 1);

	if (!res)
		return NULL;

	char *res_start = res;
	while (nreps--)
	{
		irep = my_strstr(source, search);
		size_t offset = irep - source;
		res = my_strncpy(res, source, offset) + offset;
		res = my_strcpy(res, replace) + replace_len;
		source += offset + search_len;
	}
	my_strcpy(res, source);

	res = res_start;

	return res;
}
