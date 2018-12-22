#include "movie.h"

#include <string.h>
#include <assert.h>

bool remove_movie(struct movie **head, const char *title, struct base *base)
{
	assert(head && title && base);

	if (!*head)
		return false;

	struct movie *movie = NULL;
	bool first = false;
	if (*head && !strcmp(title, (*head)->title))
	{
		first = true;
		movie = *head;
		*head = (*head)->next;
		for (size_t i = 0; i != MAX_SORT_INDEX; ++i)
			__list_del(movie->sort[i].prev, movie->sort[i].next);
		for (size_t i = 0; i != MAX_FILTER_INDEX; ++i)
			__list_del(movie->filter[i].prev, movie->filter[i].next);
	}

	for (size_t i = 0; i != MAX_SORT_INDEX; ++i)
	{
		struct movie *sort_head = list_entry(base->sort[i], struct movie, sort[i]);
		if (!strcmp(sort_head->title, title))
			base->sort[i] = *head ? base->sort[i]->next : NULL;
	}

	for (size_t i = 0; i != MAX_FILTER_INDEX; ++i)
	{
		if (!base->filter[i])
			continue;

		struct movie *filter_head = list_entry(base->filter[i], struct movie, filter[i]);
		if (!strcmp(filter_head->title, title))
			base->filter[i] = base->filter[i] != base->filter[i]->next ? base->filter[i]->next : NULL;
	}

	if (first)
	{
		movie->next = NULL;
		free_movies(&movie);
		return true;
	}

	for (movie = *head; movie->next; movie = movie->next)
		if (!strcmp(movie->next->title, title))
		{
			for (size_t i = 0; i != MAX_SORT_INDEX; ++i)
				__list_del(movie->next->sort[i].prev, movie->next->sort[i].next);
			for (size_t i = 0; i != MAX_FILTER_INDEX; ++i)
				__list_del(movie->next->filter[i].prev, movie->next->filter[i].next);

			struct movie *tmp = movie->next;
			movie->next = movie->next->next;
			tmp->next = NULL;
			free_movies(&tmp);
			return true;
		}

	return false;
}
