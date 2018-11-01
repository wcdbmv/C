#include "info.h"

void usage(void)
{
	fprintf(stderr, "Usage: app.exe input.txt output.txt\n");
}

void my_perror(int errcode)
{
	switch (errcode) {
		case WRONG_USAGE_ERROR:
			usage();
			break;
		case SAME_FILENAMES_ERROR:
			fprintf(stderr, "Please use different filenames.\n");
			break;
		case OPEN_FILE_ERROR:
			perror("open file");
			break;
		case EMPTY_FILE_ERROR:
			fprintf(stderr, "Input file is empty.\n");
			break;
		case INVALID_FILE_ERROR:
			fprintf(stderr, "Invalid input file.\n");
			break;
		case FGET_NODE_ERROR:
			fprintf(stderr, "fget_node: error\n");
			break;
	}
}
