#include "movie.h"

#include <assert.h>

void fwrite_movie(struct movie *movie, FILE *stream)
{
	assert(movie && stream);

	fprintf(stream, "%s; %d; %s\n", movie->title, movie->year, movie->director);
}


void fwrite_movies(struct movie *movies, FILE *stream)
{
	assert(stream);

	for (; movies; movies = movies->next)
		fprintf(stream, "%s;%d;%s\n", movies->title, movies->year, movies->director);
}
