#include "monty.h"


/**
 * get_func - return the rightful monty function
 * @s: token to check for
 * Return: right function ON SUCCESS, NULL ON FAILURE
 */


void (*get_func(char *s))(stack_t **top, unsigned int line_number)
{
	instruction_t inst[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
	};

	const int LEN = 5;
	int i = 0;

	while (i < LEN)
	{
		if (strcmp(s, inst[i].opcode) == 0)
			return (inst[i].f);
		i++;
	}

	return (NULL);
}
