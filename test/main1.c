#include "monty.h"



int main(void)
{
	stack_t *top;

	top = NULL;

	push(&top, 10);
	push(&top, 50);
	push(&top, 100);
	push(&top, 23);
	pall(&top, 0);

	return (0);
}
