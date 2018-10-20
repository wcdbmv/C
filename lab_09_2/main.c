#include "interface.h"

int main(int argc, char *argv[])
{
	int rc;
	if ((rc = check_args(argc, argv)) == SUCCESS)
	{
		FILE *input, *output;
		if ((rc = open_files(argv[1], argv[2], &input, &output)) == SUCCESS)
		{
			rc = fstr_replace(input, output, argv[4], argv[6]);
			close_files(input, output);
		}
	}

	my_perror(rc);
	return rc;
}
