#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <stdbool.h>
#include <stddef.h>

int my_strcmp(const char *s1, const char *s2);
char *my_strchr(const char *str, const char sym);
size_t my_strlen(const char *str);
size_t my_strnlen(const char *str, size_t max_len);
char *my_strcpy(char *des, const char *src);
char *my_strncpy(char *des, const char *src, size_t num);
char *my_strstr(const char *str, const char *sub);

#endif // __MY_STRING_H__
