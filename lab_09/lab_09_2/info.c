#include "info.h"

void usage(void)
{
	fprintf(stderr, "Usage: app.exe in.txt out.txt –s search –r replace\n");
}

void my_perror(int errcode)
{
	switch (errcode) {
		case WRONG_USAGE_ERROR:
			usage();
			break;
		case SAME_FILENAMES_ERROR:
			fprintf(stderr, "Please, use different filenames\n");
			break;
		case READ_FILE_ERROR:
			perror("input file");
			break;
		case FAILED_ALLOC_ERROR:
			perror("alloc");
			break;
		case EMPTY_SEARCH_STRING_ERROR:
			fprintf(stderr, "Empty search string\n");
			break;
	}
}
