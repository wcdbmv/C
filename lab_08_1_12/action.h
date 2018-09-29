#ifndef __ACTION_H__
#define __ACTION_H__

#include "errcodes.h"

typedef enum
{
	add, multiply, solve, help
} action_t;

int set_action(char *s, action_t *action);

#endif // __ACTION_H__
