/*
Вычисляет площадь прямоугольника.
*/

#include <stdio.h>

#define PI 3.14f

float square_rectangle(float a, float b);
float square_circle(float r);

int main(void)
{
	float a, b;
	float sr;

	printf("Input a and b: ");
	scanf("%f%f",&a, &b);

	sr = square_rectangle(a, b);

	printf("Square of rectangle is %8.3f\n", sr);

	float r;
	float sc;

	printf("Input r: ");
	scanf("%f", &r);

	sc = square_circle(r);

	printf("Square of circle is %8.3f\n", sc);

	return 0;
}

float square_rectangle(float a, float b)
{
	return a * b;
}

float square_circle(float r)
{
	return PI * r * r;
}
