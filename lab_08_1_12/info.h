#ifndef __INFO_H__
#define __INFO_H__

#include <stdio.h>
#include "errcodes.h"

void usage(FILE *stream);
void my_perror(const int errcode);
void show_info(void);

#endif // __INFO_H__
