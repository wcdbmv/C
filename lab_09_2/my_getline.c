#include "my_getline.h"

#define BUF_SIZE 128

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buf[BUF_SIZE];

	if (!fgets(buf, BUF_SIZE, stream))
		return feof(stream) ? EOF : READ_FILE_ERROR;

	char *peol = my_strchr(buf, '\n');
	if (peol)
		*peol = '\0';

	size_t buf_len = my_strlen(buf);

	if (!*lineptr || buf_len + 1 > *n)
	{
		char *p = realloc(*lineptr, BUF_SIZE);
		if (!p)
			return FAILED_ALLOC_ERROR;
		*lineptr = p;
		*n = BUF_SIZE;
	}

	my_strcpy(*lineptr, buf);
	return buf_len;
}
