#include "action.h"

int set_action(char *s, action_t *action)
{
	if (!*s || s[1])
	{
		return WRONG_USAGE_ERROR;
	}

	switch (*s)
	{
		case 'a':
			*action = add;
			break;
		case 'm':
			*action = multiply;
			break;
		case 'o':
			*action = solve;
			break;
		case 'h':
			*action = help;
			break;
		default:
			return WRONG_USAGE_ERROR;
	}

	return SUCCESS;
}
