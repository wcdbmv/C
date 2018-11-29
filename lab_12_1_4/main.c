/*
 * Реализовать лабораторную работу 7 с использованием библиотек разного типа. В
 * библиотеку вынести функции ввода/вывода и обработки. Для динамических
 * библиотек использовать два вида компоновки.
 * Реализацию функцию-фильтр придется изменить таким образом, чтобы выделение
 * памяти выполняла вызывающая сторона.
 */

#include <string.h>
#include "arr_lib.h"
#include "interface.h"
#include "errcodes.h"

int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	int rc = SUCCESS;

	bool filter = false;

	if ((rc = check_args(argc, argv, &filter)) != SUCCESS)
		goto fin;

	const char *input_filename = argv[1];
	const char *output_filename = argv[2];

	if (!strcmp(input_filename, output_filename))
	{
		rc = SAME_FILENAMES;
		goto fin;
	}

	FILE *input_file = fopen(input_filename, "r");
	if (!input_file)
	{
		perror(input_filename);
		rc = CANT_OPEN_INPUT_FILE;
		goto fin;
	}

	FILE *output_file = fopen(output_filename, "w");
	if (!output_file)
	{
		perror(output_filename);
		rc = CANT_OPEN_OUTPUT_FILE;
		goto close_input;
	}

	int size = count_array_size(input_file);
	if (size <= 0)
	{
		rc = size;
		goto close_output;
	}
	rewind(input_file);

	int *pb = NULL, *pe = NULL;
	rc = get_array(input_file, &pb, &pe, size);
	if (rc == FAILED_MALLOC)
	{
		perror("malloc");
		goto close_output;
	}

	if (filter)
	{
		int *old_pb = pb, *old_pe = pe;
		double average;
		size = kpp(old_pb, old_pe, &average);
		if (!size)
		{
			free(old_pb);
			rc = EMPTY_FILTERED_ARRAY;
			goto close_output;
		}
		pb = malloc(size * sizeof (int));
		if (!pb)
		{
			free(old_pb);
			rc = FAILED_MALLOC;
			goto close_output;
		}
		pe = pb + size;
		key(old_pb, old_pe, pb, pe, average);
		free(old_pb);
	}

	mysort(pb, pe - pb, sizeof (int), compare_int);
	write_array(output_file, pb, pe);
	free(pb);

	rc = SUCCESS;

	close_output:
		fclose(output_file);

	close_input:
		fclose(input_file);

	fin:
		return my_perror(rc);
}
