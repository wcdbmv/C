#include "int_sll_ext.h"

bool test_pop_back_simple(void);
bool test_pop_back_single(void);
bool test_pop_back_nullptr(void);
bool test_insert_simple(void);
bool test_insert_first(void);
bool test_insert_last(void);
bool test_insert_void(void);
bool test_insert_fake(void);
bool test_insert_nullptr(void);
bool test_reverse_simple(void);
bool test_reverse_single(void);
bool test_reverse_nullptr(void);
bool test_front_back_split_even(void);
bool test_front_back_split_odd(void);
bool test_front_back_split_single(void);
bool test_front_back_split_nullptr(void);
bool test_magnet_simple(void);
bool test_magnet_nullptr(void);
bool test_sorted_merge_simple(void);
bool test_sorted_merge_trivial(void);
bool test_sorted_merge_nullptr(void);
bool test_sort_simple(void);
bool test_sort_nullptr(void);

bool (*tests[])(void) = {
	test_pop_back_simple,
	test_pop_back_single,
	test_pop_back_nullptr,
	test_insert_simple,
	test_insert_first,
	test_insert_last,
	test_insert_void,
	test_insert_fake,
	test_insert_nullptr,
	test_reverse_simple,
	test_reverse_single,
	test_reverse_nullptr,
	test_front_back_split_even,
	test_front_back_split_odd,
	test_front_back_split_single,
	test_front_back_split_nullptr,
	test_magnet_simple,
	test_magnet_nullptr,
	test_sorted_merge_simple,
	test_sorted_merge_trivial,
	test_sorted_merge_nullptr,
	test_sort_simple,
	test_sort_nullptr };

int main(void)
{
	const size_t TESTS = sizeof(tests) / sizeof(tests[0]);
	size_t passed = 0;

	for (size_t i = 0; i != TESTS; ++i)
		if (tests[i]())
		{
			fprintf(stderr, "passed\n");
			++passed;
		}
		else
			fprintf(stderr, "failed\n");

	fprintf(stderr, "passed %lu/%lu\n", passed, TESTS);
	return passed != TESTS;
}

bool test_pop_back_simple(void)
{
	fprintf(stderr, "%s: ", __func__);
	int a[] = { 0, 1, 2, 3, 4 };
	node_t *head = create_int_chain(a, sizeof a / sizeof a[0]);
	int *popped = pop_back(&head);
	bool res = *popped == 4 && len(head) == 4;
	delete_chain(&head, NULL);
	return res;
}

bool test_pop_back_single(void)
{
	fprintf(stderr, "%s: ", __func__);
	int data = 10;
	node_t *node = create_node(&data);
	int *popped = pop_back(&node);
	bool res = *popped == data && !node;
	return res;
}

bool test_pop_back_nullptr(void)
{
	fprintf(stderr, "%s: ", __func__);
	node_t *head = NULL;
	return !pop_back(NULL) && !pop_back(&head);
}

bool test_insert_simple(void)
{
	fprintf(stderr, "%s: ", __func__);
	int a[] = { 0, 1, 2, 4 };
	int data = 3;
	node_t *head = create_int_chain(a, sizeof a / sizeof a[0]);
	node_t *node = create_node(&data);
	node_t *tail = head->next->next->next;
	insert(&head, node, tail);
	int *b = create_int_array(head, 5);
	bool res = b[0] == 0 && b[1] == 1 && b[2] == 2 && b[3] == 3 && b[4] == 4;
	delete_chain(&head, NULL);
	free(b);
	return res;
}

bool test_insert_first(void)
{
	fprintf(stderr, "%s: ", __func__);
	int a[] = { 1, 2, 3, 4 };
	int data = 0;
	node_t *head = create_int_chain(a, sizeof a / sizeof a[0]);
	node_t *node = create_node(&data);
	insert(&head, node, head);
	int *b = create_int_array(head, 5);
	bool res = b[0] == 0 && b[1] == 1 && b[2] == 2 && b[3] == 3 && b[4] == 4;
	delete_chain(&head, NULL);
	free(b);
	return res;
}

