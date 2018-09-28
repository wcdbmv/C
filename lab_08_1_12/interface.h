#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <string.h>
#include <stdbool.h>
#include "action.h"
#include "info.h"
#include "matrix.h"

int check_filenames(int argc, char *argv[]);
int check_args(int argc, char *argv[], action_t *action);
int open_files(int argc, char *argv[], FILE **mtr_1, FILE **mtr_2, FILE **res);
void close_files(FILE **mtr_1, FILE **mtr_2, FILE **res);
int do_action(action_t action, FILE *mtr_1, FILE *mtr_2, FILE *res);

#endif // __INTERFACE_H__
