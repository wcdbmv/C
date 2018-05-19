#include <stdio.h>
#include "array.h"

int main(int argc, char **argv)
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	if (argc != 2)
	{
		my_perror(BAD_USAGE);
		return BAD_USAGE;
	}

	const char *file_name = *(argv + 1);
	int a[N], *end_a = NULL;
	FILE *file = fopen(file_name, "r");
	if (file != NULL)
	{
		int rc;
		if ((rc = read_array(file, a, &end_a)) == SUCCESS)
		{
			int different = count_different(a, end_a);
			printf("different: %d\n", different);
		}
		else
		{
			my_perror(rc);
			return rc;
		}
		fclose(file);
	}
	else
	{
		perror("fopen");
		return CANT_OPEN_FILE;
	}

	return SUCCESS;
}

void my_perror(int rc)
{
	if (rc == BAD_USAGE)
	{
		fprintf(stderr, "Usage: ./different <file>\n");
	}
	else if (rc == EMPTY_FILE)
	{
		fprintf(stderr, "File is empty\n");
	}
	else if (rc == INVALID_FILE_INPUT)
	{
		fprintf(stderr, "Invalid input\n");
	}
}
