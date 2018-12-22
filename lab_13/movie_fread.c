#include "movie.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#define LINE_SIZE_LIMIT 128
#define FIRST_FILM_YEAR 1895
#define CURRENT_YEAR 2018

typedef int (*cmp_t)(struct movie *, struct movie *);

char *cut_leading_spaces(char *s)
{
	while (isspace(*s))
		++s;

	return s;
}

char *cut_trailing_spaces(char *s)
{
	while (isspace(*s))
		--s;

	return s;
}

char *strip(char *begin, char *end)
{
	if (begin >= end)
		return NULL;

	char *begin_s = cut_leading_spaces(begin);
	if (begin_s >= end)
		return NULL;
	char *end_s = cut_trailing_spaces(end);

	const size_t n = end_s - begin_s + 1;
	char *word = malloc(n + 1);
	if (!word)
		return NULL;

	strncpy(word, begin_s, n);
	word[n] = '\0';

	return word;
}

int str_to_year(char *begin, char *end)
{
	if (begin >= end)
		return 0;

	int d = 0;
	if (sscanf(begin, "%d", &d) != 1)
		return 0;

	if (d < FIRST_FILM_YEAR || d > CURRENT_YEAR)
		return 0;

	return d;
}

struct movie *sread_movie(char *line)
{
	char *end = line + strlen(line) - 1;
	*end = '\0';

	char *last = line;
	char *delims[MAX_SORT_INDEX - 1];
	for (size_t i = 0; i != MAX_SORT_INDEX - 1; ++i)
	{
		if (!(delims[i] = strchr(last, ';')))
			return NULL;
		*delims[i] = '\0';
		last = delims[i] + 1;
	}

	struct movie *movie = malloc(sizeof (struct movie));
	if (!movie)
		return NULL;

	if (!(movie->title = strip(line, delims[0] - 1)))
		goto free_movie;

	if (!(movie->year = str_to_year(delims[0] + 1, delims[1] - 1)))
		goto free_title;

	if (!(movie->director = strip(delims[1] + 1, end - 1)))
		goto free_title;

	return movie;

free_title:
	free(movie->title);
free_movie:
	free(movie);
	return NULL;
}

bool fread_movies(struct movie **head, FILE *stream, struct base *base)
{
	assert(head && stream && base);

	*head = NULL;
	memset(base->filter, 0, MAX_FILTER_INDEX * sizeof *base->filter);
	char line[LINE_SIZE_LIMIT];
	while (fgets(line, LINE_SIZE_LIMIT, stream))
	{
		struct movie *movie = sread_movie(line);
		if (!movie)
		{
			free_movies(head);
			return false;
		}
		push_movie(head, movie, base);
	}

	return true;
}
