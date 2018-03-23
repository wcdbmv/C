#include <stdio.h>

const float EPS = 1e-9;

int main(void)
{
	setbuf(stdout, NULL);

	float x, y;
	printf("Input x, y: ");
	if (scanf("%f%f", &x, &y) < 2)
	{
		printf("x and y must be numbers.\n");
		return 1;
	}

	float a, b, c;
	printf("Input A, B, C: ");
	if (scanf("%f%f%f", &a, &b, &c) < 3)
	{
		printf("A, B and C must be numbers.\n");
		return 2;
	}

	if (!a && !b)
	{
		printf("0x + 0y + %.1f = 0 is not a line.\n", c);
		return 3;
	}

	float p = a*x + b*y + c;

	printf("Point (%.1f, %.1f) is ", x, y);
	if (p > EPS)
	{
		printf("above");
	}
	else if (p < -EPS)
	{
		printf("below");
	}
	else
	{
		printf("on");
	}
	printf(" the line %.1fx + %.1fy + %.1f = 0\n", a, b, c);

	return 0;
}
