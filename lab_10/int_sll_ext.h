#ifndef __INT_SLL_EXT_H__
#define __INT_SLL_EXT_H__

#include "sll.h"

void *fget_int_data(FILE *stream);

node_t *create_int_chain(int *a, size_t n);
int *create_int_array(node_t *head, size_t n);
void print_int_chain(node_t *head);

int compare_int(const void *a, const void *b);


#endif // __INT_SLL_EXT_H__
