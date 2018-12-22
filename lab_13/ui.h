#ifndef UI_H_
#define UI_H_

#include <stdbool.h>
#include <stddef.h>
#include "movie.h"

bool err();
bool suc();

bool check_command(const char *command);
bool load(struct movie **head, struct base *base);
bool save(struct movie *head);
bool sort_by(struct base *base, size_t i);
bool filter_by(struct base *base, size_t i);
bool add(struct movie **head, struct base *base);
bool remov(struct movie **head, struct base *base);

#endif // UI_H_
