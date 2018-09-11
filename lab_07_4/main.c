#include <string.h>
#include <stdbool.h>
#include "array_io.h"
#include "sort.h"
#include "error.h"

int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	int rc = SUCCESS;

	bool filter = false;

	if (argc == 4)
	{
		if (strcmp(argv[3], "f"))
		{
			rc = WRONG_USAGE;
			goto fin;
		}
		else
		{
			filter = true;
		}
	}
	else if (argc != 3)
	{
		rc = WRONG_USAGE;
		goto fin;
	}

	const char *input_filename = argv[1];
	const char *output_filename = argv[2];

	if (!strcmp(input_filename, output_filename))
	{
		rc = SAME_FILENAMES;
		goto fin;
	}

	FILE *input_file = fopen(input_filename, "r");
	if (!input_file)
	{
		perror(input_filename);
		rc = CANT_OPEN_INPUT_FILE;
		goto fin;
	}

	FILE *output_file = fopen(output_filename, "w");
	if (!output_file)
	{
		perror(output_filename);
		rc = CANT_OPEN_OUTPUT_FILE;
		goto close_input;
	}

	rc = count_array_size(input_file);
	if (rc <= 0)
	{
		goto close_output;
	}
	int size = rc;
	rewind(input_file);

	int *pb = NULL, *pe = NULL;
	rc = get_array(input_file, &pb, &pe, size);
	if (rc == FAILED_MALLOC)
	{
		perror("malloc");
		goto close_output;
	}

	if (filter)
	{
		int *old_pb = pb, *old_pe = pe;
		rc = key(old_pb, old_pe, &pb, &pe);
		free(old_pb);
		old_pb = old_pe = NULL;
		if (rc == EMPTY_FILTERED_ARRAY)
		{
			goto close_output;
		}
		size = rc;
	}

	my_sort(pb, pe - pb, sizeof (int), compare_int);
	write_array(output_file, pb, pe);
	free(pb);

	rc = SUCCESS;

close_output:
	fclose(output_file);

close_input:
	fclose(input_file);

fin:
	my_perror(rc);
	return rc;
}
