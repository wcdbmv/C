#ifndef __SLL_H__
#define __SLL_H__

#include <stdio.h> // FILE *
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct node node_t;

struct node
{
	void *data;
	node_t *next;
};

typedef void *(*fget_data_func_t)(FILE *);
typedef void (*delete_data_func_t)(void **);
typedef int (*compare_t)(const void *, const void *);

node_t *create_node(void *data);
node_t *fget_node(fget_data_func_t fget_data_func, FILE *stream);
void delete_node(node_t **node, delete_data_func_t delete_data_func);
void delete_chain(node_t **head, delete_data_func_t delete_data_func);
void simple_free(void **data);

void *pop_back(node_t **head);
void insert(node_t **head, node_t *elem, node_t *before);
node_t* reverse(node_t *head);
void front_back_split(node_t* head, node_t** back);
node_t* sorted_merge(node_t **head_a, node_t **head_b, compare_t compare);
node_t* sort(node_t *head, compare_t compare);

void magnet(node_t **dest, node_t **src);


size_t len(node_t *head);
node_t *max(node_t *head, int *i_max, compare_t compare);

#endif // __SLL_H__
