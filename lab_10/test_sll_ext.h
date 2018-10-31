#ifndef __TEST_SLL_EXT_H__
#define __TEST_SLL_EXT_H__

#include "sll.h"

size_t len(node_t *head);
node_t *create_int_chain(int *a, size_t n);
int *create_int_array(node_t *head, size_t n);
void delete_chain(node_t **head, delete_data_func_t delete_data_func);
void print_int_chain(node_t *head);
int compare_int(const void *a, const void *b);

#endif // __TEST_SLL_EXT_H__
