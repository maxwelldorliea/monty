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

	ptr = strtok(buf, " \t\r\n");
	while (ptr)
	{
		arr[i++] = ptr;
		ptr = strtok(NULL, " \t\r\n");
	}

	return (i);
}

/**
 * istherealpha - check if there is an alphabet in a string
 * @s: string to check
 * Return: 1 if True or ) if False
 */

int istherealpha(char *s)
{
	while (*s)
	{
		if ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z'))
			return (1);
		s++;
	}

	return (0);
}

/**
 * execute_func - executes the rightful monty function
 * @top: top of the stack
 * @arr: array of tokenize values
 * @line: current line of execution
 * @arrlen: Length of the array
 * Return: Nothing when found, Terminate the program when no function is found
 */

void execute_func(stack_t **top, char **arr, int line, int arrlen)
{
	int num;
	void (*func)(stack_t **top, unsigned int number);

	if (arrlen == 1)
		num = 0;
	else
		num = atoi(arr[1]);

	if (istherealpha(arr[1]) && strcmp(arr[0], "push") == 0)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line);
		if (top)
			free_stack(top);
		exit(EXIT_FAILURE);
	}

	func = get_func(arr[0]);
	if (func)
		func(top, num);
	else
	{

		fprintf(stderr, "L%d: unknown instruction %s\n", line, arr[0]);
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
	int arrlen, line_number = 0;
	stack_t *top = NULL;
	FILE *fp;
	char buf[1024], *arr[2];
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
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			if (top)
				free_stack(&top);
			return (EXIT_FAILURE);
		}
		execute_func(&top, arr, line_number, arrlen);
	}
	fclose(fp);
	if (top)
		free_stack(&top);
	return (0);
}
