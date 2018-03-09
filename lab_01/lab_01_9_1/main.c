/*
 * Программа считает и выводит на экран периметр равнобедренной
 * трапеции по основаниям и высоте.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//только ради дефайна как такового
#define FINE 0

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		puts("Usage: ./isosceles_trapezoid base1 base2 height");
		return 1;
	}

	float base1 = atof(argv[1]);
	float base2 = atof(argv[2]);
	float height = atof(argv[3]);

	float side = sqrt(pow((base2 - base1) / 2.0f, 2) + pow(height, 2));
	float perimetr = base1 + base2 + 2 * side;
	printf("Perimetr: %.4f\n", perimetr);

	return FINE;
}
