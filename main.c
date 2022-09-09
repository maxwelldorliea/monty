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

void tokenize(char *buf, char **arr)
{
	arr[0] = strtok(buf, " \t\r\n");
	arr[1] = strtok(NULL, " \t\r\n");
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
 * @mode: mode of execution
 * @arr: array of tokenize values
 * @line: current line of execution
 * Return: Nothing when found, Terminate the program when no function is found
 */

void execute_func(stack_t **top, char **arr, int line, int mode)
{
	int num;
	void (*func)(stack_t **top, unsigned int number);

	if (arr[1] != NULL)
		num = atoi(arr[1]);
	else
		num = 0;

	if (!arr[0] || arr[0][0] == '#')
		return;

	if (strcmp(arr[0], "push") == 0 && (!arr[1] || istherealpha(arr[1])))
	{
		fprintf(stderr, "L%d: usage: push integer\n", line);
		if (top)
			free_stack(top);
		exit(EXIT_FAILURE);
	}

	if (strcmp(arr[0], "push") == 0)
	{
		push(top, num, mode);
		return;
	}

	func = get_func(arr[0]);
	if (func)
		func(top, line);
	else if (!func && strcmp(arr[0], "\n") != 0)
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
	int line_number = 0, mode = 1;
	stack_t *top = NULL;
	FILE *fp;
	char buf[1024], *arr[100];
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

		if (strcmp(buf, "\n") == 0)
			continue;
		if (strncmp(buf, "queue ", 6) == 0 || strcmp(buf, "queue\n") == 0)
		{
			mode = 0;
			continue;
		}
		if (strncmp(buf, "stack ", 6) == 0 || strcmp(buf, "stack\n") == 0)
		{
			mode = 1;
			continue;
		}
		tokenize(buf, arr);
		execute_func(&top, arr, line_number, mode);
	}
	fclose(fp);
	if (top)
		free_stack(&top);
	return (0);
}
