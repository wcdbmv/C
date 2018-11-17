/*
 * Реализовать  собственную  версию  функции  snprintf, обрабатывающую указанные
 * спецификаторы  типа.  Функция  должна  называться my_snprintf. При реализации
 * этой функции запрещается использовать любые стандартные функции для обработки
 * строк.
 */

#ifndef __MY_SNPRINTF_H__
#define __MY_SNPRINTF_H__

#include <stddef.h>

#define MY_SNPRINTF_ERROR -1

int my_snprintf(char *str, size_t size, const char *format, ...);

#endif // __MY_SNPRINTF_H__
