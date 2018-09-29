#include "interface.h"

int check_filenames(int argc, char *argv[])
{
	assert(argc == 4 || argc == 5);

	if (!strcmp(argv[2], argv[3]))
	{
		return SAME_FILENAMES_ERROR;
	}

	if (argc == 4)
	{
		return SUCCESS;
	}

	if (!strcmp(argv[2], argv[4]) || !strcmp(argv[3], argv[4]))
	{
		return SAME_FILENAMES_ERROR;
	}

	return SUCCESS;
}

int check_args(int argc, char *argv[], action_t *action)
{
	int rc;
	if (argc < 2 || argc > 5 || (rc = set_action(argv[1], action)) != SUCCESS)
	{
		return WRONG_USAGE_ERROR;
	}

	if (*action == help)
	{
		return argc == 5 ? SUCCESS : WRONG_USAGE_ERROR;
	}

	bool c1 = argc == 4 && *action == solve;
	bool c2 = argc == 5 && (*action == add || *action == multiply);

	if (c1 || c2)
	{
		return check_filenames(argc, argv);
	}

	return WRONG_USAGE_ERROR;
}

int open_files(int argc, char *argv[], FILE **mtr_1, FILE **mtr_2, FILE **res)
{
	char **iargv = argv + 2;
	if (!(*mtr_1 = fopen(*iargv, "r")))
	{
		perror(*iargv);
		return OPEN_FILE_ERROR;
	}

	if (argc == 5)
	{
		if (!(*mtr_2 = fopen(*++iargv, "r")))
		{
			perror(*iargv);
			return OPEN_FILE_ERROR;
		}
	}

	if (!(*res = fopen(*++iargv, "w")))
	{
		perror(*iargv);
		return OPEN_FILE_ERROR;
	}

	return SUCCESS;
}

void close_files(FILE **mtr_1, FILE **mtr_2, FILE **res)
{
	if (*mtr_1)
	{
		fclose(*mtr_1);
		*mtr_1 = NULL;
	}

	if (*mtr_2)
	{
		fclose(*mtr_2);
		*mtr_2 = NULL;
	}

	if (*res)
	{
		fclose(*res);
		*res = NULL;
	}
}

int do_action(action_t action, FILE *mtr_1, FILE *mtr_2, FILE *res)
{
	assert(action != help);

	int rc;
	matrix_t a, b, c;
	if ((rc = get_matrix_1(mtr_1, &a)) != SUCCESS)
	{
		goto fin;
	}

	if (action == solve)
	{
		if ((rc = solve_matrix(&a, &c)) != SUCCESS)
		{
			goto free_a;
		}
	}
	else
	{
		if ((rc = get_matrix_1(mtr_2, &b)) != SUCCESS)
		{
			goto free_a;
		}

		if (action == add)
		{
			if ((rc = add_matrices(&a, &b, &c)) != SUCCESS)
			{
				goto free_b;
			}
		}
		else if ((rc = multiply_matrices(&a, &b, &c)) != SUCCESS)
		{
			goto free_b;
		}
	}

	write_matrix_2(res, &c);

	free_matrix(&c);

	free_b:
	if (action != solve)
	{
		free_matrix(&b);
	}

	free_a:
		free_matrix(&a);

	fin:
		return rc;
}
