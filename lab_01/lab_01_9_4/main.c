/*
 * Программа считает какое наибольшее количество бутылок воды по 45 копеек вы
 * можете купить за S копеек, если продавать пустые бутылки можно за 20 копеек.
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		puts("Usage: ./bottles cash");
		return 1;
	}

	const int purchase = 45;
	const int sale = 20;

	int cash = atoi(argv[1]);
	int bottles = (cash - sale) / (purchase - sale);
	printf("%d\n", bottles);

	return 0;
}
