#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "errcodes.h"

typedef int (*compare_t)(const void *, const void *);
typedef int (*fn_count_array_size_t)(FILE *);
typedef int (*fn_get_array_t)(FILE *, int **, int **, size_t);
typedef void (*fn_write_array_t)(FILE *, const int *, const int *);
typedef size_t (*fn_kpp_t)(const int *, const int *, double *);
typedef void (*fn_key_t)(const int *, const int *, int *, int *, double);
typedef void (*fn_sort_t)(void *, size_t, size_t, compare_t);
typedef int (*fn_cmp_t)(const void *, const void *);

#define load(var, sym) \
{ \
	var = dlsym(handle, sym); \
	if (dlerror()) \
	{ \
		fputs (dlerror(), stderr); \
		rc = CANT_LOAD_DYNAMIC_LIBRARY; \
		goto close_dll; \
	} \
}

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

	void *handle = dlopen("/home/user/bmstu/c/gitlab/lab_12_1_4/libarr.so", RTLD_LAZY);
	if (!handle)
		shotdown_c(fputs(dlerror(), stderr), CANT_LOAD_DYNAMIC_LIBRARY, fin)

	fn_count_array_size_t count_array_size;
	fn_get_array_t get_array;
	fn_write_array_t write_array;
	fn_kpp_t kpp;
	fn_key_t key;
	fn_sort_t mysort;
	fn_cmp_t compare_int;

	load(count_array_size, "count_array_size")
	load(get_array, "get_array")
	load(write_array, "write_array")
	load(kpp, "kpp")
	load(key, "key")
	load(mysort, "mysort")
	load(compare_int, "compare_int")

	bool filter = false;

	if ((rc = check_args(argc, argv, &filter)) != SUCCESS)
		goto close_dll;

	const char *input_filename = argv[1];
	const char *output_filename = argv[2];

	if (!strcmp(input_filename, output_filename))
		shotdown(SAME_FILENAMES, close_dll)

	FILE *input_file = fopen(input_filename, "r");
	if (!input_file)
		shotdown_c(perror(input_filename), CANT_OPEN_INPUT_FILE, close_dll)

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

	close_dll:
		dlclose(handle);

	fin:
		return my_perror(rc);
}
