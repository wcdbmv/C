#include "interface.h"

#include <stdio.h>
#include <string.h>
#include "errcodes.h"

int check_args(int argc, char **argv, bool *filter)
{
	if (argc == 4)
	{
		if (strcmp(argv[3], "f"))
		{
			return WRONG_USAGE;
		}
		else
		{
			*filter = true;
		}
	}
	else if (argc != 3)
	{
		return WRONG_USAGE;
	}
	return SUCCESS;
}

int my_perror(int errcode)
{
	switch (errcode)
	{
		case WRONG_USAGE:
			fprintf(stderr, "Usage: app.exe in_file out_file [f]\n");
			break;
		case SAME_FILENAMES:
			fprintf(stderr, "Please, use different filenames\n");
			break;
		case EMPTY_INPUT_FILE:
			fprintf(stderr, "Input file is empty\n");
			break;
		case EMPTY_FILTERED_ARRAY:
			fprintf(stderr, "Array is empty after filtration\n");
			break;
		case INVALID_INPUT_FILE_SYNTAX:
			fprintf(stderr, "Input file has invalid syntax\n");
			break;
	}

	return errcode;
}
