#include "ui.h"

#include <string.h>
#include <stdlib.h>

#define LINE_SIZE_LIMIT 32

int main(void)
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	struct movie *head = NULL;
	struct base base;
	memset(base.filter, 0, MAX_FILTER_INDEX * sizeof *base.filter);

	bool runtime = true;
	while (runtime)
	{
		puts(
			"1. Load movies from file\n"
			"2. Save movies in file\n"
			"3. Show movies sorted by title\n"
			"4. Show movies sorted by year\n"
			"5. Show movies sorted by director\n"
			"6. Show movies in 20 century\n"
			"7. Show W. Allen's movies\n"
			"8. Add movie\n"
			"9. Remove movie\n"
			"0. Exit\n\n"
			"Input command: "
		);

		char command[LINE_SIZE_LIMIT];
		if (!fgets(command, LINE_SIZE_LIMIT, stdin) || !check_command(command))
		{
			err();
			continue;
		}

		switch (command[0])
		{
			case '1':
				load(&head, &base);
				break;
			case '2':
				save(head);
				break;
			case '3':
			case '4':
			case '5':
				sort_by(&base, command[0] - '3');
				break;
			case '6':
			case '7':
				filter_by(&base, command[0] - '6');
				break;
			case '8':
				add(&head, &base);
				break;
			case '9':
				remov(&head, &base);
				break;
			case '0':
				runtime = false;
				break;
		}
	}

	free_movies(&head);

	return EXIT_SUCCESS;
}
