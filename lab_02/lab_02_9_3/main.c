#include <stdio.h>
#include <math.h>

double s(double x, double eps);
double f(double x);

int main(void)
{
	setbuf(stdout, NULL);

	double x;
	printf("Input x: ");
	if (scanf("%lf", &x) < 1)
	{
		printf("x must be a number.\n");
		return 1;
	}

	double eps;
	printf("Input eps: ");
	if (scanf("%lf", &eps) < 1 || eps <= 0.0)
	{
		printf("eps must be a positive number.\n");
		return 2;
	}

	double sx = s(x, eps);
	double fx = f(x);
	double absolute_error = fabs(sx - fx);
	double relative_error = fabs(absolute_error / fx);

	printf("s(%.1lf) = %.4e\n", x, sx);
	printf("f(%.1lf) = %.4e\n", x, fx);
	printf("absolute error: %.4e\n", absolute_error);
	printf("relative error: %.4e\n", relative_error);

	return 0;
}

double s(double x, double eps)
{
	long long i = 1;
	double t = x;
	double res = t;
	while (fabs(t) > eps)
	{
		i += 2;
		t *= (2 - i) * x * x / i;
		res += t;
	}
	return res;
}

double f(double x)
{
	return atan(x);
}
