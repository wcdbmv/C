#include "movie.h"

#include <stdlib.h>
#include <assert.h>

void free_movie(struct movie *movie)
{
	assert(movie);

	free(movie->title);
	free(movie->director);
	free(movie);
}

void free_movies(struct movie **head)
{
	assert(head);

	while (*head)
	{
		struct movie *tmp = (*head)->next;

		free_movie(*head);

		*head = tmp;
	}
}
