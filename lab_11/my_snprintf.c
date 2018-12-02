#include "my_snprintf.h"

#include <stdarg.h>
#include <stdbool.h>
#include "my_itoa.h"

void putnchar(char c, char **curr, size_t size, size_t *n)
{
	if (1 + (*n)++ < size)
		*(*curr)++ = c;
}

void putnstring(const char *str, char **curr, size_t size, size_t *n)
{
	char c;
	while ((c = *str++))
		putnchar(c, curr, size, n);
}

void putnnum(const void *pnum, char **curr, size_t size, size_t *n, int base)
{
	int num = base == 10 ? *(int *) pnum : *(unsigned short *) pnum;
	char str[20];
	my_itoa(num, str, base);
	putnstring(str, curr, size, n);
}

int my_snprintf(char *str, size_t size, const char *format, ...)
{
	// If str is NULL, snprintf falls with SIGSEGV.
	if (!str || !format)
		return MY_SNPRINTF_ERROR;

	// If size is 0, snprintf returns success.

	va_list ap;
	va_start(ap, format);

	bool focus = false;
	size_t n = 0;
	char c;
	int num;
	char *put;
	bool is_short = false;

	while ((c = *format++))
	{
		if (focus)
		{
			switch (c)
			{
				case 'h':
					if (is_short)
						putnstring("%h", &str, size, &n);
					else
						focus = !focus;
					is_short = !is_short;
					break;
				case 's':
					put = va_arg(ap, char *);
					putnstring(put, &str, size, &n);
					break;
				case 'i':
					num = va_arg(ap, int);
					putnnum(&num, &str, size, &n, 10);
					break;
				case 'x':
					if (is_short)
					{
						num = va_arg(ap, int);
						putnnum(&num, &str, size, &n, 16);
					}
					else
						putnstring("%x", &str, size, &n);
					break;
				case '%':
					putnchar('%', &str, size, &n);
					break;
				default:
					putnchar('%', &str, size, &n);
					putnchar(c, &str, size, &n);
					break;
			}
		}
		else if (c != '%')
		{
			putnchar(c, &str, size, &n);
			continue;
		}
		focus = !focus;
	}

	if (focus)
		putnchar('%', &str, size, &n);

	if (size)
		*str = '\0';

	va_end(ap);

	return n;
}
