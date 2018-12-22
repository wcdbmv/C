#include "ui.h"

#include <string.h>
#include <assert.h>
#include "colors.h"

#define SYSTEM_FILE_LEN_LIMIT 250
#define LINE_SIZE_LIMIT 128

bool err()
{
	print_red("Error\n\n");
	return false;
}

bool suc()
{
	print_green("Successful\n\n");
	return true;
}

bool check_command(const char *command)
{
	assert(command);

	if (command[0] < '0' || command[0] > '9')
		return false;

	if (command[1] != '\n' || command[2] != '\0')
		return false;

	return true;
}

bool read_filename(char *filename)
{
	printf("Input filename: ");
	if (!fgets(filename, SYSTEM_FILE_LEN_LIMIT, stdin))
		return err();

	*strchr(filename, '\n') = '\0';

	return true;
}

bool save(struct movie *head)
{
	assert(head);

	char filename[SYSTEM_FILE_LEN_LIMIT];
	if (!read_filename(filename))
		return err();

	FILE *file = fopen(filename, "w");
	if (!file)
		return err();

	fwrite_movies(head, file);

	fclose(file);

	return suc();
}

bool load(struct movie **head, struct base *base)
{
	assert(head && base);

	char filename[SYSTEM_FILE_LEN_LIMIT];
	if (!read_filename(filename))
		return err();

	FILE *file = fopen(filename, "r");
	if (!file)
		return err();

	free_movies(head);

	bool rc = fread_movies(head, file, base);

	fclose(file);

	return rc ? suc() : err();
}

bool add(struct movie **head, struct base *base)
{
	assert(head && base);

	printf("Input movie in format `title;year;director`: ");
	char line[LINE_SIZE_LIMIT];
	if (!fgets(line, LINE_SIZE_LIMIT, stdin))
		return err();
	struct movie *movie = sread_movie(line);
	if (!movie)
		return err();
	push_movie(head, movie, base);
	return suc();
}

bool remov(struct movie **head, struct base *base)
{
	assert(head && base);

	printf("Input title: ");
	char line[LINE_SIZE_LIMIT];
	if (!fgets(line, LINE_SIZE_LIMIT, stdin) || *line == '\n')
		return err();

	*strchr(line, '\n') = '\0';

	return remove_movie(head, line, base) ? suc() : err();
}

#define PRINT_LIST_HEAD(field)                                                 \
	do                                                                         \
	{                                                                          \
		putchar('\n');                                                         \
		if (!base->field[i])                                                   \
		{                                                                      \
			puts("There are no movies");                                       \
			return false;                                                      \
		}                                                                      \
		struct list_head *iter = NULL;                                         \
		list_for_each(iter, base->field[i])                                    \
		{                                                                      \
			struct movie *mov = list_entry(iter->prev, struct movie, field[i]);\
			fwrite_movie(mov, stdout);                                         \
		}                                                                      \
		struct movie *movie = list_entry(iter->prev, struct movie, field[i]);  \
		fwrite_movie(movie, stdout);                                           \
		putchar('\n');                                                         \
	}                                                                          \
	while (0)

bool sort_by(struct base *base, size_t i)
{
	assert(base && i < MAX_SORT_INDEX);

	PRINT_LIST_HEAD(sort);

	return true;
}

bool filter_by(struct base *base, size_t i)
{
	assert(base && i < MAX_FILTER_INDEX);

	PRINT_LIST_HEAD(filter);

	return true;
}
