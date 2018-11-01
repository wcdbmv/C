#include "int_sll_ext.h"

void *fget_int_data(FILE *stream)
{
	int *data = (int *) malloc(sizeof (int));
	if (fscanf(stream, "%d", data) != 1)
	{
		free(data);
		return NULL;
	}

	return data;
}

node_t *create_int_chain(int *a, size_t n)
{
	if (!n)
		return NULL;

	node_t *head = create_node(a);
	node_t *tail = head;
	for (int i = 1; i < n; ++i)
	{
		node_t *node = create_node(a + i);
		tail = tail->next = node;
	}

	return head;
}

int *create_int_array(node_t *head, size_t n)
{
	assert(head);

	if (!n)
		return NULL;

	int *a = (int *) malloc(n * sizeof (int));
	if (!a)
		return NULL;

	node_t *curr = head;
	for (size_t i = 0; i != n; ++i)
	{
		a[i] = *(int *) curr->data;
		curr = curr->next;
	}

	return a;
}

// debug
void print_int_chain(node_t *head)
{
	while (head)
	{
		fprintf(stderr, "%d ", *(int *) head->data);
		head = head->next;
	}
	fprintf(stderr, "\n");
}

int compare_int(const void *a, const void *b)
{
	return *(int *) a - *(int *) b;
}