bool test_insert_last(void)
{
	fprintf(stderr, "%s: ", __func__);
	int a[] = { 0, 1, 2, 3 };
	int data = 4;
	node_t *head = create_int_chain(a, sizeof a / sizeof a[0]);
	node_t *node = create_node(&data);
	insert(&head, node, NULL);
	int *b = create_int_array(head, 5);
	bool res = b[0] == 0 && b[1] == 1 && b[2] == 2 && b[3] == 3 && b[4] == 4;
	delete_chain(&head, NULL);
	free(b);
	return res;
}

bool test_insert_void(void)
{
	fprintf(stderr, "%s: ", __func__);
	int data = 10;
	node_t *head = NULL;
	node_t *node = create_node(&data);
	insert(&head, node, NULL);
	bool res = head && *(int *) head->data == data && !head->next;
	delete_node(&head, NULL);
	return res;
}

bool test_insert_fake(void)
{
	fprintf(stderr, "%s: ", __func__);
	int a[] = { 0, 1, 2, 3 };
	int data = 4;
	node_t *head = create_int_chain(a, sizeof a / sizeof a[0]);
	node_t *node = create_node(&data);
	insert(&head, node, node);
	size_t len_head = len(head);
	int *b = create_int_array(head, len_head);
	bool res = len_head == 4 && b[0] == 0 && b[1] == 1 && b[2] == 2 && b[3] == 3;
	delete_chain(&head, NULL);
	delete_node(&node, NULL);
	free(b);
	return res;
}

bool test_insert_nullptr(void)
{
	fprintf(stderr, "%s: ", __func__);
	insert(NULL, NULL, NULL);
	return true;
}

bool test_reverse_simple(void)
{
	fprintf(stderr, "%s: ", __func__);
	int a[] = { 0, 1, 2, 3, 4 };
	node_t *head = create_int_chain(a, sizeof a / sizeof a[0]);
	head = reverse(head);
	int *b = create_int_array(head, 5);
	bool res = b[0] == 4 && b[1] == 3 && b[2] == 2 && b[3] == 1 && b[4] == 0;
	delete_chain(&head, NULL);
	free(b);
	return res;
}

bool test_reverse_single(void)
{
	fprintf(stderr, "%s: ", __func__);
	int data = 10;
	node_t *node = create_node(&data);
	node = reverse(node);
	bool res = !node->next && *(int *) node->data == 10;
	delete_node(&node, NULL);
	return res;
}

bool test_reverse_nullptr(void)
{
	fprintf(stderr, "%s: ", __func__);
	return !reverse(NULL);
}

bool test_front_back_split_even(void)
{
	fprintf(stderr, "%s: ", __func__);
	int a[] = { 0, 1, 2, 3, 4 };
	node_t *head = create_int_chain(a, sizeof a / sizeof a[0]);
	node_t *back = NULL;
	front_back_split(head, &back);
	const size_t len_head = len(head);
	const size_t len_back = len(back);
	int *b = create_int_array(head, len_head);
	int *c = create_int_array(back, len_back);
	bool res = len_head == 3 && b[0] == 0 && b[1] == 1 && b[2] == 2;
	res &= len_back == 2 && c[0] == 3 && c[1] == 4;
	delete_chain(&head, NULL);
	delete_chain(&back, NULL);
	free(b);
	free(c);
	return res;
}

bool test_front_back_split_odd(void)
{
	fprintf(stderr, "%s: ", __func__);
	int a[] = { 0, 1, 2, 3, 4, 5};
	node_t *head = create_int_chain(a, sizeof a / sizeof a[0]);
	node_t *back = NULL;
	front_back_split(head, &back);
	const size_t len_head = len(head);
	const size_t len_back = len(back);
	int *b = create_int_array(head, len_head);
	int *c = create_int_array(back, len_back);
	bool res = len_head == 3 && b[0] == 0 && b[1] == 1 && b[2] == 2;
	res &= len_back == 3 && c[0] == 3 && c[1] == 4 && c[2] == 5;
	delete_chain(&head, NULL);
	delete_chain(&back, NULL);
	free(b);
	free(c);
	return res;
}

