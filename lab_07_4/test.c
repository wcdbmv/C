#include <string.h>
#include "filter.h"
#include "sort.h"
#include "comparator.h"

void test_my_sort_random(void)
{
	int a[] = {2, 0, 4, 1, 3};

	my_sort(a, 5, sizeof (int), compare_int);

	char status[] = "failed";
	if (a[0] == 0 && a[1] == 1 && a[2] == 2 && a[3] == 3 && a[4] == 4)
		strcpy(status, "passed");

	printf("test_my_sort_random: %s\n", status);
}

void test_my_sort_sorted(void)
{
	int a[] = {0, 1, 2, 3, 4};

	my_sort(a, 5, sizeof (int), compare_int);

	char status[] = "failed";
	if (a[0] == 0 && a[1] == 1 && a[2] == 2 && a[3] == 3 && a[4] == 4)
		strcpy(status, "passed");

	printf("test_my_sort_sorted: %s\n", status);
}

void test_my_sort_reversed(void)
{
	int a[] = {4, 3, 2, 1, 0};

	my_sort(a, 5, sizeof (int), compare_int);

	char status[] = "failed";
	if (a[0] == 0 && a[1] == 1 && a[2] == 2 && a[3] == 3 && a[4] == 4)
		strcpy(status, "passed");

	printf("test_my_sort_reversed: %s\n", status);
}

void test_key_simple(void)
{
	int *old_pb = malloc(5 * sizeof (int));
	int *old_pe = old_pb + 5;

	old_pb[0] = 0, old_pb[1] = 1, old_pb[2] = 2, old_pb[3] = 3, old_pb[4] = 4;

	int *pb = NULL, *pe = NULL;

	int size = key(old_pb, old_pe, &pb, &pe);
	free(old_pb);

	char status[] = "failed";
	if (size == 2 && pb[0] == 3 && pb[1] == 4 && pe == pb + 2)
		strcpy(status, "passed");

	printf("test_key_simple: %s\n", status);
	free(pb);
}

void test_key_empty_output(void)
{
	int *old_pb = malloc(5 * sizeof (int));
	int *old_pe = old_pb + 5;

	old_pb[0] = 0, old_pb[1] = 0, old_pb[2] = 0, old_pb[3] = 0, old_pb[4] = 0;

	int *pb = NULL, *pe = NULL;

	int rc = key(old_pb, old_pe, &pb, &pe);
	free(old_pb);

	char status[] = "failed";
	if (rc == EMPTY_FILTERED_ARRAY)
		strcpy(status, "passed");

	printf("test_key_empty_output: %s\n", status);
	free(pb);
}

int main(void)
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	test_my_sort_random();
	test_my_sort_sorted();
	test_my_sort_reversed();

	test_key_simple();
	test_key_empty_output();
}
