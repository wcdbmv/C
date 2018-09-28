#include "info.h"

void usage(FILE *stream)
{
	fputs("Usage: app.exe action mtr_1.txt [mtr_2.txt] res.txt\n", stream);
	fputs("actions:\n", stream);
	fputs("  a       add\n", stream);
	fputs("  m       multiply\n", stream);
	fputs("  o       solve SLAE (without mtr_2.txt)\n", stream);
	fputs("  h       help (without *.txt)\n", stream);
}

void show_info(void)
{
	usage(stdout);

	puts("\nformats of matrices:");
	puts("  input    simple");
	puts("  output   coordinate");
}

void my_perror(const int errcode)
{
	switch (errcode)
	{
		case WRONG_USAGE_ERROR:
			usage(stderr);
			break;
		case SAME_FILENAMES_ERROR:
			fprintf(stderr, "Please, use different files\n");
			break;
		case INVALID_INPUT_FILE_ERROR:
			fprintf(stderr, "Can't read matrix\n");
			break;
		case FAILED_MALLOC_ERROR:
			perror("malloc");
			break;
		case MATRICES_SIZES_ERROR:
			fprintf(stderr, "Error while compare sizes\n");
			break;
		case INCOMPATIBLE_SLAE_ERROR:
			fprintf(stderr, "There are no solutions\n");
			break;
	}
}
