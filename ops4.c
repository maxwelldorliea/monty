#include "monty.h"


/**
 * rotr - make last node as the first element
 * @top: top of the stack
 * @line_number: current line of execution
 * Return: Nothing
 */


void rotr(stack_t **top, unsigned int line_number)
{
	stack_t *curr;

	(void)line_number;

	if (!top || !(*top) || !((*top)->next))
		return;

	curr = *top;

	while (curr->next != NULL)
		curr = curr->next;

	curr->prev->next = NULL;
	curr->next = *top;
	curr->prev = NULL;
	*top = curr;
}
