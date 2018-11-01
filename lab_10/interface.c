#include "interface.h"

int check_filenames(const char *filename1, const char *filename2)
{
	return strcmp(filename1, filename2) ? EXIT_SUCCESS : SAME_FILENAMES_ERROR;
}

int check_args(int argc, char *argv[])
{
	if (argc != 3)
		return WRONG_USAGE_ERROR;

	return check_filenames(argv[1], argv[2]);
}

int open_files(const char *s1, const char *s2, FILE **input, FILE **output)
{
	if (!(*input = fopen(s1, "r")) || !(*output = fopen(s2, "w")))
		return OPEN_FILE_ERROR;

	return EXIT_SUCCESS;
}

void close_files(FILE *input, FILE *output)
{
	fclose(input);
	fclose(output);
}

int solve(FILE *input, FILE *output)
{
	int size, max_revenue = 0;
	node_t *exchange;
	int rc;
	if ((rc = read_file(input, &size, &exchange)) != EXIT_SUCCESS)
		return rc;

	while (size)
	{
		int i;
		node_t *max_node = max(exchange, &i, compare_int);
		int days = size - i;
		max_revenue += *(int *) max_node->data * days;
		for (int i = 0; i != days; ++i)
			free(pop_back(&exchange));
		size -= days;
	}

	fprintf(output, "%d\n", max_revenue);

	return EXIT_SUCCESS;
}

// in *head will be reversed input
int read_file(FILE *input, int *size, node_t **head)
{
	int sz, rc;
	if ((rc = fscanf(input, "%d", &sz)) != 1)
		return rc ? EMPTY_FILE_ERROR : INVALID_FILE_ERROR;

	if (sz <= 0 || sz >= LIMIT)
		return INVALID_FILE_ERROR;

	*size = sz;
	*head = NULL;

	for (int i = 0; i != sz; ++i)
	{
		node_t *node = fget_node(fget_int_data, input);
		if (!node)
		{
			delete_chain(head, simple_free);
			return FGET_NODE_ERROR;
		}
		insert(head, node, *head);
	}

	return EXIT_SUCCESS;
}
