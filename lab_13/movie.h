#ifndef MOVIE_H_
#define MOVIE_H_

#include <stdbool.h>
#include <stdio.h>
#include "list.h"

#define MAX_SORT_INDEX 3
#define MAX_FILTER_INDEX 2

#pragma pack(push, 1)
struct movie
{
	char *title;
	int year;
	char *director;

	struct list_head sort[MAX_SORT_INDEX];
	struct list_head filter[MAX_FILTER_INDEX];

	struct movie *next;
};
#pragma pack(pop)

struct base
{
	struct list_head *sort[MAX_SORT_INDEX];
	struct list_head *filter[MAX_FILTER_INDEX];
};

struct movie *sread_movie(char *line);
bool fread_movies(struct movie **head, FILE *stream, struct base *base);
void push_movie(struct movie **head, struct movie *movie, struct base *base);
bool remove_movie(struct movie **head, const char *title, struct base *base);
void fwrite_movie(struct movie *movie, FILE *stream);
void fwrite_movies(struct movie *head, FILE *stream);
void free_movie(struct movie *movie);
void free_movies(struct movie **head);

#endif // MOVIE_H_
