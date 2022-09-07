#include "monty.h"




/**
 * swap - swaps the first two node of the stack
 * @top: top of the stack
 * @line_number: current line of execution
 * Return: Nothing
 */

void swap(stack_t **top, unsigned int line_number)
{
	stack_t *next;
	int currV;

	if (!top || !(*top) || !((*top)->next))
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	next = (*top)->next;
	currV = (*top)->n;
	(*top)->n = next->n;
	next->n = currV;
}
