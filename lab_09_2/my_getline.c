#include "my_getline.h"

#define BUF_SIZE 256

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
	if (!lineptr || !n || !stream)
		return NULLPTR_ERROR;

	char *buf = *lineptr;
	size_t buf_len = *n;

	if (!buf || !buf_len)
	{
		buf_len = BUF_SIZE;
		if (!(buf = malloc(buf_len)))
			return FAILED_ALLOC_ERROR;
		*lineptr = buf;
	}

	if (!fgets(buf, buf_len - 1, stream))
	{
		if (feof(stream))
		{
			free(buf);
			*lineptr = buf = NULL;
			*n = 0;
			return EOF;
		}
		else
		{
			free(buf);
			*lineptr = buf = NULL;
			*n = 0;
			return READ_FILE_ERROR;
		}
	}

	char *peol;
	while (!(peol = my_strchr(buf, '\n')))
	{
		char *buf2;
		if (!(buf2 = malloc(buf_len)))
		{
			free(buf);
			*lineptr = buf = NULL;
			*n = 0;
			return FAILED_ALLOC_ERROR;
		}

		if (!fgets(buf2, buf_len - 1, stream))
		{
			free(buf2);
			if (feof(stream))
				break;
			else
			{
				free(buf);
				*lineptr = buf = NULL;
				*n = 0;
				return READ_FILE_ERROR;
			}
		}

		buf_len *= 2;
		char *new_buf = realloc(buf, buf_len);
		if (!new_buf)
		{
			free(buf2);
			free(buf);
			*lineptr = buf = NULL;
			*n = 0;
			return FAILED_ALLOC_ERROR;
		}

		buf = new_buf;
		my_strncat(buf, buf2, buf_len);
		free(buf2);
	}

	*lineptr = buf;
	*n = buf_len;

	return my_strlen(buf);
}
