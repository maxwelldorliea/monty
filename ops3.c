#include "monty.h"




/**
 * mul - multiply the first node value with the second node value of the
 * stack and delete the top node
 * @top: top of the stack
 * @line_number: current line of execution
 * Return: Nothing
 */

void mul(stack_t **top, unsigned int line_number)
{
	stack_t *next;

	if (!top || !(*top) || !((*top)->next))
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	next = (*top)->next;
	next->n = next->n * (*top)->n;
	free(*top);
	*top = next;
}
