#include "movie.h"
#include "ui.h"

#include <string.h>

bool test_check_command_simple(void);
bool test_check_command_not_num(void);
bool test_check_command_long(void);
bool test_sread_movie_simple(void);
bool test_sread_movie_year_director_missed(void);
bool test_sread_movie_empty_director(void);
bool test_sread_movie_empty_title(void);
bool test_sread_movie_invalid_year(void);
bool test_sread_movie_empty_year(void);
bool test_push_movie_simple(void);
bool test_remove_movie_simple(void);
bool test_remove_wrong_movie(void);
bool test_remove_movie_in_empty(void);

static bool (*tests[])(void) = {
	test_check_command_simple,
	test_check_command_not_num,
	test_check_command_long,
	test_sread_movie_simple,
	test_sread_movie_year_director_missed,
	test_sread_movie_empty_director,
	test_sread_movie_empty_title,
	test_sread_movie_invalid_year,
	test_sread_movie_empty_year,
	test_push_movie_simple,
	test_remove_movie_simple,
	test_remove_wrong_movie,
	test_remove_movie_in_empty };


extern inline bool print_result(const char *func, const bool res);
extern inline bool print_passed(const size_t passed, const size_t total);

int main()
{
	setbuf(stderr, NULL);

	const size_t n_tests = (&tests)[1] - tests;
	size_t passed = 0;

	for (size_t i = 0; i != n_tests; ++i)
		passed += tests[i]();

	return print_passed(passed, n_tests);
}

//——————————————————————————————————————————————————————————————————————— print

inline bool print_result(const char *func, const bool res)
{
	fprintf(stderr, "%s: %s\033[0m\n", func, res ? "\033[32mpassed" : "\033[31mfailed");
	return res;
}

// success — 0
inline bool print_passed(const size_t passed, const size_t total)
{
	fprintf(stderr, "passed %lu/%lu\n", passed, total);
	return passed != total;
}

//———————————————————————————————————————————————————————————————————————— test

bool test_check_command_simple(void)
{
	return print_result(__func__, check_command("7\n"));
}

bool test_check_command_not_num(void)
{
	return print_result(__func__, !check_command("&\n"));
}

bool test_check_command_long(void)
{
	return print_result(__func__, !check_command("55\n"));
}

bool test_sread_movie_simple(void)
{
	char line[] = "title;2018;dircetor";

	struct movie *movie = sread_movie(line);

	bool res = movie;

	free_movie(movie);

	return print_result(__func__, res);
}

bool test_sread_movie_year_director_missed(void)
{
	char line[] = "title 2018 dircetor";

	return print_result(__func__, !sread_movie(line));
}

bool test_sread_movie_empty_director(void)
{
	char line[] = "title; 2018;";

	return print_result(__func__, !sread_movie(line));
}

bool test_sread_movie_empty_title(void)
{
	char line[] = "; 2018; director";

	return print_result(__func__, !sread_movie(line));
}

bool test_sread_movie_invalid_year(void)
{
	char line[] = "title; 9999; dircetor";

	return print_result(__func__, !sread_movie(line));
}

bool test_sread_movie_empty_year(void)
{
	char line[] = "title;   ;dircetor";

	return print_result(__func__, !sread_movie(line));
}

bool test_push_movie_simple(void)
{
	struct movie *m1, *m2, *m3;
	char line[32] = "btitle1;2001;director1";
	m1 = sread_movie(line);
	strcpy(line, "atitle2;2000;director2");
	m2 = sread_movie(line);
	strcpy(line, "ctitle3;2010;director3");
	m3 = sread_movie(line);

	struct movie *head = NULL;
	struct base base;
	memset(base.filter, 0, MAX_FILTER_INDEX * sizeof *base.filter);

	push_movie(&head, m1, &base);
	push_movie(&head, m2, &base);
	push_movie(&head, m3, &base);

	struct movie *m = list_entry(base.sort[0], struct movie, sort[0]);
	bool res = !strcmp(m->title, m2->title);
	m = list_entry(base.sort[1], struct movie, sort[1]);
	res &= !strcmp(m->title, m3->title);
	m = list_entry(base.sort[2], struct movie, sort[2]);
	res &= !strcmp(m->title, m1->title);

	free_movies(&head);

	return print_result(__func__, res);
}

bool test_remove_movie_simple(void)
{
	struct movie *m1, *m2, *m3;
	char line[32] = "btitle1;2001;director2";
	m1 = sread_movie(line);
	strcpy(line, "atitle2;2000;director1");
	m2 = sread_movie(line);
	strcpy(line, "ctitle3;2010;director3");
	m3 = sread_movie(line);

	struct movie *head = NULL;
	struct base base;
	memset(base.filter, 0, MAX_FILTER_INDEX * sizeof *base.filter);

	push_movie(&head, m1, &base);
	push_movie(&head, m2, &base);
	push_movie(&head, m3, &base);

	bool res = remove_movie(&head, "atitle2", &base);

	struct movie *m = list_entry(base.sort[0], struct movie, sort[0]);
	res &= !strcmp(m->title, m1->title);
	m = list_entry(base.sort[1], struct movie, sort[1]);
	res &= !strcmp(m->title, m3->title);
	m = list_entry(base.sort[2], struct movie, sort[2]);
	res &= !strcmp(m->title, m1->title);

	free_movies(&head);

	return print_result(__func__, res);
}

bool test_remove_wrong_movie(void)
{
	struct movie *m1, *m2, *m3;
	char line[32] = "btitle1;2001;director2";
	m1 = sread_movie(line);
	strcpy(line, "atitle2;2000;director1");
	m2 = sread_movie(line);
	strcpy(line, "ctitle3;2010;director3");
	m3 = sread_movie(line);

	struct movie *head = NULL;
	struct base base;
	memset(base.filter, 0, MAX_FILTER_INDEX * sizeof *base.filter);

	push_movie(&head, m1, &base);
	push_movie(&head, m2, &base);
	push_movie(&head, m3, &base);

	bool res = !remove_movie(&head, "title", &base);

	free_movies(&head);

	return print_result(__func__, res);
}

bool test_remove_movie_in_empty(void)
{
	struct movie *head = NULL;
	struct base base;
	memset(base.filter, 0, MAX_FILTER_INDEX * sizeof *base.filter);

	return print_result(__func__, !remove_movie(&head, "title", &base));
}
