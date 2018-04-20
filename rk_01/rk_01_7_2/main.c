/*
 * type - int
 * end - X = 99
 * divided by Y = 7
 */

#include <stdio.h>

#define X 99
#define Y 7

int main(void)
{
	setbuf(stdout, NULL);

	printf("Input sequence: ");
	int n = 1;
	int i = 0, pos = -1;
	int rc;
	while ((rc = scanf("%d", &n)) == 1 && n != X)
	{
		if (n % Y == 0)
		{
			pos = i;
			break;
		}
		++i;
	}

	if (~pos) // pos != -1
	{
		printf("There is number divided by %d in position %d.\n", Y, pos);
	}
	else
	{
		printf("There are not numbers divided by %d.\n", Y);
	}

	return 0;
}