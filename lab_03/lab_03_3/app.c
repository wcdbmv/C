/*
 * Программа сортирует содержимое бинарного файла
 *     ТИП СЧИТЫВАЕМОГО ЧИСЛА: int (int32_t);
 *     АЛГОРИТМ СОРТИРОВКИ: selection sort (по возрастанию);
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void usage(void);
int touch(char *file_name);
int cat(char *file_name);
int sort(char *file_name);
void selection_sort(FILE *file);
int length(FILE *file);
void swap(FILE *file, int i, int j);
int get_number_by_pos(FILE *file, int i);
void put_number_by_pos(FILE *file, int n, int i);

int main(int argc, char **argv)
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	if (argc != 3)
	{
		usage();
		return -1;
	}

	int rc;
	if (strcmp(argv[1], "touch") == 0)
	{
		rc = touch(argv[2]);
	}
	else if (strcmp(argv[1], "cat") == 0)
	{
		rc = cat(argv[2]);
	}
	else if (strcmp(argv[1], "sort") == 0)
	{
		rc = sort(argv[2]);
	}
	else
	{
		fprintf(stderr, "'%s': no such action name.\n", argv[1]);
		return -2;
	}

}

void usage(void)
{
	printf("Usage: ./app <action> <file>\n");
	printf("  actions: touch, cat, sort\n");
}

int touch(char *file_name)
{
	if (strcmp(file_name, "app.c") == 0)
	{
		fprintf(stderr, "touch: Permission denied\n");
		return -3;
	}
	FILE *file = fopen(file_name, "wb");
	if (file == NULL)
	{
		perror("touch");
		return -4;
	}
	srand(time(NULL));
	for (int i = 0; i != 20; ++i)
	{
		int n = rand() % 100;
		fwrite(&n, 1, sizeof n, file);
	}
	fclose(file);
	return 0;
}

int cat(char *file_name)
{
	if (strcmp(file_name, "app.c") == 0)
	{
		fprintf(stderr, "cat: Permission denied\n");
		return -3;
	}
	FILE *file = fopen(file_name, "rb");
	if (file == NULL)
	{
		perror("cat");
		return -5;
	}
	int n;
	while (1)
	{
		fread(&n, 1, sizeof n, file);
		if (feof(file))
		{
			break;
		}
		printf("%d ", n);
	}
	printf("\n");

	fclose(file);
	return 0;
}

int sort(char *file_name)
{
	if (strcmp(file_name, "app.c") == 0)
	{
		fprintf(stderr, "sort: Permission denied\n");
		return -3;
	}
	FILE *file = fopen(file_name, "r+b");
	if (file == NULL)
	{
		perror("sort");
		return -6;
	}
	selection_sort(file);
	return 0;
}

void selection_sort(FILE *file)
{
	int n = length(file);
	for (int i = 0; i < n - 1; ++i)
	{
		int i_min = i;
		int min = get_number_by_pos(file, i_min);
		for (int j = i + 1; j < n; ++j)
		{
			int curr = get_number_by_pos(file, j);
			if (min > curr)
			{
				i_min = j;
				min = curr;
			}
		}
		swap(file, i, i_min);
	}
}

int length(FILE *file)
{
	int res = 0;
	int tmp;
	while (1)
	{
		fread(&tmp, 1, sizeof tmp, file);
		if (feof(file))
		{
			break;
		}
		++res;
	}
	return res;
}

void swap(FILE *file, int i, int j)
{
	int a = get_number_by_pos(file, i);
	int b = get_number_by_pos(file, j);
	put_number_by_pos(file, b, i);
	put_number_by_pos(file, a, j);
}

int get_number_by_pos(FILE *file, int i)
{
	int tmp;
	fseek(file, i * (sizeof tmp), SEEK_SET);
	fread(&tmp, 1, sizeof tmp, file);
	return tmp;
}

void put_number_by_pos(FILE *file, int n, int i)
{
	fseek(file, i * (sizeof n), SEEK_SET);
	fwrite(&n, 1, sizeof n, file);
}
