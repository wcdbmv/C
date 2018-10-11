#ifndef __MY_GETLINE_H__
#define __MY_GETLINE_H__

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include "my_string.h"
#include "errcodes.h"

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);

#endif // __MY_GETLINE_H__
