#include "monty.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * tokenize - split the buf and store it in an array
 * @buf: buffer to be split
 * @arr: array buffer to be store in
 * Return: Length of the array
 */

int tokenize(char *buf, char **arr)
{
	char *ptr;
	int i = 0;

	ptr = strtok(buf, " \n");
	while (ptr)
	{
		arr[i++] = ptr;
		ptr = strtok(NULL, " \n");
	}

	return (i);
}

/**
 * execute_func - executes the rightful monty function
 * @top: top of the stack
 * @num: value to be passed to the selected function
 * @line: current line of execution
 * @funcname: name of monty function to search for
 * Return: Nothing when found, Terminate the program when no function is found
 */

void execute_func(stack_t **top, int num, int line, char *funcname)
{
	void (*func)(stack_t **top, unsigned int line_number);

	func = get_func(funcname);
	if (func)
		func(top, num);
	else
	{

		fprintf(stderr, "L<%d>: unknown instruction <%s>\n", line, funcname);
		if (*top)
			free_stack(top);
		exit(EXIT_FAILURE);
	}
}


/**
 * main - Run the monty interpreter
 * @argc: the Length og the argument vector(array)
 * @argv: the argument vector
 * Return: 0 on success, 1 on failure
 */

int main(int argc, char **argv)
{
	int num, arrlen;
	stack_t *top = NULL;
	FILE *fp;
	char buf[1024], *arr[2], line_number = 0;
	size_t buflen = 1024;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}
	while (fgets(buf, buflen, fp) != NULL)
	{
		line_number++;
		arrlen = tokenize(buf, arr);

		if (arrlen != 2 && strcmp(arr[0], "push") == 0)
		{
			fprintf(stderr, "L<%d>: unknown instruction <%s>\n", line_number, arr[0]);
			if (top)
				free_stack(&top);
			return (EXIT_FAILURE);
		}
		if (arrlen == 1)
			num = 0;
		num = atoi(arr[1]);
		execute_func(&top, num, line_number, arr[0]);
	}
	fclose(fp);
	return (0);
}
