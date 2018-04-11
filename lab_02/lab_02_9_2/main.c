#include <stdio.h>

int input(float *x, float *y, float *k, float *b);
void compare(float x, float y, float k, float b);

int main(void)
{
	setbuf(stdout, NULL);

	float x, y;
	float k, b;
	if (input(&x, &y, &k, &b))
	{
		return 1;
	}

	compare(x, y, k, b);
	
	return 0;
}

int input(float *x, float *y, float *k, float *b)
{
	printf("Input x, y: ");
	if (scanf("%f%f", x, y) < 2)
	{
		printf("x and y must be numbers.\n");
		return 1;
	}
	
	printf("Input k, b: ");
	if (scanf("%f%f", k, b) < 2)
	{
		printf("k and b must be numbers.\n");
		return 2;
	}
	
	return 0;
}

void compare(float x, float y, float k, float b)
{
	float yx = k*x + b;
	printf("Point (%.1f, %.1f) is ", x, y);
	if (y > yx)
	{
		printf("above");
	}
	else if (y < yx)
	{
		printf("below");
	}
	else
	{
		printf("on");
	}
	printf(" the line y = %.1fx%+.1f\n", k, b);
}
