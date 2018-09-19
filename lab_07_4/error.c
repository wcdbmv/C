#include "error.h"

void my_perror(int error)
{
	switch (error)
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
}
