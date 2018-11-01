#include "sll.h"

node_t *create_node(void *data)
{
	node_t *node = (node_t *) malloc(sizeof (node_t));

	if (node)
	{
		node->data = data;
		node->next = NULL;
	}

	return node;
}

node_t *fget_node(fget_data_func_t fget_data_func, FILE *stream)
{
	assert(stream);

	void *data = fget_data_func(stream);

	if (!data)
		return NULL;

	return create_node(data);
}

void delete_node(node_t **node, delete_data_func_t delete_data_func)
{
	assert(node && *node);

	if (delete_data_func && (*node)->data)
		delete_data_func(&(*node)->data);

	free(*node);
	*node = NULL;
}

void delete_chain(node_t **head, delete_data_func_t delete_data_func)
{
	assert(head && *head);

	while (*head)
	{
		node_t *node = *head;
		*head = (*head)->next;
		delete_node(&node, delete_data_func);
	}
}

void simple_free(void **data)
{
	free(*data);
	*data = NULL;
}


void *pop_back(node_t **head)
{
	if (!head || !*head)
		return NULL;

	node_t *prev = NULL, *curr = *head;
	while (curr->next)
	{
		prev = curr;
		curr = curr->next;
	}

	if (!prev)
		*head = NULL;
	else
		prev->next = NULL;

	void *data = curr->data;

	delete_node(&curr, NULL);

	return data;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
	if (!(head && elem))
		return;

	node_t *prev = NULL, *curr = *head;

	while (curr && curr != before)
	{
		prev = curr;
		curr = curr->next;
	}

	if (curr != before)
		return;

	if (curr == *head)
		*head = elem;
	else
		prev->next = elem;
	elem->next = before;
}

node_t *reverse(node_t *head)
{
	if (!head)
		return NULL;

	if (!head->next)
		return head;

	node_t *new_head = reverse(head->next);
	head->next->next = head;
	head->next = NULL;

	return new_head;
}

void front_back_split(node_t *head, node_t **back)
{
	if (!head || !back)
		return;

	if (!head->next)
	{
		*back = NULL;
		return;
	}

	node_t *slow = head;
	node_t *fast = head;

	node_t *tmp;
	while ((tmp = fast->next) && (tmp = tmp->next))
	{
		fast = tmp;
		slow = slow->next;
	}

	*back = slow->next;
	slow->next = NULL;
}

void magnet(node_t **dest, node_t **src)
{
	if (!dest || !src)
		return;

	node_t *node = *src;
	if (!node)
		return;

	*src = node->next;
	node->next = *dest;
	*dest = node;
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, compare_t compare)
{
	if (!head_a || !head_b || !compare)
		return NULL;

	node_t prehead;
	node_t *tail = &prehead;
	prehead.next = NULL;

	while (true)
	{
		if (!*head_a)
		{
			tail->next = *head_b;
			*head_b = NULL;
			break;
		}
		else if (!*head_b)
		{
			tail->next = *head_a;
			*head_a = NULL;
			break;
		}
		if (compare((*head_a)->data, (*head_b)->data) <= 0)
			magnet(&tail->next, head_a);
		else
			magnet(&tail->next, head_b);
		tail = tail->next;
	}
	return prehead.next;
}

node_t *sort(node_t *head, compare_t compare)
{
	if (!head || !compare)
		return NULL;

	if (!head->next)
		return head;

	node_t *back = NULL;
	front_back_split(head, &back);

	head = sort(head, compare);
	back = sort(back, compare);

	return sorted_merge(&head, &back, compare);
}


size_t len(node_t *head)
{
	size_t res = 0;
	while (head)
	{
		head = head->next;
		++res;
	}
	return res;
}

node_t *max(node_t *head, int *i_max, compare_t compare)
{
	if (!head)
		return NULL;

	node_t *node = head;
	void *max_data = node->data;
	int i = 0;
	*i_max = i;
	while ((head = head->next))
	{
		++i;
		if (compare(max_data, head->data) < 0)
		{
			node = head;
			max_data = node->data;
			*i_max = i;
		}
	}
	return node;
}
