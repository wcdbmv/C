#include <stdio.h>

#define N 100

#define SUCCESS 0
#define BAD_USAGE -1
#define CANT_OPEN_FILE -2
#define EMPTY_FILE -3
#define INVALID_FILE_INPUT -4

void my_perror(int rc);
int read_array(FILE *file, int *a, int **end_a);
int check_overflow(FILE *file);
int count_different(int *begin_a, int *end_a);

int main(int argc, char **argv)
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	if (argc != 2)
	{
		my_perror(BAD_USAGE);
		return BAD_USAGE;
	}

	const char *file_name = *(argv + 1);
	int a[N], *end_a = NULL;
	FILE *file = fopen(file_name, "r");
	if (file != NULL)
	{
		int rc;
		if ((rc = read_array(file, a, &end_a)) == SUCCESS)
		{
			int different = count_different(a, end_a);
			printf("different: %d\n", different);
		}
		else
		{
			my_perror(rc);
			return rc;
		}
		fclose(file);
	}
	else
	{
		perror("fopen");
		return CANT_OPEN_FILE;
	}

	return SUCCESS;
}

void my_perror(int rc)
{
	switch (rc)
	{
		case BAD_USAGE:
			fprintf(stderr, "Usage: ./different <file>\n");
			break;
		case EMPTY_FILE:
			fprintf(stderr, "File is empty\n");
			break;
		case INVALID_FILE_INPUT:
			fprintf(stderr, "Invalid input\n");
			break;
	}
}

int read_array(FILE *file, int *a, int **end_a)
{
	int rc;
	for (int i = 0; i != N; ++i)
	{
		if ((rc = fscanf(file, "%d", a++)) == EOF)
		{
			if (i)
			{
				*end_a = --a;
				return SUCCESS;
			}
			return EMPTY_FILE;
		}
		if (!rc)
		{
			return INVALID_FILE_INPUT;
		}
	}
	*end_a = a;
	rc = check_overflow(file);
	return rc;
}

int check_overflow(FILE *file)
{
	int tmp, rc, i = 0;
	while ((rc = fscanf(file, "%d", &tmp)) == 1)
	{
		++i;
	}
	if (!rc)
	{
		return i ? INVALID_FILE_INPUT : SUCCESS;
	}
	if (i)
	{
		fprintf(stderr, "Note: There are more then %d numbers in the file.\n", N);
	}
	return SUCCESS;
}

int count_different(int *begin_a, int *end_a)
{
	int *p1 = begin_a + 1;
	int res = 1;
	while (p1 < end_a)
	{
		int *p2 = begin_a;
		int flag_repeat = 1;
		while (p2 < p1)
		{
			if (*p2 == *p1)
			{
				flag_repeat = 0;
				break;
			}
			++p2;
		}
		res += flag_repeat;
		++p1;
	}
	return res;
}
