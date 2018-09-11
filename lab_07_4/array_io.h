#ifndef __ARRAY_IO_H__
#define __ARRAY_IO_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "errcodes.h"

int count_array_size(FILE *file);
int get_array(FILE *file, int **pb, int **pe, size_t size);
void write_array(FILE *file, int *pb, int *pe);

#endif // __ARRAY_IO_H__
