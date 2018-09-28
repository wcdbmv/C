#include "interface.h"

int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	int rc = SUCCESS;

	action_t action;
	if ((rc = check_args(argc, argv, &action)) != SUCCESS)
	{
		my_perror(rc);
		return rc;
	}

	if (action == help)
	{
		show_info();
		return SUCCESS;
	}

	FILE *mtr_1 = NULL, *mtr_2 = NULL, *res = NULL;
	if ((rc = open_files(argc, argv, &mtr_1, &mtr_2, &res)) == SUCCESS)
	{
		rc = do_action(action, mtr_1, mtr_2, res);
		close_files(&mtr_1, &mtr_2, &res);
	}

	my_perror(rc);
	return rc;
}
