/*
 * Программа определяет нормальный вес человека и индекс массы его тела
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		puts("Usage: ./human height mass chest");
		return 1;
	}

	float height = atof(argv[1]);
	float mass = atof(argv[2]);
	float chest = atof(argv[3]);

	float normal_weight = height * chest / 240.0f;
	height /= 100;
	float body_mass_index = mass / height / height;
	printf("Normal weight: %.1f\n", normal_weight);
	printf("Body mass index: %.1f\n", body_mass_index);

	return 0;
}
