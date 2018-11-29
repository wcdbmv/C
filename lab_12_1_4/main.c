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

#define shotdown(var, label) \
{ \
	rc = var; \
	goto label; \
}

#define shotdown_c(command, var, label) \
{ \
	command; \
	rc = var; \
	goto label; \
}


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
		shotdown(SAME_FILENAMES, fin)

	FILE *input_file = fopen(input_filename, "r");
	if (!input_file)
		shotdown_c(perror(input_filename), CANT_OPEN_INPUT_FILE, fin)

	FILE *output_file = fopen(output_filename, "w");
	if (!output_file)
		shotdown_c(perror(output_filename), CANT_OPEN_OUTPUT_FILE, close_input)

	int size = count_array_size(input_file);
	if (size <= 0)
		shotdown(size, close_output)
	rewind(input_file);

	int *pb = NULL, *pe = NULL;
	rc = get_array(input_file, &pb, &pe, size);
	if (rc == FAILED_MALLOC)
		shotdown_c(perror("malloc"), rc, close_output)

	if (filter)
	{
		int *old_pb = pb, *old_pe = pe;
		double average;
		size = kpp(old_pb, old_pe, &average);
		if (!size)
			shotdown_c(free(old_pb), EMPTY_FILTERED_ARRAY, close_output)
		pb = malloc(size * sizeof (int));
		if (!pb)
			shotdown_c(free(old_pb), FAILED_MALLOC, close_output)
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
