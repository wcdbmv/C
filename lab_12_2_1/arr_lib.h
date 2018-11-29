#ifndef ARR_LIB_H_
#define ARR_LIB_H_

#include <stddef.h>

// Реализовать функцию циклического сдвига массива на k позиций влево.
void shift(int *a, size_t n, int k);

// Реализовать функцию, которая из одного массива помещает в другой элементы
// первого, которые являются полными квадратами.
size_t copy_squares(const int *a, const size_t n, int *b);

void c_print(const int *a, size_t n);

#endif // ARR_LIB_H_
