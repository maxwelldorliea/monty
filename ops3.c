#include "monty.h"
#include <stdio.h>
#include <stdlib.h>




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


/**
 * mod - find the mod of the first node value from the second node value of the
 * stack and delete the top node
 * @top: top of the stack
 * @line_number: current line of execution
 * Return: Nothing
 */

void mod(stack_t **top, unsigned int line_number)
{
	stack_t *next;

	if (!top || !(*top) || !((*top)->next))
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	if ((*top)->n == 0)
	{

		fprintf(stderr, "L%d: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}

	next = (*top)->next;
	next->n = next->n % (*top)->n;
	free(*top);
	*top = next;
}


/**
 * pchar - prints the value at the top of stack as char
 * @top: top of the stack
 * @line_number: current line of execution
 * Return: Nothing
 */


void pchar(stack_t **top, unsigned int line_number)
{
	int val;

	if (!top || !(*top))
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	val = (*top)->n;

	if (val >= 0 && val <= 127)
	{
		putchar(val);
		putchar('\n');
	}
	else
	{
		fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
		exit(EXIT_FAILURE);
	}
}


/**
 * pstr - prints the ascii value of all nodes in the stack
 * @top: top of the stack
 * @line_number: current line of execution
 * Return: Nothing
 */


void pstr(stack_t **top, unsigned int line_number)
{
	int val;
	stack_t *curr;

	(void)line_number;

	if (!top || !(*top))
	{
		putchar('\n');
		return;
	}

	curr = *top;

	while (curr && curr->n)
	{
		val = curr->n;

		if (val >= 0 && val <= 127)
			putchar(val);
		else
			break;
		curr = curr->next;
	}

	putchar('\n');
}


/**
 * rotl - make the first node the last
 * @top: top of the stack
 * @line_number: current line of execution
 * Return: Nothing
 */


void rotl(stack_t **top, unsigned int line_number)
{
	stack_t *curr;
	int val;

	(void)line_number;

	if (!top || !(*top) || !((*top)->next))
		return;

	curr = *top;

	while (curr->next)
	{

		val = curr->n;
		curr->n = curr->next->n;
		curr->next->n = val;
		curr = curr->next;
	}
}
