#include "colors.h"

#include <stdio.h>

void cls()
{
	printf(CLS);
}

void print_red(const char *s)
{
	printf(DEFAULT RED_FG "%s" DEFAULT, s);
}

void print_green(const char *s)
{
	printf(DEFAULT GREEN_FG "%s" DEFAULT, s);
}

void print_flashing(const char *s)
{
	printf(DEFAULT FLASHING "%s" DEFAULT, s);
}
