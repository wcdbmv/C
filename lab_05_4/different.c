#include <stdio.h>

#define N 100

#define SUCCESS 0
#define BAD_USAGE -1
#define CANT_OPEN_FILE -2
#define EMPTY_FILE -3
#define INVALID_FILE_INPUT -4

int check_valid(FILE *file);
void my_perror(int rc);
int overflowed(FILE *file);
void read_array(FILE *file, int *begin_a, int **end_a);
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
	FILE *file = fopen(file_name, "r");
	if (file != NULL)
	{
		int rc;
		if ((rc = check_valid(file)) == SUCCESS)
		{
			rewind(file);
			if (overflowed(file))
			{
				printf("Note: There are more then %d numbers in the file.\n", N);
			}
			rewind(file);
			int a[N], *end_a = NULL;
			read_array(file, a, &end_a);
			printf("different: %d\n", count_different(a, end_a));
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

int check_valid(FILE *file)
{
	int i;
	int rc;
	if ((rc = fscanf(file, "%d", &i)) == 1)
	{
		while ((rc = fscanf(file, "%d", &i)) == 1)
			;
		if (rc == EOF)
		{
			return SUCCESS;
		}
		return INVALID_FILE_INPUT;
	}
	else if (rc == EOF)
	{
		return EMPTY_FILE;
	}
	else
	{
		return INVALID_FILE_INPUT;
	}
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

int overflowed(FILE *file)
{
	int i;
	int count;
	while (fscanf(file, "%d", &i) != EOF)
	{
		++count;
	}
	return count > N ? 1 : 0;
}

void read_array(FILE *file, int *begin_a, int **end_a)
{
	int *pa = begin_a;
	for (int i = 0; i != N; ++i)
	{
		if (fscanf(file, "%d", pa++) == EOF)
		{
			--pa;
			break;
		}
	}
	*end_a = pa;
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
