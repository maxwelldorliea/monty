#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * push - add a node(value) at the top of the stack
 * @top: current top of the stack
 * @val: the current line in the monty file
 * @mode: mode of execution
 * Return: Nothing
 */

void push(stack_t **top, int val, int mode)
{
	stack_t *node, *curr;

	if (!top)
		return;

	node = malloc(sizeof(*node));

	if (!node)
	{
		free(node);
		node = NULL;
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	node->n = val;
	node->next = NULL;
	node->prev = NULL;

	if (!(*top))
	{
		*top = node;
		return;
	}

	if (mode)
	{
		(*top)->prev = node;
		node->next = *top;
		*top = node;
	}
	else
	{
		curr = *top;
		while (curr->next)
			curr = curr->next;
		node->prev = curr;
		curr->next = node;
	}

}


/**
 * pall - print all nodes(value) in the stack
 * @top: top of the stack
 * @line_number: the current line in the monty file
 * Return: Nothing
 */


void pall(stack_t **top, unsigned int line_number)
{
	stack_t *curr;

	(void)line_number;

	if (!top)
		return;

	curr = *top;

	while (curr)
	{
		printf("%d\n", (curr)->n);
		curr = curr->next;
	}

}


/**
 * free_stack - frees all nodes(value) from memory
 * @top : top of the stack;
 * Return: Nothing
 */

void free_stack(stack_t **top)
{
	if (!top)
		return;

	while (*top)
	{
		stack_t *next = (*top)->next;

		free(*top);
		*top = next;
	}

	if (*top != NULL)
		*top = NULL;
}

/**
 * pint - prints the first node value of the stack
 * @top: top of the stack
 * @line_number: current line of execution
 * Return: Nothing
 */

void pint(stack_t **top, unsigned int line_number)
{

	if (!top || !(*top))
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*top)->n);
}

/**
 * pop - remove the first node of the stack
 * @top: top of the stack
 * @line_number: current line of execution
 * Return: Nothing
 */

void pop(stack_t **top, unsigned int line_number)
{
	stack_t *next;

	if (!top || !(*top))
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	next = (*top)->next;
	free(*top);
	*top = next;
}
