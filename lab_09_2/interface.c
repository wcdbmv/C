#include "interface.h"

int check_args(int argc, char *argv[])
{
	if (argc != 7 || my_strcmp(argv[3], "-s") || my_strcmp(argv[5], "-r"))
		return WRONG_USAGE_ERROR;

	return SUCCESS;
}

int open_files(const char *argv1, const char *argv2, FILE **in, FILE **out)
{
	if (!my_strcmp(argv1, argv2))
		return SAME_FILENAMES_ERROR;

	if (!(*in = fopen(argv1, "r")))
	{
		perror(argv1);
		return CANT_OPEN_FILE;
	}

	if (!(*out = fopen(argv2, "w")))
	{
		perror(argv2);
		return CANT_OPEN_FILE;
	}

	return SUCCESS;
}

int fstr_replace(FILE *in, FILE *out, const char *search, const char *replace)
{
	int rc;
	if (!*search)
		return EMPTY_SEARCH_STRING_ERROR;
	char *source = NULL;
	size_t n = 0;
	size_t lines = 0;
	while ((rc = my_getline(&source, &n, in)) != EOF)
	{
		++lines;
		char *destination = str_replace(source, search, replace);
		if (!destination)
			return FAILED_ALLOC_ERROR;
		fputs(destination, out);
		free(destination);
	}
	if (source)
		free(source);
	if (!lines)
		return EMPTY_INPUT_FILE_ERROR;

	return SUCCESS;
}

void close_files(FILE *in, FILE *out)
{
	fclose(in);
	fclose(out);
}
