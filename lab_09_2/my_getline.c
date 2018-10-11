#include "my_getline.h"

#define BUF_SIZE 512

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
	if (!lineptr || !n || !stream)
		return NULLPTR_ERROR;

	static char buf[BUF_SIZE];

	if (!fgets(buf, BUF_SIZE, stream))
		return feof(stream) ? EOF : READ_FILE_ERROR;

	size_t buf_len = my_strnlen(buf, BUF_SIZE - 1);

	if (!*lineptr || *n == 0)
	{
		char *p = malloc(BUF_SIZE);
		if (!p)
			return FAILED_ALLOC_ERROR;
		*lineptr = p;
		*n = BUF_SIZE;
	}
	else if (buf_len + 1 > *n)
	{
		char *p = realloc(*lineptr, BUF_SIZE);
		if (!p)
			return FAILED_ALLOC_ERROR;
		*lineptr = p;
		*n = BUF_SIZE;
	}

	my_strncpy(*lineptr, buf, BUF_SIZE);
	if (buf_len + 1 == BUF_SIZE)
		lineptr[buf_len] = '\0';
	return buf_len;
}