bool test_front_back_split_single(void)
{
	fprintf(stderr, "%s: ", __func__);
	int data = 10;
	node_t *node = create_node(&data);
	node_t *back = NULL;
	front_back_split(node, &back);
	bool res = *(int *) node->data == data && !node->next && !back;
	delete_node(&node, NULL);
	return res;
}

bool test_front_back_split_nullptr(void)
{
	fprintf(stderr, "%s: ", __func__);
	front_back_split(NULL, NULL);
	return true;
}

bool test_magnet_simple(void)
{
	fprintf(stderr, "%s: ", __func__);
	int a[] = { 1, 3, 5 };
	int b[] = { 0, 2, 4 };
	node_t *dest = create_int_chain(a, sizeof a / sizeof a[0]);
	node_t *src = create_int_chain(b, sizeof b / sizeof b[0]);
	magnet(&dest, &src);
	const size_t len_dest = len(dest);
	const size_t len_src = len(src);
	int *c = create_int_array(dest, len_dest);
	int *d = create_int_array(src, len_src);
	bool res = len_dest == 4 && c[0] == 0 && c[1] == 1 && c[2] == 3 && c[3] == 5;
	res &= len_src == 2 && d[0] == 2 && d[1] == 4;
	delete_chain(&dest, NULL);
	delete_chain(&src, NULL);
	free(c);
	free(d);
	return res;

}

bool test_magnet_nullptr(void)
{
	fprintf(stderr, "%s: ", __func__);
	node_t *dest = NULL;
	node_t *src = NULL;
	magnet(NULL, NULL);
	magnet(&dest, &src);
	return true;
}


bool test_sorted_merge_simple(void)
{
	fprintf(stderr, "%s: ", __func__);
	int a[] = { 0, 2, 4 };
	int b[] = { 1, 3, 5 };
	node_t *head_a = create_int_chain(a, sizeof a / sizeof a[0]);
	node_t *head_b = create_int_chain(b, sizeof b / sizeof b[0]);
	node_t *head = sorted_merge(&head_a, &head_b, compare_int);
	const size_t len_head = len(head);
	int *c = create_int_array(head, len_head);
	bool res = !head_a && !head_b && len_head == 6;
	res &= c[0] == 0 && c[1] == 1 && c[2] == 2 && c[3] == 3 && c[4] == 4 && c[5] == 5;
	delete_chain(&head, NULL);
	free(c);
	return res;
}

bool test_sorted_merge_trivial(void)
{
	fprintf(stderr, "%s: ", __func__);
	int a[] = { 3, 4, 5 };
	int b[] = { 0, 1, 2 };
	node_t *head_a = create_int_chain(a, sizeof a / sizeof a[0]);
	node_t *head_b = create_int_chain(b, sizeof b / sizeof b[0]);
	node_t *head = sorted_merge(&head_a, &head_b, compare_int);
	const size_t len_head = len(head);
	int *c = create_int_array(head, len_head);
	bool res = !head_a && !head_b && len_head == 6;
	res &= c[0] == 0 && c[1] == 1 && c[2] == 2 && c[3] == 3 && c[4] == 4 && c[5] == 5;
	delete_chain(&head, NULL);
	free(c);
	return res;
}

bool test_sorted_merge_nullptr(void)
{
	fprintf(stderr, "%s: ", __func__);
	sorted_merge(NULL, NULL, NULL);
	return true;
}

bool test_sort_simple(void)
{
	fprintf(stderr, "%s: ", __func__);
	int a[] = { 4, 3, 2, 1, 0 };
	node_t *head = create_int_chain(a, sizeof a / sizeof a[0]);
	head = sort(head, compare_int);
	const size_t len_head = len(head);
	int *b = create_int_array(head, len_head);
	bool res = len_head == 5;
	res &= b[0] == 0 && b[1] == 1 && b[2] == 2 && b[3] == 3 && b[4] == 4;
	delete_chain(&head, NULL);
	free(b);
	return res;
}

bool test_sort_nullptr(void)
{
	fprintf(stderr, "%s: ", __func__);
	return !sort(NULL, NULL);
}
