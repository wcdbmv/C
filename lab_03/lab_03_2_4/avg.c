#include <stdio.h>

#define INVALID_COMMAND_LINE_ARGUMENTS -1
#define CANT_OPEN_FILE -2
#define NO_INPUT -3
#define INVALID_INPUT -4
#define NO_NUMBERS_BETWEEN_MAX_AND_MIN -5
#define SEVERAL_MAX_OR_MIN -6

int avg(FILE *istream);
int find_ij(FILE *istream, int *i, int *j);
void template_assignment(float, float, float *, float, int *, int, int *);

int main(int argc, char **argv)
{
	setbuf(stdout, NULL);

	if (argc != 2)
	{
		printf("Usage: ./avg <file>\n");
		return INVALID_COMMAND_LINE_ARGUMENTS;
	}

	FILE *f_in = fopen(argv[1], "r");
	if (f_in == NULL)
	{
		fprintf(stderr, "Can't open %s\n", argv[1]);
		return CANT_OPEN_FILE;
	}

	int rc = avg(f_in);

	fclose(f_in);
	return rc;
}

int avg(FILE *istream)
{
	int i = 0, j = 0;
	int rc = find_ij(istream, &i, &j);
	if (rc)
	{
		return rc;
	}
	float curr;
	for (int k = 0; k <= i; ++k)
	{
		fscanf(istream, "%f", &curr);
	}
	float sum = 0.0f;
	for (int k = i + 1; k < j; ++k)
	{
		fscanf(istream, "%f", &curr);
		sum += curr;
	}
	printf("%.1f\n", sum / (j - i - 1.0f));
	rewind(istream);
	return 0;
}

int find_ij(FILE *istream, int *i, int *j)
{
	float curr;
	int rc = fscanf(istream, "%f", &curr);
	if (rc == EOF)
	{
		fprintf(stderr, "No input data in file.\n");
		return NO_INPUT;
	}
	if (!rc)
	{
		fprintf(stderr, "Invalid input.\n");
		return INVALID_INPUT;
	}
	int i_min = 0, i_max = 0, i_curr = 0;
	float min = curr, max = curr;
	int count_min = 1, count_max = 1;
	while ((rc = fscanf(istream, "%f", &curr)) != EOF)
	{
		if (!rc)
		{
			fprintf(stderr, "Invalid input.\n");
			return INVALID_INPUT;
		}
		++i_curr;
		template_assignment(curr, min, &min, curr, &i_min, i_curr, &count_min);
		template_assignment(max, curr, &max, curr, &i_max, i_curr, &count_max);
	}
	if (count_min + count_max != 2)
	{
		fprintf(stderr, "There are several maxima or minima.\n");
		return SEVERAL_MAX_OR_MIN;
	}
	*i = i_min;
	*j = i_max;
	if (*i > *j)
	{
		*i = i_max;
		*j = i_min;
	}
	if (*j - *i < 2)
	{
		fprintf(stderr, "There are not numbers between max and min.\n");
		return NO_NUMBERS_BETWEEN_MAX_AND_MIN;
	}
	rewind(istream);
	return 0;
}

void template_assignment(
		float left, float right,
		float *extrem, float curr,
		int *i_extrem, int i_curr,
		int *count_extrem)
{
	if (left < right)
	{
		*extrem = curr;
		*i_extrem = i_curr;
		*count_extrem = 1;
	}
	else if (left == right)
	{
		++*count_extrem;
	}
}
