#include "my_string.h"

int my_strcmp(const char *s1, const char *s2)
{
	const char *p1 = s1, *p2 = s2;
	char c1, c2;

	do
	{
		c1 = *p1++;
		c2 = *p2++;
		if (!c1)
			return c1 - c2;
	}
	while (c1 == c2);

	return c1 - c2;
}

char *my_strchr(const char *str, const char sym)
{
	const char *s = str;
	for (; *s != sym; ++s)
		if (!*s)
			return NULL;
	return (char *) s;
}

size_t my_strlen(const char *str)
{
	const char *s = str - 1;
	while (*++s);
	return s - str;
}

size_t my_strnlen(const char *str, size_t max_len)
{
	size_t len = 0;
	for (; len < max_len; ++len, ++str)
		if (!*str)
			break;
	return len;
}

char *my_strcpy(char *dst, const char *src)
{
	char *s = dst;
	while ((*s++ = *src++));
	return dst;
}

char *my_strncpy(char *dst, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dst[i] = src[i];
	for (; i < n; i++)
		dst[i] = '\0';

	return dst;
}

char *my_strstr(const char *str, const char *sub)
{
	if (!str || !sub)
		return NULL;

	for (; *str; ++str)
	{
		const char *s, *u;
		for (s = str, u = sub; *s && *u && (*s == *u); ++s, ++u);
		if (!*u)
			return (char *) str;
	}

	return NULL;
}

char *my_strncat(char *des, const char *src, size_t num)
{
	char *des_end = des + my_strlen(des);
	while (*src && num--)
		*des_end++ = *src;
	*des_end = '\0';
	return des;
}
