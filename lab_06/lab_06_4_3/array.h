#ifndef ARRAY_H
#define ARRAY_H

#define N 100

#define SUCCESS 0
#define BAD_USAGE -1
#define CANT_OPEN_FILE -2
#define EMPTY_FILE -3
#define INVALID_FILE_INPUT -4

void my_perror(int rc);
int read_array(FILE *file, int *a, int **end_a);
int check_overflow(FILE *file);
int count_different(int *begin_a, int *end_a);

#endif //ARRAY_H
