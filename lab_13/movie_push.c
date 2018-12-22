#include "movie.h"

#include <string.h>
#include <assert.h>

typedef int (*cmp_t)(struct movie *, struct movie *);

int title_cmp(struct movie *a, struct movie *b)
{
	return strcmp(a->title, b->title);
}

int year_cmp(struct movie *a, struct movie *b)
{
	return b->year - a->year;
}

int director_cmp(struct movie *a, struct movie *b)
{
	return strcmp(a->director, b->director);
}

void push_filtered(struct movie *movie, struct base *base, size_t i)
{
	// fputs(".", stderr);

	if (base->filter[i])
	{
		list_add(&movie->filter[i], base->filter[i]);
		return;
	}

	INIT_LIST_HEAD(&movie->filter[i]);
	base->filter[i] = &movie->filter[i];
}

void filter_1(struct movie *movie, struct base *base)
{
	if (movie->year < 2000)
		push_filtered(movie, base, 0);
}

void filter_2(struct movie *movie, struct base *base)
{
	if (!strcmp("W. Allen", movie->director))
		push_filtered(movie, base, 1);
}

void sorted_insert(struct movie *movie, struct base *base, cmp_t cmp, size_t i)
{
	struct movie *head = list_entry(base->sort[i], struct movie, sort[i]);
	if (cmp(movie, head) < 0)
	{
		list_add(&movie->sort[i], base->sort[i]->prev);
		base->sort[i] = base->sort[i]->prev;
		return;
	}

	struct list_head *iter = base->sort[i]->next;
	for (; iter != base->sort[i]; iter = iter->next)
	{
		struct movie *curr = list_entry(iter, struct movie, sort[i]);
		if (cmp(movie, curr) < 0)
		{
			list_add(&movie->sort[i], iter->prev);
			return;
		}
	}

	list_add(&movie->sort[i], iter->prev);
}

void push_movie(struct movie **head, struct movie *movie, struct base *base)
{
	assert(head && movie && base);

	movie->next = *head;
	*head = movie;

	for (size_t i = 0; i != MAX_SORT_INDEX; ++i)
		INIT_LIST_HEAD(&(*head)->sort[i]);

	for (size_t i = 0; i != MAX_FILTER_INDEX; ++i)
		INIT_LIST_HEAD(&(*head)->filter[i]);

	filter_1(movie, base);
	filter_2(movie, base);

	if (!(*head)->next)
	{
		for (int i = 0; i < MAX_SORT_INDEX; ++i)
			base->sort[i] = &(*head)->sort[i];
		return;
	}

	sorted_insert(movie, base, title_cmp, 0);
	sorted_insert(movie, base, year_cmp, 1);
	sorted_insert(movie, base, director_cmp, 2);
}
