#include "info.h"
#include "errcodes.h"

void my_perror(int errcode)
{
	switch (errcode) {
		case INVALID_FILE:
			fprintf(stderr, "Invalid file.\n");
			break;
		case UNEXPECTED_EOF:
			fprintf(stderr, "Unexpected EOF.\n");
			break;
		case FAILED_ALLOC:
			fprintf(stderr, "Failed alloc.\n");
			break;
		case NEGATIVE_SIZE:
			fprintf(stderr, "Negative size.\n");
			break;
		case NEGATIVE_ANSWER:
			fprintf(stderr, "Negative answer.\n");
			break;
	}
}
