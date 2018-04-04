#include <stdio.h>

#define NO_INPUT -1
#define INVALID_INPUT -2
#define NO_POS_AFTER_NEG -3

int process(FILE *istream);

int main(void)
{
	setbuf(stdout, NULL);

	return process(stdin);
}

int process(FILE *istream)
{
	int prev = 0, curr = 0;
	int max_pos_after_neg = 0;
	int error = fscanf(istream, "%d", &prev);
	if (error == EOF)
	{
		return NO_INPUT;
	}
	if (!error)
	{
		return INVALID_INPUT;
	}
	while ((error = fscanf(istream, "%d", &curr)) != EOF)
	{
		if (!error)
		{
			return INVALID_INPUT;
		}
		if (prev < 0 && curr > 0 && curr > max_pos_after_neg)
		{
			max_pos_after_neg = curr;
		}
		prev = curr;
	}
	if (!max_pos_after_neg)
	{
		return NO_POS_AFTER_NEG;
	}
	printf("%d\n", max_pos_after_neg);
	return 0;
}
